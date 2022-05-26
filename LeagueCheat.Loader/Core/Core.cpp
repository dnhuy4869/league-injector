#include "./Core.h"

extern Utilities* Utils;
extern class Menu* Menu;
extern class D3DX9* D3DX9;

void Core::ExitFailed(const char* log)
{
	MessageBoxA(0, log, xorstr_("Error"), MB_ICONERROR);
	ExitProcess(-1);
}

void Core::CreateResources()
{
	CHAR szProgramFiles[MAX_PATH];
	SHGetSpecialFolderPathA(0, szProgramFiles, CSIDL_PROGRAM_FILES, FALSE);
	std::string rootPath = szProgramFiles;

	rootPath += "\\LeagueCheat";
	CreateDirectoryA(rootPath.c_str(), 0);
	
	std::string resPath = rootPath + "\\Resources";
	CreateDirectoryA(resPath.c_str(), 0);

	std::string scriptsPath = rootPath + "\\Scripts";
	CreateDirectoryA(scriptsPath.c_str(), 0);

	this->RobotoPath = resPath + "\\Roboto.ttf";
	if (!PathFileExistsA(this->RobotoPath.c_str()))
	{
		Utils->WriteDataToFile((UCHAR*)Roboto_RawBinary, sizeof(Roboto_RawBinary), this->RobotoPath, CREATE_NEW);
	}

	this->FontAwesomePath = resPath + "\\FontAwesome.ttf";
	if (!PathFileExistsA(this->FontAwesomePath.c_str()))
	{
		Utils->WriteDataToFile((UCHAR*)FontAwesome_RawBinary, sizeof(FontAwesome_RawBinary), this->FontAwesomePath, CREATE_NEW);
	}

	this->ArialUniPath = resPath + "\\ArialUni.ttf";

	this->ConfigPath = rootPath + "\\Config.ini";
	if (!PathFileExistsA(this->ConfigPath.c_str()))
	{
		Utils->WriteDataToFile((UCHAR*)0, 0, this->ConfigPath, CREATE_NEW);
	}

	this->CorePath = rootPath + "\\Sandbox.dll";

	this->ServicePath = rootPath + "\\Nvidia10.sys";
	if (!PathFileExistsA(this->ServicePath.c_str()))
	{
		//Utils->WriteDataToFile((UCHAR*)Xtreme_RawBinary, sizeof(Xtreme_RawBinary), this->XtremePath, CREATE_NEW);
	}
}

bool Core::IsSectionProtected()
{
	clock_t firstTick = 0;
	clock_t lastTick = 0;
	firstTick = clock();

	DWORD leagueBase = Utils->GetModuleAddr(this->ProcessId, L"League of Legends.exe");

	while (true)
	{
		Sleep(1000);

		lastTick = clock();
		if (lastTick - firstTick > 8000)
		{
			return false;
		}

		DWORD oldProtect;
		if (!VirtualProtectEx(this->hProcess, (LPVOID)leagueBase, 1, PAGE_EXECUTE_READWRITE, &oldProtect))
		{
			Menu->Print("VirtualProtectEx failed.", D3DX9->Color.Red600);
			continue;
		}

		BYTE originByte;
		if (!ReadProcessMemory(this->hProcess, (void*)leagueBase, &originByte, 1, 0))
		{
			Menu->Print("ReadProcessMemory failed.", D3DX9->Color.Red600);
			continue;
		}

		BYTE patchByte;
		if (!WriteProcessMemory(this->hProcess, (void*)leagueBase, &patchByte, 1, 0))
		{
			Menu->Print("WriteProcessMemory failed.", D3DX9->Color.Red600);
			continue;
		}

		WriteProcessMemory(this->hProcess, (void*)leagueBase, &originByte, 1, 0);
		VirtualProtectEx(this->hProcess, (LPVOID)leagueBase, 1, oldProtect, nullptr);
		return true;
	}

	return false;
}

void Core::WriteProtected(DWORD addr, void* value, size_t size)
{
	DWORD oldProtect;
	VirtualProtectEx(this->hProcess, (LPVOID)addr, size, PAGE_EXECUTE_READWRITE, &oldProtect);
	WriteProcessMemory(this->hProcess, (LPVOID)addr, value, size, nullptr);
	VirtualProtectEx(this->hProcess, (LPVOID)addr, size, oldProtect, nullptr);
}

bool Core::ScanHook(HANDLE hProcess, LPCSTR ModuleName, LPCSTR FuncName)
{
	DWORD moduleAddr = (DWORD)GetModuleHandleA(ModuleName);
	if (moduleAddr <= 0)
	{
		return false;
	}

	DWORD funcAddr = (DWORD)GetProcAddress((HMODULE)moduleAddr, FuncName);
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

	if (bIsHooked)
	{
		this->WriteProtected(funcAddr, &OriginalBytes, HOOK_BYTES);
		return true;
	}
}

bool Core::RestoreNtdll()
{
	this->ScanHook(this->hProcess, "ntdll.dll", "NtProtectVirtualMemory");
	this->ScanHook(this->hProcess, "ntdll.dll", "NtQueryVirtualMemory");
	this->ScanHook(this->hProcess, "ntdll.dll", "NtCreateSection");

	return true;
}