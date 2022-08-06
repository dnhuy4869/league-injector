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

	public:

	static bool Initialize();

	static void SelectOption();

	static bool InjectDll(DWORD procId, const std::string& dllPath);

	static void InjectLoop();
};