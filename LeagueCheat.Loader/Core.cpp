#include "./Core.h"

bool Core::Initialize()
{
	Console::Setup(VMPSTRA("Loader"));

	GetDllPath();

	WSADATA WSAData;
	int error = WSAStartup(MAKEWORD(2, 2), &WSAData);
	if (error != 0)
	{
		Console::Log(VMPSTRA("WSAStartup failed with code ") + Utilities::IntToHex(WSAGetLastError()), ConsoleColor::Red);
		Console::Pause();
		ExitProcess(0);
	}

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

	if (ScanHook(Core::ProcessHandle, VMPSTRA("ntdll.dll"), VMPSTRA("NtCreateSection")))
	{
		Sleep(3000);
		return;
	}
	else
	{
		Sleep(8000);
	}

	while (true)
	{
		if (ScanHook(Core::ProcessHandle, VMPSTRA("ntdll.dll"), VMPSTRA("NtCreateSection")))
		{
			break;
		}

		Sleep(1000);
	}
}

typedef HMODULE(__stdcall* f_LoadLibraryA)(LPCSTR);

struct LOADLIBRARYA_DATA
{
	f_LoadLibraryA pLoadLibraryA;
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

bool Core::IsDllInjected()
{
	DWORD moduleBase = Utilities::GetModuleBase(Core::ProcessId, L"");
	if (moduleBase > 0)
	{
		return true;
	}

	return false;
}

void Core::InjectDll()
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

void Core::PrintMessage()
{
	Console::Log(VMPSTRA("Connecting to io server..."), ConsoleColor::Yellow);

	IOClient = new TCPSocket(VMPSTRA("127.0.0.1"), 27015);

	while (!IOClient->Connect())
	{
		Sleep(1000);
	}

	Console::Log(VMPSTRA("Connected successfully."), ConsoleColor::Green);

	char buffer[4096];

	while (true)
	{
		Sleep(10);

		ZeroMemory(buffer, sizeof(buffer));

		if (IOClient->Recv(buffer, sizeof(buffer)))
		{
			std::string message = buffer;
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

		//Core::AwaitGameLoad();

		Win32Hook::Initialize(Core::ProcessHandle);

		Core::DllPath = "C:\\Users\\Admin\\Desktop\\Projects\\LeagueCheat\\LeagueCheat.Core\\Release\\LeagueCheat.Core.dll";

		if (!IsDllInjected())
		{
			Core::InjectDll();
		}

		CloseHandle(ProcessHandle);

		ProcessId = 0;
		ProcessHandle = 0;

		Win32Hook::Dispose();

		Console::Log(VMPSTRA("Game process is running..."), ConsoleColor::Yellow);

		hMessageThread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)PrintMessage, 0, 0, 0);

		Core::AwaitGameClose();
	}
}