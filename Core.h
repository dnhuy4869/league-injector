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

#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "urlmon.lib")

enum class CmdOption : int
{
	Unknown,
	InjectCore,
	DumpProcess,
	DumpOffsets,
};

class Core abstract final
{
	private:

	inline static CmdOption m_CmdOption = CmdOption::InjectCore;

	inline static const wchar_t* m_TargetName = VMPSTRW(L"League of Legends.exe");

	inline static const wchar_t* m_ModuleName = VMPSTRW(L"LeagueCheat.Core.dll");

	inline static UDPSocket* m_ConsoleServer;

	inline static HANDLE m_hMessageLoop;

	public:

	static bool Initialize();

	static bool ConsoleServer();

	static void ConsoleLog();

	static void SelectOption();

	static bool InjectDll(DWORD procId, const std::string& dllPath);

	static void InjectLoop();
};