#pragma once

#include "../WinMain.h"
#include "../Dependencies/ntdll.h"

class Utilities
{
public:

	std::string GetFileName(const std::string fullPath);

	bool IsProcessRunning(const WCHAR* procName);

	DWORD GetProcessId(const WCHAR* procName);

	std::wstring string_to_wstring(const std::string source);

	std::string wstring_to_string(const std::wstring source);

	bool WriteDataToFile(UCHAR pBuffer[], DWORD dwSize, std::string& strFileName, DWORD dwCreationDisposition);

	int system_no_output(std::string command);

	BOOL IsElevated();

	std::string int_to_hex(int number, int fillWidth = 8, std::string prefix = "0x");

	DWORD GetModuleAddr(DWORD procId, const wchar_t* modName);

	DWORD GetModuleSize(DWORD procId, const wchar_t* modName);

	std::vector<std::string> split_string(std::string s, std::string delimiter);

	bool IsNumber(const std::string& s);

	void Patch(void* dest, void* source, int size);

	void Nop(void* dest, int size);
};