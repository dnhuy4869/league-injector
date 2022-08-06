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

#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "urlmon.lib")

class Core abstract final
{
	public:

	static bool Initialize();
};