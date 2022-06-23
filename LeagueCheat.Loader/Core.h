#pragma once

#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <filesystem>
#include <shlobj_core.h>

#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

#include "./VMProtect.h"
#include "./ThirdParty/io_color.h"
#include "./Console.h"
#include "./Utilities.h"
#include "./Win32Hook.h"
#include "./TCPSocket.h"

class Core abstract final
{
	private:

	public:

	inline static const wchar_t* TargetName = VMPSTRW(L"League of Legends.exe");

	inline static const wchar_t* ModuleName = VMPSTRW(L"LeagueCheat.Core.dll");

	inline static std::string DllPath;

	inline static DWORD ProcessId = 0;

	inline static HANDLE ProcessHandle = 0;

	inline static TCPSocket* IOClient;

	static bool Initialize();

	static void GetDllPath();

	static void GetGameProcess();

	static bool ScanHook(HANDLE hProcess, std::string moduleName, std::string funcName);

	static void AwaitGameLoad();

	static bool IsDllInjected();

	static void InjectDll();

	static void AwaitGameClose();

	static void InjectThread();
};