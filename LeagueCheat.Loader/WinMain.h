#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <strsafe.h>
#include <cstdio>
#include <string>
#include <vector>
#include <codecvt>
#include <TlHelp32.h>
#include <shlobj_core.h>
#include <sstream>
#include <stdio.h>
#include <time.h>
#include <iomanip>
#include <shellapi.h>
#include <ctime>
#include <random>
#include <functional> 
#include <algorithm> 
#include <psapi.h>
#include <thread>
#include <mutex>
#include <assert.h>
#include <dwmapi.h>
#include <shlwapi.h>
#include <math.h>
#include <windef.h>
#include <map>

#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "urlmon.lib")
#pragma comment(lib, "ntdll.lib")

#include "./Dependencies/xorstr.hpp"

const bool IS_DEBUG = true;
const DWORD LOADER_VERSION = 1000;
const std::string GAME_VERSION = "Version 12.9.439.127 [PUBLIC]";
const std::string PROJECT_ID = xorstr_("623d2aa37790f51bd9d6004c");
const std::string WEB_ENDPOINT = xorstr_("http://sockethax.com");
const std::string API_ENDPOINT = xorstr_("http://api-socket.xyz/hax");
const std::string API_KEY = xorstr_("JaGKsVn7qbsLrhXjbTZnpUptAfGh2Kvr");
const std::string SERVER_ENDPOINT = xorstr_("45.77.251.76");
const std::string LOCALHOST_ENDPOINT = xorstr_("127.0.0.1");