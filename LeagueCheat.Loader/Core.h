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

	//inline static const wchar_t* TargetName = VMPSTRW(L"hackme-x86.exe");
	//inline static const wchar_t* TargetName = VMPSTRW(L"example_win32_directx9.exe");
	inline static const wchar_t* TargetName = VMPSTRW(L"League of Legends.exe");

	inline static const wchar_t* ModuleName = VMPSTRW(L"LeagueCheat.Core.dll");

	inline static bool m_bSendCommand = false;

	inline static std::string DllPath;

	inline static DWORD GameTimeOffset = 0x0;

	inline static DWORD ProcessId = 0;

	inline static HANDLE ProcessHandle = 0;

	inline static DWORD LeagueBase = 0;

	inline static TCPSocket* IOClient;

	inline static HANDLE hMessageThread;

	static bool Initialize();

	static void GetDllPath();

	static bool GetGameTimeOffset();

	static void GetGameProcess();

	static void AwaitGameLoad();

	static bool IsDllInjected();

	static void NormalLoadLibrary();

	static void ShellcodeLoadLibrary();

	static void IOConnect();

	static void PrintMessage();

	static void AwaitGameClose();

	static void InjectThread();
};