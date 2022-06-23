#include "./Core.h"

bool Core::Initialize()
{
	Console::Setup(VMPSTRA("Loader"));

	GetDllPath();

	return true;
}

void Core::GetDllPath()
{
	CHAR szProgramFiles[MAX_PATH];
	SHGetSpecialFolderPathA(0, szProgramFiles, CSIDL_PROGRAM_FILES, FALSE);
	std::string rootPath = szProgramFiles;

	CreateDirectoryA(rootPath.c_str(), 0);

	DllPath = rootPath + VMPSTRA("\\LeagueCheat.Core.dll");
}

void Core::GetGameProcess()
{
	Console::Log(VMPSTRA("Waiting for game process..."), ConsoleColor::Yellow);

	while (true)
	{
		Sleep(1000);

		//Core::ProcessId = Utilities::GetTargetProcessId(VMPSTRW(L"hackme-x86.exe"));
		Core::ProcessId = Utilities::GetTargetProcessId(VMPSTRW(L"League of Legends.exe"));

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

bool Core::ScanHook(HANDLE hProcess, std::string moduleName, std::string funcName)
{
	DWORD moduleAddr = (DWORD)GetModuleHandleA(moduleName.c_str());
	if (moduleAddr <= 0)
	{
		return false;
	}

	DWORD funcAddr = (DWORD)GetProcAddress((HMODULE)moduleAddr, funcName.c_str());
	if (funcAddr <= 0)
	{
		return false;
	}

	const int HOOK_BYTES = 16;
	BYTE OriginalBytes[HOOK_BYTES] = {};
	BYTE ScanBytes[HOOK_BYTES] = {};

	ZeroMemory(OriginalBytes, HOOK_BYTES);
	ZeroMemory(ScanBytes, HOOK_BYTES);

	memcpy(OriginalBytes, (void*)funcAddr, HOOK_BYTES);
	ReadProcessMemory(hProcess, (void*)funcAddr, ScanBytes, sizeof(ScanBytes), nullptr);

	bool bIsHooked = false;
	for (int i = 0; i != HOOK_BYTES; ++i)
	{
		if (OriginalBytes[i] != ScanBytes[i])
		{
			bIsHooked = true;
		}
	}

	return bIsHooked;
}

void Core::AwaitGameLoad()
{
	Console::Log(VMPSTRA("Waiting for game completely loaded..."), ConsoleColor::Yellow);

	while (true)
	{
		Sleep(1000);

		if (ScanHook(Core::ProcessHandle, VMPSTRA("ntdll.dll"), VMPSTRA("NtCreateSection")))
		{
			break;
		}
	}
}

typedef HMODULE(__stdcall* f_LoadLibraryA)(LPCSTR);

typedef DWORD(__stdcall* f_GetLastError)();

struct LOADLIBRARYA_DATA
{
	f_LoadLibraryA pLoadLibraryA;
	f_GetLastError pGetLastError;
	CHAR szDllPath[MAX_PATH];
};

DWORD __stdcall LoadLibrary_ShellCode(void* data)
{
	if (!data)
	{
		return 0;
	}

	LOADLIBRARYA_DATA* pData = (LOADLIBRARYA_DATA*)data;

	DWORD ret = (DWORD)pData->pLoadLibraryA(pData->szDllPath);

	return ret;
}

DWORD __stdcall LoadLibrary_ShellCodeEnd()
{
	return 0;
}

void Core::InjectDll()
{
	Console::Log(VMPSTRA("Injecting..."), ConsoleColor::Yellow);
	Sleep(3000);

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

	/*void* pShellCode = VirtualAllocEx(ProcessHandle, 0, 500, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if ((DWORD)pShellCode <= 0)
	{
		VirtualFreeEx(ProcessHandle, pData, 0, MEM_RELEASE);

		Console::Log(VMPSTRA("VirtualAllocEx failed with code ") + Utilities::IntToHex(GetLastError()), ConsoleColor::Red);
		Console::Pause();
		ExitProcess(0);
	}

	if (!WriteProcessMemory(ProcessHandle,
		pShellCode, 
		LoadLibrary_ShellCode,
		(DWORD)LoadLibrary_ShellCodeEnd - (DWORD)LoadLibrary_ShellCode,
		0))
	{
		VirtualFreeEx(ProcessHandle, pData, 0, MEM_RELEASE);
		VirtualFreeEx(ProcessHandle, pShellCode, 0, MEM_RELEASE);

		Console::Log(VMPSTRA("WriteProcessMemory failed with code ") + Utilities::IntToHex(GetLastError()), ConsoleColor::Red);
		Console::Pause();
		ExitProcess(0);
	}*/

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

		Console::Log(VMPSTRA("LoadLibraryA failed with code ") + Utilities::IntToHex(retCode), ConsoleColor::Red);
		Console::Pause();
		ExitProcess(0);
	}

	VirtualFreeEx(ProcessHandle, pDllPath, 0, MEM_RELEASE);

	Console::Log(VMPSTRA("Injected successfully."), ConsoleColor::Green);
}

void Core::AwaitGameClose()
{
	system(VMPSTRA("cls"));

	Console::Log(VMPSTRA("Game process is running..."), ConsoleColor::Yellow);

	while (true)
	{
		Sleep(1000);

		Core::ProcessId = Utilities::GetTargetProcessId(VMPSTRW(L"League of Legends.exe"));

		if (Core::ProcessId <= 0)
		{
			Console::Log(VMPSTRA("Game process is closed."), ConsoleColor::Yellow);
			break;
		}
	}

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

		Core::DllPath = "C:\\Users\\Admin\\Desktop\\Projects\\LeagueCheat\\LeagueCheat.Core\\Release\\LeagueCheat.Core.dll";
		Core::InjectDll();

		CloseHandle(ProcessHandle);

		ProcessId = 0;
		ProcessHandle = 0;

		Win32Hook::Dispose();



		Core::AwaitGameClose();
	}
}