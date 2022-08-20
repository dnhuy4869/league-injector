#pragma once

#include <Windows.h>
#include <TlHelp32.h>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <codecvt>

class Utilities abstract final
{
	public:

	static std::string GetFileName(const std::string fullPath);

	static bool IsProcessRunning(const WCHAR* procName);

	static std::wstring StringToWString(const std::string source);

	static DWORD GetTargetProcessId(const WCHAR* procName);

	static DWORD GetModuleBase(DWORD procId, const wchar_t* modName);

	static DWORD GetHijackThreadId(DWORD procId);

	static bool SuspendThread(DWORD procId, DWORD threadId);

	static bool ResumeThread(DWORD procId, DWORD threadId);

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