#include "./Core.h"

extern const DWORD LOADER_VERSION;

DWORD WINAPI UnloadCore(HMODULE hModule)
{
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}

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
		Console::Log(VMPSTRA("Process is already running"), ConsoleColor::Red);
		Console::Pause();
		ExitProcess(0);
	}

	WSADATA WSAData;
	int error = WSAStartup(MAKEWORD(2, 2), &WSAData);
	if (error != 0)
	{
		Console::Log(VMPSTRA("WSAStartup failed with code ") + Utilities::IntToHex(WSAGetLastError()), ConsoleColor::Red);
		Console::Pause();
		ExitProcess(0);
	}

	GetDllPath();

	if (!GetServerVersion())
	{
		Console::Log(VMPSTRA("Check version failed with code ") + Utilities::IntToHex(WSAGetLastError()), ConsoleColor::Red);
		Console::Pause();
		ExitProcess(0);
	}

	CheckLoaderVersion();

	CheckDllVersion();

	if (!GetGameTimeOffset())
	{
		Console::Log(VMPSTRA("GetGameTimeOffset failed with code ") + Utilities::IntToHex(WSAGetLastError()), ConsoleColor::Red);
		Console::Pause();
		ExitProcess(0);
	}

	system(VMPSTRA("cls"));

	return true;
}

void Core::GetDllPath()
{
	CHAR szProgramFiles[MAX_PATH];
	SHGetSpecialFolderPathA(0, szProgramFiles, CSIDL_COMMON_APPDATA, FALSE);
	std::string rootPath = szProgramFiles;

	rootPath += VMPSTRA("\\LeagueCheat");
	CreateDirectoryA(rootPath.c_str(), 0);

	DllPath = rootPath + VMPSTRA("\\LeagueCheat.Core.dll");

	VersionJsonPath = rootPath + VMPSTRA("\\version.json");
}

bool Core::GetServerVersion()
{
	Console::Log(VMPSTRA("Checking version..."), ConsoleColor::Yellow);

	if (PathFileExistsA(VersionJsonPath.c_str()))
	{
		_unlink(VersionJsonPath.c_str());
	}

	std::string versionLink = VMPSTRA("https://github.com/dnhuy4869/LeagueCheat.Dependencies/raw/master/version.json");

	HRESULT hr = URLDownloadToFileA(NULL, versionLink.c_str(), VersionJsonPath.c_str(), 0, NULL);
	if (FAILED(hr))
	{
		Console::Log(VMPSTRA("URLDownloadToFileA failed with code ") + Utilities::IntToHex(GetLastError()), ConsoleColor::Red);
		Console::Pause();
		ExitProcess(0);
	}

	std::ifstream i(VersionJsonPath);
	nlohmann::json versionJson;
	i >> versionJson;

	LoaderServerVersion = versionJson[VMPSTRA("loaderVersion")];
	CoreServerVersion = versionJson[VMPSTRA("coreVersion")];

	return true;
}

void Core::CheckLoaderVersion()
{
	std::string updateLink = VMPSTRA("https://github.com/dnhuy4869/LeagueCheat.Dependencies/raw/master/Loader.exe");

	if (LoaderServerVersion > LOADER_VERSION)
	{
		Console::Log(VMPSTRA("Downloading..."), ConsoleColor::Yellow);

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
			Console::Log(VMPSTRA("Restarting..."), ConsoleColor::Yellow);

			Sleep(500);

			rename(loaderPath.c_str(), loaderOldPath.c_str());
			rename(loaderUpdatePath.c_str(), loaderPath.c_str());

			ShellExecuteA(NULL, VMPSTRA("open"), loaderPath.c_str(), NULL, NULL, SW_SHOWDEFAULT);
			ExitProcess(0);
		}
		else
		{
			Console::Log(VMPSTRA("URLDownloadToFileA failed with code ") + Utilities::IntToHex(GetLastError()), ConsoleColor::Red);
			Console::Pause();
			ExitProcess(0);
		}
	}
}

void Core::CheckDllVersion()
{
	Console::Log(VMPSTRA("Checking core..."), ConsoleColor::Yellow);

	bool isValidCore = true;

	if (PathFileExistsA(DllPath.c_str()))
	{
		HMODULE hModule = LoadLibraryA(DllPath.c_str());

		if ((DWORD)hModule > 0)
		{
			typedef DWORD(__stdcall* f_GetCoreVersion)();
			f_GetCoreVersion pGetCoreVersion = (f_GetCoreVersion)GetProcAddress(hModule, VMPSTRA("GetCoreVersion"));

			if ((DWORD)pGetCoreVersion > 0)
			{
				DWORD coreVersion = pGetCoreVersion();

				if (CoreServerVersion > coreVersion)
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
			Console::Log(VMPSTRA("WaitForSingleObject failed with code ") + Utilities::IntToHex(GetLastError()), ConsoleColor::Red);
			Console::Pause();
			ExitProcess(0);
		}
	}
	else
	{
		isValidCore = false;
	}

	std::string updateLink = VMPSTRA("https://github.com/dnhuy4869/LeagueCheat.Dependencies/raw/master/LeagueCheat.Core.dll");

	if (!isValidCore)
	{
		if (PathFileExistsA(DllPath.c_str()))
		{
			if (_unlink(DllPath.c_str()) != 0)
			{
				Console::Log(VMPSTRA("DeleteFile failed with code ") + Utilities::IntToHex(GetLastError()), ConsoleColor::Red);
				Console::Pause();
				ExitProcess(0);
			}
		}

		Console::Log(VMPSTRA("Downloading..."), ConsoleColor::Yellow);

		HRESULT hr = URLDownloadToFileA(NULL, updateLink.c_str(), DllPath.c_str(), 0, NULL);
		if (FAILED(hr))
		{
			Console::Log(VMPSTRA("URLDownloadToFileA failed with code ") + Utilities::IntToHex(GetLastError()), ConsoleColor::Red);
			Console::Pause();
			ExitProcess(0);
		}
	}
}

bool Core::GetGameTimeOffset()
{
	Console::Log(VMPSTRA("Getting offsets..."), ConsoleColor::Yellow);

	HMODULE hModule = LoadLibraryA(Core::DllPath.c_str());

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
	
	Core::GameTimeOffset = f_Function();

	HANDLE hUnload = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)UnloadCore, hModule, 0, 0);
	if (WaitForSingleObject(hUnload, INFINITE) == WAIT_FAILED)
	{
		return false;
	}

	return true;
}

void Core::GetGameProcess()
{
	Console::Log(VMPSTRA("Waiting for game process..."), ConsoleColor::Yellow);

	while (true)
	{
		Sleep(1000);

		Core::ProcessId = Utilities::GetTargetProcessId(TargetName);

		if (Core::ProcessId > 0)
		{
			break;
		}
	}

	Core::ProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Core::ProcessId);
	if ((DWORD)Core::ProcessHandle <= 0)
	{
		Console::Log(VMPSTRA("OpenProcess failed with code ") + Utilities::IntToHex(GetLastError()), ConsoleColor::Red);
		Console::Pause();
		ExitProcess(0);
	}
}

void Core::AwaitGameLoad()
{
	Console::Log(VMPSTRA("Waiting for game completely loaded..."), ConsoleColor::Yellow);

	Core::LeagueBase = Utilities::GetModuleBase(Core::ProcessId, TargetName);
	if (Core::LeagueBase <= 0)
	{
		Console::Log(VMPSTRA("GetModuleBase failed with code ") + Utilities::IntToHex(GetLastError()), ConsoleColor::Red);
		Console::Pause();
		ExitProcess(0);
	}

	while (true)
	{
		Sleep(1000);

		float currentTime = Utilities::ReadEx<float>(Core::ProcessHandle, Core::LeagueBase + Core::GameTimeOffset);
		if (currentTime > 1.0f)
		{
			break;
		}
	}
}

typedef HMODULE(__stdcall* f_LoadLibraryA)(LPCSTR);

struct LOADLIBRARYA_DATA
{
	f_LoadLibraryA pLoadLibraryA;
	CHAR szDllPath[MAX_PATH];
};

DWORD __stdcall LoadLibrary_Shellcode(void* data)
{
	if (!data)
	{
		return 0;
	}

	LOADLIBRARYA_DATA* pData = (LOADLIBRARYA_DATA*)data;

	DWORD ret = (DWORD)pData->pLoadLibraryA(pData->szDllPath);

	return ret;
}

DWORD __stdcall LoadLibrary_ShellcodeEnd()
{
	return 0;
}

bool Core::IsDllInjected()
{
	DWORD moduleBase = Utilities::GetModuleBase(Core::ProcessId, L"");
	if (moduleBase > 0)
	{
		return true;
	}

	return false;
}

void Core::NormalLoadLibrary()
{
	Console::Log(VMPSTRA("Injecting..."), ConsoleColor::Yellow);

	void* pDllPath = VirtualAllocEx(ProcessHandle, 0, 500, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if ((DWORD)pDllPath <= 0)
	{
		Console::Log(VMPSTRA("VirtualAllocEx failed with code ") + Utilities::IntToHex(GetLastError()), ConsoleColor::Red);
		Console::Pause();
		ExitProcess(0);
	}

	if (!WriteProcessMemory(ProcessHandle, pDllPath, DllPath.c_str(), strlen(DllPath.c_str()) + 1, 0))
	{
		VirtualFreeEx(ProcessHandle, pDllPath, 0, MEM_RELEASE);

		Console::Log(VMPSTRA("WriteProcessMemory failed with code ") + Utilities::IntToHex(GetLastError()), ConsoleColor::Red);
		Console::Pause();
		ExitProcess(0);
	}

	Win32Hook::RestoreHook(VMPSTRA("NtCreateSection"));
	//Win32Hook::RestoreHook(VMPSTRA("NtCreateThread"));
	//Win32Hook::RestoreHook(VMPSTRA("NtCreateThreadEx"));
	//Win32Hook::RestoreHook(VMPSTRA("LdrInitializeThunk"));

	HANDLE hThread = CreateRemoteThread(ProcessHandle, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, pDllPath, 0, 0);
	if ((DWORD)hThread <= 0)
	{
		VirtualFreeEx(ProcessHandle, pDllPath, 0, MEM_RELEASE);

		Console::Log(VMPSTRA("CreateRemoteThread failed with code ") + Utilities::IntToHex(GetLastError()), ConsoleColor::Red);
		Console::Pause();
		ExitProcess(0);
	}

	if (WaitForSingleObject(hThread, INFINITE) == WAIT_FAILED)
	{
		VirtualFreeEx(ProcessHandle, pDllPath, 0, MEM_RELEASE);

		Console::Log(VMPSTRA("WaitForSingleObject failed with code ") + Utilities::IntToHex(GetLastError()), ConsoleColor::Red);
		Console::Pause();
		ExitProcess(0);
	}

	DWORD retCode;
	GetExitCodeThread(hThread, &retCode);

	CloseHandle(hThread);
	
	Win32Hook::PlaceHook(VMPSTRA("NtCreateSection"));
	//Win32Hook::PlaceHook(VMPSTRA("NtCreateThread"));
	//Win32Hook::PlaceHook(VMPSTRA("NtCreateThreadEx"));
	//Win32Hook::PlaceHook(VMPSTRA("LdrInitializeThunk"));

	if (retCode <= 0)
	{
		VirtualFreeEx(ProcessHandle, pDllPath, 0, MEM_RELEASE);

		Console::Log(VMPSTRA("LoadLibraryA return ") + Utilities::IntToHex(retCode), ConsoleColor::Red);
		Console::Pause();
		ExitProcess(0);
	}

	VirtualFreeEx(ProcessHandle, pDllPath, 0, MEM_RELEASE);

	Console::Log(VMPSTRA("Injected successfully."), ConsoleColor::Green);
}

void Core::ShellcodeLoadLibrary()
{
	Console::Log(VMPSTRA("Injecting..."), ConsoleColor::Yellow);

	LOADLIBRARYA_DATA data;
	data.pLoadLibraryA = LoadLibraryA;
	memcpy(data.szDllPath, DllPath.c_str(), strlen(DllPath.c_str()) + 1);

	void* pData = VirtualAllocEx(ProcessHandle, 0, sizeof(LOADLIBRARYA_DATA), MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if ((DWORD)pData <= 0)
	{
		Console::Log(VMPSTRA("VirtualAllocEx failed with code ") + Utilities::IntToHex(GetLastError()), ConsoleColor::Red);
		Console::Pause();
		ExitProcess(0);
	}

	if (!WriteProcessMemory(ProcessHandle, pData, &data, sizeof(data), 0))
	{
		VirtualFreeEx(ProcessHandle, pData, 0, MEM_RELEASE);

		Console::Log(VMPSTRA("WriteProcessMemory failed with code ") + Utilities::IntToHex(GetLastError()), ConsoleColor::Red);
		Console::Pause();
		ExitProcess(0);
	}

	void* pShellcode = VirtualAllocEx(ProcessHandle, 0, 500, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if ((DWORD)pShellcode <= 0)
	{
		VirtualFreeEx(ProcessHandle, pData, 0, MEM_RELEASE);

		Console::Log(VMPSTRA("VirtualAllocEx failed with code ") + Utilities::IntToHex(GetLastError()), ConsoleColor::Red);
		Console::Pause();
		ExitProcess(0);
	}

	if (!WriteProcessMemory(ProcessHandle,
		pShellcode,
		LoadLibrary_Shellcode,
		(DWORD)LoadLibrary_ShellcodeEnd - (DWORD)LoadLibrary_Shellcode,
		0))
	{
		VirtualFreeEx(ProcessHandle, pData, 0, MEM_RELEASE);
		VirtualFreeEx(ProcessHandle, pShellcode, 0, MEM_RELEASE);

		Console::Log(VMPSTRA("WriteProcessMemory failed with code ") + Utilities::IntToHex(GetLastError()), ConsoleColor::Red);
		Console::Pause();
		ExitProcess(0);
	}

	Win32Hook::RestoreHook(VMPSTRA("NtCreateSection"));
	//Win32Hook::RestoreHook(VMPSTRA("NtCreateThread"));
	//Win32Hook::RestoreHook(VMPSTRA("NtCreateThreadEx"));
	//Win32Hook::RestoreHook(VMPSTRA("LdrInitializeThunk"));

	DWORD oldDataProtect;
	VirtualProtectEx(ProcessHandle, pData, sizeof(LOADLIBRARYA_DATA), PAGE_READWRITE, &oldDataProtect);
	DWORD oldShellcodeProtect;
	VirtualProtectEx(ProcessHandle, pShellcode, 500, PAGE_EXECUTE_READ, &oldShellcodeProtect);

	HANDLE hThread = CreateRemoteThread(ProcessHandle, 0, 0, (LPTHREAD_START_ROUTINE)pShellcode, pData, 0, 0);
	if ((DWORD)hThread <= 0)
	{
		DWORD tmp1;
		VirtualProtectEx(ProcessHandle, pData, sizeof(LOADLIBRARYA_DATA), oldDataProtect, &tmp1);
		DWORD tmp2;
		VirtualProtectEx(ProcessHandle, pShellcode, 500, oldShellcodeProtect, &tmp2);

		VirtualFreeEx(ProcessHandle, pData, 0, MEM_RELEASE);
		VirtualFreeEx(ProcessHandle, pShellcode, 0, MEM_RELEASE);

		Console::Log(VMPSTRA("CreateRemoteThread failed with code ") + Utilities::IntToHex(GetLastError()), ConsoleColor::Red);
		Console::Pause();
		ExitProcess(0);
	}

	if (WaitForSingleObject(hThread, INFINITE) == WAIT_FAILED)
	{
		DWORD tmp1;
		VirtualProtectEx(ProcessHandle, pData, sizeof(LOADLIBRARYA_DATA), oldDataProtect, &tmp1);
		DWORD tmp2;
		VirtualProtectEx(ProcessHandle, pShellcode, 500, oldShellcodeProtect, &tmp2);

		VirtualFreeEx(ProcessHandle, pData, 0, MEM_RELEASE);
		VirtualFreeEx(ProcessHandle, pShellcode, 0, MEM_RELEASE);

		Console::Log(VMPSTRA("WaitForSingleObject failed with code ") + Utilities::IntToHex(GetLastError()), ConsoleColor::Red);
		Console::Pause();
		ExitProcess(0);
	}

	DWORD retCode;
	GetExitCodeThread(hThread, &retCode);

	CloseHandle(hThread);

	Win32Hook::PlaceHook(VMPSTRA("NtCreateSection"));
	//Win32Hook::PlaceHook(VMPSTRA("NtCreateThread"));
	//Win32Hook::PlaceHook(VMPSTRA("NtCreateThreadEx"));
	//Win32Hook::PlaceHook(VMPSTRA("LdrInitializeThunk"));

	if (retCode <= 0)
	{
		DWORD tmp1;
		VirtualProtectEx(ProcessHandle, pData, sizeof(LOADLIBRARYA_DATA), oldDataProtect, &tmp1);
		DWORD tmp2;
		VirtualProtectEx(ProcessHandle, pShellcode, 500, oldShellcodeProtect, &tmp2);

		VirtualFreeEx(ProcessHandle, pData, 0, MEM_RELEASE);
		VirtualFreeEx(ProcessHandle, pShellcode, 0, MEM_RELEASE);

		Console::Log(VMPSTRA("LoadLibraryA return ") + Utilities::IntToHex(retCode), ConsoleColor::Red);
		Console::Pause();
		ExitProcess(0);
	}

	DWORD tmp1;
	VirtualProtectEx(ProcessHandle, pData, sizeof(LOADLIBRARYA_DATA), oldDataProtect, &tmp1);
	DWORD tmp2;
	VirtualProtectEx(ProcessHandle, pShellcode, 500, oldShellcodeProtect, &tmp2);

	VirtualFreeEx(ProcessHandle, pData, 0, MEM_RELEASE);
	VirtualFreeEx(ProcessHandle, pShellcode, 0, MEM_RELEASE);

	Console::Log(VMPSTRA("Injected successfully."), ConsoleColor::Green);
}

void Core::IOConnect()
{
	Console::Log(VMPSTRA("Connecting to io server..."), ConsoleColor::Yellow);

	IOClient = new TCPSocket(VMPSTRA("127.0.0.1"), 27015);

	while (!IOClient->Connect())
	{
		Sleep(1000);
	}

	Console::Log(VMPSTRA("Connected successfully."), ConsoleColor::Green);

	if (m_bSendCommand)
	{
		nlohmann::json command = {
			//{ VMPSTRA("command"), VMPSTRA("dumpOffsets") }
			{ VMPSTRA("command"), VMPSTRA("checkKey") }
		};

		const std::string obj_string = command.dump();
		IOClient->Send(obj_string.c_str(), obj_string.size());
	}
}

void Core::PrintMessage()
{
	char buffer[4096];

	while (true)
	{
		Sleep(10);

		ZeroMemory(buffer, sizeof(buffer));

		if (IOClient->Recv(buffer, sizeof(buffer)))
		{
			std::string message = buffer;
			IOClient->Send(message.c_str(), message.size());

			if (message != "")
			{
				Console::Log(buffer, ConsoleColor::Yellow);
			}
		}
	}
}

void Core::AwaitGameClose()
{
	while (true)
	{
		Sleep(1000);

		Core::ProcessId = Utilities::GetTargetProcessId(TargetName);

		if (Core::ProcessId <= 0)
		{
			//Console::Log(VMPSTRA("Game process is closed."), ConsoleColor::Yellow);
			break;
		}
	}

	TerminateThread(hMessageThread, 0);
	SAFE_DELETE_PTR(IOClient);

	system(VMPSTRA("cls"));
}

void Core::InjectThread()
{
	while (true)
	{
		Sleep(10);

		if (Core::ProcessId <= 0)
		{
			Core::GetGameProcess();
		}

		Core::AwaitGameLoad();

		Win32Hook::Initialize(Core::ProcessHandle);

		if (!IsDllInjected())
		{
			Core::NormalLoadLibrary();
			m_bSendCommand = true;
		}

		CloseHandle(ProcessHandle);

		ProcessId = 0;
		ProcessHandle = 0;

		Win32Hook::Dispose();

		Console::Log(VMPSTRA("Game process is running..."), ConsoleColor::Yellow);

		IOConnect();
		hMessageThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)PrintMessage, 0, 0, 0);

		Core::AwaitGameClose();
	}
}