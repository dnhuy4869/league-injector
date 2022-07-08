#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <iostream>

class Utilities abstract final
{
	public:

	static DWORD GetTargetProcessId(const WCHAR* procName);

	static DWORD GetModuleBase(DWORD procId, const wchar_t* modName);

	static std::string IntToHex(int number, int fillWidth = 8, std::string prefix = "0x");

	static DWORD GetExportedFunction(std::string moduleName, std::string functionName);

	static void WriteProtected(HANDLE hProcess, void* lpAddress, void* buffer, SIZE_T dwSize);

	template <typename T>
	static T ReadEx(HANDLE hProcess, DWORD addr)
	{
		T buffer;
		ReadProcessMemory(hProcess, (LPCVOID)addr, &buffer, sizeof(buffer), nullptr);

		return buffer;
	}
};