#pragma once

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

class Core abstract final
{
	private:

	public:

	inline static std::string DllPath;

	inline static DWORD ProcessId = 0;

	inline static HANDLE ProcessHandle = 0;

	static bool Initialize();

	static void GetDllPath();

	static void GetGameProcess();

	static bool ScanHook(HANDLE hProcess, std::string moduleName, std::string funcName);

	static void AwaitGameLoad();

	static void InjectDll();

	static void AwaitGameClose();

	static void InjectThread();
};