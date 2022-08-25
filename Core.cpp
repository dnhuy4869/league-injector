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

	if (!RELEASE_BUILD)
	{
		SelectOption();
	}

	if (!RELEASE_BUILD)
	{
		m_DllPath = "C:\\Users\\Admin\\Desktop\\Projects\\LeagueCheat\\LeagueCheat.Core\\Build\\LeagueCheat.Core.dll";
		goto SKIP_VERSION_CHECK;
	}

	GetDllPath();

	if (!GetServerVersion())
	{
		Console::Log("Check loader failed.", ConsoleColor::Red);
		Console::Pause();
		ExitProcess(0);
	}

	CheckLoaderVersion();

	CheckDllVersion();

	SKIP_VERSION_CHECK:

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
	std::cout << VMPSTRA("[4] Dump skin hash.") << std::endl;
	std::cout << VMPSTRA("[5] Dump spell database.") << std::endl;
	std::cout << io_color::yellow << VMPSTRA("Select option: ");
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

bool Core::InjectDll_CreateThread(DWORD procId, const std::string& dllPath)
{
	HANDLE hProcess = 0;
	void* pDllPath = 0;
	HANDLE hThread = 0;
	DWORD retCode = 0;
	bool isSuccess = false;

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

__declspec(naked) void stub()
{
	__asm
	{
		pushad
		pushfd

		call start

		start:
		pop ecx
		sub ecx, 7
		lea eax, [ecx + 32] // 32 = Code length + 11 int3 + 1
		push eax
		call dword ptr[ecx - 4] // LoadLibraryA address is stored before the shellcode

		popfd
		popad

		ret
	}
}

DWORD WINAPI stub_end()
{
	return 0;
}

bool Core::InjectDll_HijackThread(DWORD procId, const std::string& dllPath)
{
	HANDLE hProcess = 0;
	void* pShellCode = 0;
	HANDLE hThread = 0;
	HANDLE hSnapshot = 0;
	DWORD retCode = 0;
	bool isSuccess = false;

	DWORD threadId = 0;
	CONTEXT ctx;
	ctx.ContextFlags = CONTEXT_FULL;

	DWORD stublen = (DWORD)stub_end - (DWORD)stub;

	DWORD LoadLibraryA_Addr = (DWORD)LoadLibraryA;
	DWORD dllPathLen = strlen(dllPath.c_str()) + 1;

	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procId);
	if ((DWORD)hProcess <= 0)
	{
		goto INJECT_FAILED;
	}

	threadId = Utilities::GetHijackThreadId(procId);
	if (threadId <= 0)
	{
		goto INJECT_FAILED;
	}

	hThread = OpenThread(THREAD_ALL_ACCESS, false, threadId);
	if ((DWORD)hThread <= 0)
	{
		goto INJECT_FAILED;
	}

	//SuspendThread(hThread);
	Utilities::SuspendThread(procId, 0);

	if (!GetThreadContext(hThread, &ctx))
	{
		goto INJECT_FAILED;
	}

	pShellCode = VirtualAllocEx(hProcess, 0, 4096, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if ((DWORD)pShellCode <= 0)
	{
		goto INJECT_FAILED;
	}

	WriteProcessMemory(hProcess, pShellCode, &LoadLibraryA_Addr, sizeof(DWORD), NULL);
	WriteProcessMemory(hProcess, (PVOID)((LPBYTE)pShellCode + 4), stub, stublen, NULL); 
	WriteProcessMemory(hProcess, (PVOID)((LPBYTE)pShellCode + 4 + stublen), dllPath.c_str(), dllPathLen, NULL); 

	ctx.Esp -= 4;
	WriteProcessMemory(hProcess, (PVOID)ctx.Esp, &ctx.Eip, sizeof(PVOID), NULL);
	ctx.Eip = (DWORD)((LPBYTE)pShellCode + 4);

	if (!SetThreadContext(hThread, &ctx)) 
	{
		goto INJECT_FAILED;
	}

	//ResumeThread(hThread);
	Utilities::ResumeThread(procId, 0);

	INJECT_FAILED:

	if (hThread) CloseHandle(hThread);
	if (pShellCode) VirtualFreeEx(hProcess, pShellCode, 0, MEM_RELEASE);
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

		//InjectDll_HijackThread(m_ProcessId, m_DllPath);

		Core::AwaitGameLoad();

		if (!IsDllInjected())
		{
			Console::Log(VMPSTRA("Injecting..."), ConsoleColor::Yellow);

			if (!InjectDll_CreateThread(m_ProcessId, m_DllPath))
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
				case CmdOption::DumpSkinHash:
				{
					nlohmann::json command = {
						{ VMPSTRA("command"), CmdOption::DumpSkinHash },
					};

					const std::string obj_string = command.dump();
					m_ConsoleServer->Send(obj_string.c_str(), obj_string.size());

					break;
				}
				case CmdOption::DumpSpellDatabase:
				{
					nlohmann::json command = {
						{ VMPSTRA("command"), CmdOption::DumpSpellDatabase },
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

		if (!RELEASE_BUILD)
		{
			break;
		}
		
		Core::AwaitGameClose();
	}
}