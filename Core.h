#pragma once

#include <Console.h>
#include <Windows.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <filesystem>
#include <shlobj_core.h>
#include <istream>
#include <fstream>
#include <shellapi.h>
#include <shlwapi.h>
#include <Utilities.h>
#include <Winsock/UDPSocket.h>
#include <Common/VersionInfo.h>
#include <Winsock/TCPSocket.h>

#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "urlmon.lib")

enum class CmdOption : int
{
	Unknown,
	InjectCore,
	DumpProcess,
	DumpOffsets,
	DumpSkinHash,
	DumpSpellDatabase,
};

void TimeoutSocket();

class Core abstract final
{
	private:

	inline static CmdOption m_CmdOption = CmdOption::InjectCore;

	inline static const wchar_t* m_TargetName = VMPSTRW(L"League of Legends.exe");

	inline static const wchar_t* m_ModuleName = VMPSTRW(L"LeagueCheat.Core.dll");

	inline static UDPSocket* m_ConsoleServer;

	inline static TCPSocket* m_DllClient;

	inline static HANDLE m_hMessageLoop;

	inline static DWORD m_LoaderServerVersion = 0;

	inline static DWORD m_CoreServerVersion = 0;

	inline static std::string m_VersionJsonPath;

	inline static std::string m_DllPath;

	inline static DWORD m_GameTimeOffset = 0x0;

	inline static DWORD m_ProcessId = 0;

	inline static HANDLE m_ProcessHandle = 0;

	inline static bool m_bSendCommand = false;

	public:

	friend void TimeoutSocket();

	static bool Initialize();

	static bool ConsoleServer();

	static void ConsoleLog();

	static void SelectOption();

	static void GetDllPath();

	static bool GetServerVersion();

	static void CheckLoaderVersion();

	static void CheckDllVersion();

	static bool GetGameTimeOffset();

	static void AwaitProcess();

	static void AwaitGameLoad();

	static bool IsDllInjected();

	static void AwaitGameClose();

	static bool InjectDll_CreateThread(DWORD procId, const std::string& dllPath);

	static bool InjectDll_HijackThread(DWORD procId, const std::string& dllPath);

	static void InjectLoop();
};