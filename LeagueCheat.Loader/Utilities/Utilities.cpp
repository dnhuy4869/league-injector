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

DWORD Utilities::GetProcessId(const WCHAR* procName)
{
	DWORD dwProcId = 0;
	int count = 0;

	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap == 0x0 || hSnap == INVALID_HANDLE_VALUE)
	{
		return -1;
	}
	else
	{
		PROCESSENTRY32 procEntry32;
		procEntry32.dwSize = sizeof(PROCESSENTRY32);

		if (Process32First(hSnap, &procEntry32))
		{
			do
			{
				if (!_wcsicmp(procEntry32.szExeFile, procName) && procEntry32.cntThreads > count)
				{
					count = procEntry32.cntThreads;
					dwProcId = (int)procEntry32.th32ProcessID;
				}
			} while (Process32Next(hSnap, &procEntry32));
		}

		CloseHandle(hSnap);
		return dwProcId;
	}

	return -1;
}

std::wstring Utilities::string_to_wstring(const std::string source)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(source);
}

std::string Utilities::wstring_to_string(const std::wstring source)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.to_bytes(source);
}

bool Utilities::WriteDataToFile(UCHAR pBuffer[], DWORD dwSize, std::string& strFileName, DWORD dwCreationDisposition)
{
	HANDLE hFile = CreateFileA(strFileName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, nullptr, dwCreationDisposition, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (hFile == INVALID_HANDLE_VALUE) return false;
	DWORD dwNumberOfBytesWritten = NULL;
	BOOL bWriteFile = WriteFile(hFile, pBuffer, dwSize, &dwNumberOfBytesWritten, nullptr);
	CloseHandle(hFile);
	return !(!bWriteFile || dwNumberOfBytesWritten != dwSize);
}

int Utilities::system_no_output(std::string command)
{
	command.insert(0, "/C ");

	SHELLEXECUTEINFOA ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = NULL;
	ShExecInfo.lpFile = "cmd.exe";
	ShExecInfo.lpParameters = command.c_str();
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_HIDE;
	ShExecInfo.hInstApp = NULL;

	if (ShellExecuteExA(&ShExecInfo) == FALSE)
		return -1;

	WaitForSingleObject(ShExecInfo.hProcess, INFINITE);

	DWORD ExitCode;
	GetExitCodeProcess(ShExecInfo.hProcess, &ExitCode);
	CloseHandle(ShExecInfo.hProcess);

	return ExitCode;
}

BOOL Utilities::IsElevated()
{
	BOOL fRet = FALSE;
	HANDLE hToken = NULL;

	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
	{
		TOKEN_ELEVATION Elevation;
		DWORD cbSize = sizeof(TOKEN_ELEVATION);
		if (GetTokenInformation(hToken, TokenElevation, &Elevation, sizeof(Elevation), &cbSize))
		{
			fRet = Elevation.TokenIsElevated;
		}
	}

	if (hToken)
	{
		CloseHandle(hToken);
	}

	return fRet;
}

std::string Utilities::int_to_hex(int number, int fillWidth, std::string prefix)
{
	std::stringstream stream;
	stream << prefix
		<< std::uppercase
		<< std::setfill('0') << std::setw(fillWidth)
		<< std::hex << number;

	return stream.str();
}

DWORD Utilities::GetModuleAddr(DWORD procId, const wchar_t* modName)
{
	DWORD moduleAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);

	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry32;
		modEntry32.dwSize = sizeof(MODULEENTRY32W);

		if (Module32First(hSnap, &modEntry32))
		{
			do
			{
				if (!_wcsicmp(modEntry32.szModule, modName))
				{
					moduleAddr = (uintptr_t)modEntry32.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnap, &modEntry32));
		}
	}

	CloseHandle(hSnap);

	return moduleAddr;
}

DWORD Utilities::GetModuleSize(DWORD procId, const wchar_t* modName)
{
	DWORD moduleSize = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);

	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry32;
		modEntry32.dwSize = sizeof(MODULEENTRY32W);

		if (Module32First(hSnap, &modEntry32))
		{
			do
			{
				if (!_wcsicmp(modEntry32.szModule, modName))
				{
					moduleSize = (uintptr_t)modEntry32.modBaseSize;
					break;
				}
			} while (Module32Next(hSnap, &modEntry32));
		}
	}

	CloseHandle(hSnap);

	return moduleSize;
}

std::vector<std::string> Utilities::split_string(std::string s, std::string delimiter)
{
	size_t pos_start = 0, pos_end, delim_len = delimiter.length();
	std::string token;
	std::vector<std::string> res;

	while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
	{
		token = s.substr(pos_start, pos_end - pos_start);
		pos_start = pos_end + delim_len;
		res.push_back(token);
	}

	res.push_back(s.substr(pos_start));
	return res;
}

bool Utilities::IsNumber(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

void Utilities::Patch(void* dest, void* source, int size)
{
	DWORD oldProtect;
	VirtualProtect(dest, size, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy(dest, source, size);
	VirtualProtect(dest, size, oldProtect, &oldProtect);
}

void Utilities::Nop(void* dest, int size)
{
	DWORD oldProtect;
	VirtualProtect(dest, size, PAGE_EXECUTE_READWRITE, &oldProtect);
	memset(dest, 0x90, size);
	VirtualProtect(dest, size, oldProtect, &oldProtect);
}