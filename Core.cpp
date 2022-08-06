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



	SelectOption();

	return true;
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

	std::cout << (int)m_CmdOption << std::endl;
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

	std::string dllPath = "C:\\Users\\Admin\\Desktop\\Projects\\LeagueCheat\\LeagueCheat.Core\\Release\\LeagueCheat.Core.dll";

	Console::Log(VMPSTRA("Injecting..."), ConsoleColor::Yellow);

	if (!InjectDll(procId, dllPath))
	{
		Console::Log(VMPSTRA("Inject attempt failed."), ConsoleColor::Red);
		Console::Pause();
		ExitProcess(0);
	}

	Console::Log(VMPSTRA("Injected sucessfully."), ConsoleColor::Green);
}