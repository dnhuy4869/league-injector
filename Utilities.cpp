#include "./Utilities.h"

std::string Utilities::GetFileName(const std::string fullPath)
{
	char separate = '\\';

	size_t i = fullPath.rfind(separate, fullPath.length());
	if (i != std::string::npos)
	{
		return(fullPath.substr(i + 1, fullPath.length() - i));
	}

	return("");
}

bool Utilities::IsProcessRunning(const WCHAR* procName)
{
	int count = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnap == 0x0 || hSnap == INVALID_HANDLE_VALUE)
	{
		return false;
	}
	else
	{
		PROCESSENTRY32 procEntry32;
		procEntry32.dwSize = sizeof(PROCESSENTRY32);
		if (Process32First(hSnap, &procEntry32))
		{
			do
			{
				if (!_wcsicmp(procEntry32.szExeFile, procName))
				{
					count++;
				}
			} while (Process32Next(hSnap, &procEntry32));
		}

		CloseHandle(hSnap);

		if (count >= 2)
		{
			return true;
		}
	}

	return false;
}

std::wstring Utilities::StringToWString(const std::string source)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.from_bytes(source);
}

DWORD Utilities::GetTargetProcessId(const WCHAR* procName)
{
	DWORD dwProcId = 0;

	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if ((DWORD)hSnap <= 0)
	{
		return false;
	}

	PROCESSENTRY32 procEntry32;
	procEntry32.dwSize = sizeof(PROCESSENTRY32);

	if (Process32First(hSnap, &procEntry32))
	{
		do
		{
			if (!_wcsicmp(procEntry32.szExeFile, procName))
			{
				dwProcId = (DWORD)procEntry32.th32ProcessID;
				break;
			}
		} while (Process32Next(hSnap, &procEntry32));
	}

	CloseHandle(hSnap);
	return dwProcId;
}

DWORD Utilities::GetModuleBase(DWORD procId, const wchar_t* modName)
{
	DWORD moduleAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
	if ((DWORD)hSnap <= 0)
	{
		return false;
	}

	MODULEENTRY32W modEntry32;
	modEntry32.dwSize = sizeof(MODULEENTRY32W);

	if (Module32FirstW(hSnap, &modEntry32))
	{
		do
		{
			if (!_wcsicmp(modEntry32.szModule, modName))
			{
				moduleAddr = (uintptr_t)modEntry32.modBaseAddr;
				break;
			}
		} while (Module32NextW(hSnap, &modEntry32));
	}

	CloseHandle(hSnap);
	return moduleAddr;
}

std::string Utilities::IntToHex(int number, int fillWidth, std::string prefix)
{
	std::stringstream stream;
	stream << prefix
		<< std::uppercase
		<< std::setfill('0') << std::setw(fillWidth)
		<< std::hex << number;

	return stream.str();
}

DWORD Utilities::GetExportedFunction(std::string moduleName, std::string functionName)
{
	DWORD moduleAddr = (DWORD)GetModuleHandleA(moduleName.c_str());
	if (moduleAddr <= 0)
	{
		return 0;
	}

	DWORD ret = (DWORD)GetProcAddress((HMODULE)moduleAddr, functionName.c_str());
	if (ret <= 0)
	{
		return 0;
	}

	return ret;
}

void Utilities::WriteProtected(HANDLE hProcess, void* lpAddress, void* buffer, SIZE_T dwSize)
{
	DWORD oldProtect;
	VirtualProtectEx(hProcess, lpAddress, dwSize, PAGE_EXECUTE_READWRITE, &oldProtect);
	WriteProcessMemory(hProcess, lpAddress, buffer, dwSize, 0);
	VirtualProtectEx(hProcess, lpAddress, dwSize, oldProtect, 0);
}