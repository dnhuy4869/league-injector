#pragma once

#include <Windows.h>
#include <vector>
#include <string>
#include <unordered_map>

#include "./VMProtect.h"
#include "./Definitions.h"
#include "./Utilities.h"

typedef struct _WIN32_HOOK_NAME
{
	std::string ModuleName;
	std::string FunctionName;

} WIN32_HOOK_NAME, * PWIN32_HOOK_NAME;

typedef struct _WIN32_HOOK_DATA
{
	DWORD FunctionAddress;
	std::string ModuleName;
	std::string FunctionName;
	BYTE OriginalBytes[16];
	BYTE HookBytes[16];

} WIN32_HOOK_DATA, * PWIN32_HOOK_DATA;

class Win32Hook abstract final
{
	private:

	inline static std::vector<WIN32_HOOK_NAME> m_HookNames =
	{
		{
			VMPSTRA("ntdll.dll"),
			VMPSTRA("NtCreateSection")
		},
		{
			VMPSTRA("ntdll.dll"),
			VMPSTRA("NtContinue")
		},
		{
			VMPSTRA("ntdll.dll"),
			VMPSTRA("NtTestAlert")
		},
		/*{
			VMPSTRA("ntdll.dll"),
			VMPSTRA("NtCreateThread")
		},
		{
			VMPSTRA("ntdll.dll"),
			VMPSTRA("NtCreateThreadEx")
		},
		{
			VMPSTRA("ntdll.dll"),
			VMPSTRA("LdrInitializeThunk")
		},*/
	};

	inline static std::unordered_map<std::string, WIN32_HOOK_DATA*> m_AllHooks;

	inline static HANDLE m_hProcess;

	public:

	static bool Initialize(HANDLE hProcess);

	static bool Dispose();

	static bool AddHookName(std::string moduleName, std::string functionName);

	static bool GetBytesCode(HANDLE hProcess, WIN32_HOOK_DATA* pHookData);

	static bool AddWin32Hook(WIN32_HOOK_DATA* pHookData);

	static WIN32_HOOK_DATA* GetWin32Hook(std::string functionName);

	static bool RestoreHook(std::string functionName);

	static bool PlaceHook(std::string functionName);
};