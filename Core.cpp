#include "Core.h"

DWORD WINAPI UnloadCore(HMODULE hModule)
{
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}

bool Core::Initialize()
{
	Console::Setup("Loader");

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
		Console::Log("Console setup failed.", ConsoleColor::Red);
		Console::Pause();
		ExitProcess(0);
	}

	//SelectOption();

	GetDllPath();

	if (!GetServerVersion())
	{
		Console::Log("Check loader failed.", ConsoleColor::Red);
		Console::Pause();
		ExitProcess(0);
	}

	CheckLoaderVersion();

	CheckDllVersion();

	if (!GetGameTimeOffset())
	{
		Console::Log("Get offsets failed.", ConsoleColor::Red);
		Console::Pause();
		ExitProcess(0);
	}

	Console::Clear();
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
				Console::Log(cmd_json["message"], cmd_json["consoleColor"]);
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

void Core::GetDllPath()
{
	CHAR szProgramFiles[MAX_PATH];
	SHGetSpecialFolderPathA(0, szProgramFiles, CSIDL_COMMON_APPDATA, FALSE);
	std::string rootPath = szProgramFiles;

	rootPath += "\\LeagueCheat";
	CreateDirectoryA(rootPath.c_str(), 0);

	m_DllPath = rootPath + "\\LeagueCheat.Core.dll";

	m_VersionJsonPath = rootPath + "\\version.json";
}

bool Core::GetServerVersion()
{
	Console::Log("Checking version...", ConsoleColor::Yellow);

	if (PathFileExistsA(m_VersionJsonPath.c_str()))
	{
		_unlink(m_VersionJsonPath.c_str());
	}

	std::string versionLink = "https://github.com/dnhuy4869/LeagueCheat.Dependencies/raw/master/version.json";

	HRESULT hr = URLDownloadToFileA(NULL, versionLink.c_str(), m_VersionJsonPath.c_str(), 0, NULL);
	if (FAILED(hr))
	{
		return false;
	}

	std::ifstream i(m_VersionJsonPath);
	nlohmann::json versionJson;
	i >> versionJson;

	m_LoaderServerVersion = versionJson["loaderVersion"];
	m_CoreServerVersion = versionJson["coreVersion"];

	return true;
}

void Core::CheckLoaderVersion()
{
	std::string updateLink = "https://github.com/dnhuy4869/LeagueCheat.Dependencies/raw/master/Loader.exe";

	if (m_LoaderServerVersion > LOADER_VERSION)
	{
		Console::Log("Downloading...", ConsoleColor::Yellow);

		CHAR szExeFileName[MAX_PATH];
		GetModuleFileNameA(NULL, szExeFileName, sizeof(szExeFileName));
		std::string loaderPath = szExeFileName;

		CHAR szBuffer[MAX_PATH];
		GetCurrentDirectoryA(sizeof(szBuffer), szBuffer);
		std::string currentPath = szBuffer;

		std::string loaderUpdatePath = currentPath + VMPSTRA("\\Unknown3304.exe");
		std::string loaderOldPath = currentPath + VMPSTRA("\\Loader_old_3304.exe");

		HRESULT hr = URLDownloadToFileA(NULL, updateLink.c_str(), loaderUpdatePath.c_str(), 0, NULL);
		if (SUCCEEDED(hr))
		{
			Console::Log("Restarting...", ConsoleColor::Yellow);

			Sleep(500);

			rename(loaderPath.c_str(), loaderOldPath.c_str());
			rename(loaderUpdatePath.c_str(), loaderPath.c_str());

			ShellExecuteA(NULL, "open", loaderPath.c_str(), NULL, NULL, SW_SHOWDEFAULT);
			ExitProcess(0);
		}
		else
		{
			Console::Log("Download loader failed", ConsoleColor::Red);
			Console::Pause();
			ExitProcess(0);
		}
	}
}

void Core::CheckDllVersion()
{
	Console::Log("Checking core...", ConsoleColor::Yellow);

	bool isValidCore = true;

	if (PathFileExistsA(m_DllPath.c_str()))
	{
		HMODULE hModule = LoadLibraryA(m_DllPath.c_str());

		if ((DWORD)hModule > 0)
		{
			typedef DWORD(__stdcall* f_GetCoreVersion)();
			f_GetCoreVersion pGetCoreVersion = (f_GetCoreVersion)GetProcAddress(hModule, "GetCoreVersion");

			if ((DWORD)pGetCoreVersion > 0)
			{
				DWORD coreVersion = pGetCoreVersion();

				if (m_CoreServerVersion > coreVersion)
				{
					isValidCore = false;
				}
			}
			else
			{
				isValidCore = false;
			}
		}
		else
		{
			isValidCore = false;
		}

		HANDLE hUnload = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)UnloadCore, hModule, 0, 0);
		if (WaitForSingleObject(hUnload, INFINITE) == WAIT_FAILED)
		{
			Console::Log("Check core failed", ConsoleColor::Red);
			Console::Pause();
			ExitProcess(0);
		}
	}
	else
	{
		isValidCore = false;
	}

	std::string updateLink = "https://github.com/dnhuy4869/LeagueCheat.Dependencies/raw/master/LeagueCheat.Core.dll";

	if (!isValidCore)
	{
		if (PathFileExistsA(m_DllPath.c_str()))
		{
			if (_unlink(m_DllPath.c_str()) != 0)
			{
				Console::Log("Could not delete old core.", ConsoleColor::Red);
				Console::Pause();
				ExitProcess(0);
			}
		}

		Console::Log("Downloading...", ConsoleColor::Yellow);

		HRESULT hr = URLDownloadToFileA(NULL, updateLink.c_str(), m_DllPath.c_str(), 0, NULL);
		if (FAILED(hr))
		{
			Console::Log("Download core failed", ConsoleColor::Red);
			Console::Pause();
			ExitProcess(0);
		}
	}
}

bool Core::GetGameTimeOffset()
{
	Console::Log("Getting offsets...", ConsoleColor::Yellow);

	HMODULE hModule = LoadLibraryA(m_DllPath.c_str());

	if ((DWORD)hModule <= 0)
	{
		return false;
	}

	typedef DWORD(__stdcall* f_GetGameTimeOffset)();

	f_GetGameTimeOffset f_Function = (f_GetGameTimeOffset)GetProcAddress(hModule, VMPSTRA("GetGameTimeOffset"));
	if ((DWORD)f_Function <= 0)
	{
		return false;
	}

	m_GameTimeOffset = f_Function();

	HANDLE hUnload = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)UnloadCore, hModule, 0, 0);
	if (WaitForSingleObject(hUnload, INFINITE) == WAIT_FAILED)
	{
		return false;
	}

	return true;
}

void Core::AwaitProcess()
{
	Console::Log(VMPSTRA("Waiting for game process..."), ConsoleColor::Yellow);

	while (true)
	{
		Sleep(1000);

		m_ProcessId = Utilities::GetTargetProcessId(m_TargetName);

		if (m_ProcessId > 0)
		{
			break;
		}
	}
}

void Core::AwaitGameLoad()
{
	Console::Log(VMPSTRA("Waiting for game completely loaded..."), ConsoleColor::Yellow);

	DWORD leagueBase = 0;

	do
	{
		leagueBase = Utilities::GetModuleBase(m_ProcessId, m_TargetName);
	} while (leagueBase <= 0);

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, m_ProcessId);
	if ((DWORD)hProcess <= 0)
	{
		Console::Log("Could not find game process.", ConsoleColor::Red);
		Console::Pause();
		ExitProcess(0);
	}

	while (true)
	{
		Sleep(1000);

		float currentTime = Utilities::ReadEx<float>(hProcess, leagueBase + m_GameTimeOffset);
		if (currentTime > 1.0f)
		{
			break;
		}
	}

	CloseHandle(hProcess);
}

bool m_bSendSuccess = false;

void TimeoutSocket()
{
	if (Core::m_DllClient->Send("cls", 4))
	{
		m_bSendSuccess = true;
	}
}

bool Core::IsDllInjected()
{
	m_DllClient = new TCPSocket(VMPSTRA("127.0.0.1"), 25379);

	if (!m_DllClient->Connect())
	{
		return false;
	}

	HANDLE hTimeout = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)TimeoutSocket, 0, 0, 0);
	WaitForSingleObject(hTimeout, 1000);
	TerminateThread(hTimeout, 0);

	m_DllClient->Close();
	delete m_DllClient;

	if (!m_bSendSuccess)
	{
		return false;
	}

	return true;
}

void Core::AwaitGameClose()
{
	while (true)
	{
		Sleep(1000);

		if (Utilities::GetTargetProcessId(m_TargetName) <= 0)
		{
			break;
		}
	}

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
	while (true)
	{
		Sleep(10);

		if (m_ProcessId <= 0)
		{
			Core::AwaitProcess();
		}

		Core::AwaitGameLoad();

		if (!IsDllInjected())
		{
			Console::Log(VMPSTRA("Injecting..."), ConsoleColor::Yellow);

			if (!InjectDll(m_ProcessId, m_DllPath))
			{
				Console::Log(VMPSTRA("Inject attempt failed."), ConsoleColor::Red);
				Console::Pause();
				ExitProcess(0);
			}
			else
			{
				Console::Log(VMPSTRA("Injected sucessfully."), ConsoleColor::Green);
			}

			m_bSendCommand = true;
		}

		if (m_bSendCommand)
		{
			char buffer[512];
			ZeroMemory(buffer, sizeof(buffer));
			m_ConsoleServer->Recv(buffer, sizeof(buffer));

			switch (m_CmdOption)
			{
				case CmdOption::InjectCore:
				{
					nlohmann::json command = {
						{ VMPSTRA("command"), CmdOption::InjectCore },
						{ VMPSTRA("authKey"), VMPSTRA("abcxyz") },
					};

					const std::string obj_string = command.dump();
					m_ConsoleServer->Send(obj_string.c_str(), obj_string.size());

					break;
				}
				case CmdOption::DumpProcess:
				{
					nlohmann::json command = {
						{ VMPSTRA("command"), CmdOption::DumpProcess },
					};

					const std::string obj_string = command.dump();
					m_ConsoleServer->Send(obj_string.c_str(), obj_string.size());

					break;
				}
				case CmdOption::DumpOffsets:
				{
					nlohmann::json command = {
						{ VMPSTRA("command"), CmdOption::DumpOffsets },
					};

					const std::string obj_string = command.dump();
					m_ConsoleServer->Send(obj_string.c_str(), obj_string.size());

					break;
				}
			}
		}
		else
		{
			Console::Log(VMPSTRA("Injected skipped, hack loaded sucessfully."), ConsoleColor::Green);
		}

		m_ProcessId = 0;
		m_ProcessHandle = 0;

		if ((DWORD)m_hMessageLoop <= 0)
		{
			m_hMessageLoop = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)ConsoleLog, 0, 0, 0);
		}

		Core::AwaitGameClose();
	}
}