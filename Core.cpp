#include "Core.h"

bool Core::Initialize()
{
	Console::Setup(VMPSTRA("Loader"));

	CHAR szBuffer[MAX_PATH];
	GetFullPathNameA(VMPSTRA("Loader_old_3304.exe"), sizeof(szBuffer), szBuffer, nullptr);
	std::string oldLoaderPath = szBuffer;
	if (PathFileExistsA(oldLoaderPath.c_str()))
	{
		_unlink(oldLoaderPath.c_str());
	}

	CHAR szExeFileName[MAX_PATH];
	GetModuleFileNameA(NULL, szExeFileName, sizeof(szExeFileName));
	std::string fileName = Utilities::GetFileName(szExeFileName);

	if (Utilities::IsProcessRunning(Utilities::StringToWString(fileName).c_str()))
	{
		Console::Log(VMPSTRA("Process is already running."), ConsoleColor::Red);
		Console::Pause();
		ExitProcess(0);
	}

	WSADATA WSAData;
	int error = WSAStartup(MAKEWORD(2, 2), &WSAData);
	if (error != 0)
	{
		Console::Log(VMPSTRA("WSAStartup failed."), ConsoleColor::Red);
		Console::Pause();
		ExitProcess(0);
	}

	if (!ConsoleServer())
	{
		Console::Log(VMPSTRA("Console setup failed."), ConsoleColor::Red);
		Console::Pause();
		ExitProcess(0);
	}

	SelectOption();

	return true;
}

bool Core::ConsoleServer()
{
	m_ConsoleServer = new UDPSocket(VMPSTRA("127.0.0.1"), 25378);
	
	if (!m_ConsoleServer->Bind())
	{
		return false;
	}

	return true;
}

void Core::ConsoleLog()
{
	char buffer[4096];

	while (true)
	{
		Sleep(10);

		ZeroMemory(buffer, sizeof(buffer));

		if (m_ConsoleServer->Recv(buffer, sizeof(buffer)))
		{
			std::string message = buffer;

			if (message != "")
			{
				nlohmann::json cmd_json = nlohmann::json::parse(message);
				Console::Log(cmd_json[VMPSTRA("message")], cmd_json[VMPSTRA("consoleColor")]);
			}

			m_ConsoleServer->Send("cls", 4);
		}
	}
}

void Core::SelectOption()
{
	std::cout << io_color::yellow;
	std::cout << VMPSTRA("[1] Inject dll.") << std::endl;
	std::cout << VMPSTRA("[2] Dump process.") << std::endl;
	std::cout << VMPSTRA("[3] Dump offsets.") << std::endl;
	std::cout << io_color::yellow << "Select option: ";
	int option;
	std::cin >> option;
	m_CmdOption = (CmdOption)option;

	Console::Clear();
}

bool Core::InjectDll(DWORD procId, const std::string& dllPath)
{
	HANDLE hProcess = 0;
	void* pDllPath = 0;
	HANDLE hThread = 0;
	DWORD retCode = 0;
	bool isSuccess = 0;

	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procId);
	if ((DWORD)hProcess <= 0)
	{
		goto INJECT_FAILED;
	}

	pDllPath = VirtualAllocEx(hProcess, 0, 500, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if ((DWORD)pDllPath <= 0)
	{
		goto INJECT_FAILED;
	}

	if (!WriteProcessMemory(hProcess, pDllPath, dllPath.c_str(), strlen(dllPath.c_str()) + 1, 0))
	{
		goto INJECT_FAILED;
	}

	hThread = CreateRemoteThread(hProcess, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, pDllPath, 0, 0);
	if ((DWORD)hThread <= 0)
	{
		goto INJECT_FAILED;
	}

	if (WaitForSingleObject(hThread, INFINITE) == WAIT_FAILED)
	{
		goto INJECT_FAILED;
	}

	GetExitCodeThread(hThread, &retCode);

	if (retCode > 0)
	{
		isSuccess = true;
	}

	INJECT_FAILED:

	if (hThread) CloseHandle(hThread);
	if (pDllPath) VirtualFreeEx(hProcess, pDllPath, 0, MEM_RELEASE);
	if (hProcess) CloseHandle(hProcess);

	if (isSuccess)
	{
		return true;
	}

	return false;
}

void Core::InjectLoop()
{
	DWORD procId = Utilities::GetTargetProcessId(m_TargetName);
	if (procId <= 0)
	{
		Console::Log(VMPSTRA("Cound not find process id."), ConsoleColor::Red);
		Console::Pause();
		ExitProcess(0);
	}

	std::string dllPath = "C:\\Users\\Admin\\Desktop\\Projects\\LeagueCheat\\LeagueCheat.Core\\Build\\LeagueCheat.Core.dll";

	Console::Log(VMPSTRA("Injecting..."), ConsoleColor::Yellow);

	if (!InjectDll(procId, dllPath))
	{
		Console::Log(VMPSTRA("Inject attempt failed."), ConsoleColor::Red);
		Console::Pause();
		ExitProcess(0);
	}

	Console::Log(VMPSTRA("Injected sucessfully."), ConsoleColor::Green);

	char buffer[512];
	ZeroMemory(buffer, sizeof(buffer));
	m_ConsoleServer->Recv(buffer, sizeof(buffer));

	switch (m_CmdOption)
	{
		case CmdOption::InjectCore:
		{
			nlohmann::json command = {
				{ VMPSTRA("command"), VMPSTRA("loadCore") },
				{ VMPSTRA("authKey"), VMPSTRA("abcxyz") },
			};

			const std::string obj_string = command.dump();
			m_ConsoleServer->Send(obj_string.c_str(), obj_string.size());

			break;
		}
		case CmdOption::DumpProcess:
		{
			nlohmann::json command = {
				{ VMPSTRA("command"), VMPSTRA("dumpProcess") },
			};

			const std::string obj_string = command.dump();
			m_ConsoleServer->Send(obj_string.c_str(), obj_string.size());

			break;
		}
		case CmdOption::DumpOffsets:
		{
			nlohmann::json command = {
				{ VMPSTRA("command"), VMPSTRA("dumpOffsets") },
			};

			const std::string obj_string = command.dump();
			m_ConsoleServer->Send(obj_string.c_str(), obj_string.size());

			break;
		}
	}

	m_hMessageLoop = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ConsoleLog, 0, 0, 0);
}