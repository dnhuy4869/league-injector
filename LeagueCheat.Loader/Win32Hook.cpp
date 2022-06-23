#include "./Win32Hook.h"

bool Win32Hook::Initialize(HANDLE hProcess)
{
	m_hProcess = hProcess;

	for (WIN32_HOOK_NAME hookName : m_HookNames)
	{
		WIN32_HOOK_DATA* pHookData = new WIN32_HOOK_DATA();
		pHookData->ModuleName = hookName.ModuleName;
		pHookData->FunctionName = hookName.FunctionName;

		GetBytesCode(hProcess, pHookData);

		AddWin32Hook(pHookData);
	}

	return true;
}

bool Win32Hook::Dispose()
{
	m_hProcess = 0;

	for (auto& [function, pHookData] : m_AllHooks)
	{
		SAFE_DELETE_PTR(pHookData);
	}

	m_AllHooks.clear();

	return true;
}

bool Win32Hook::AddHookName(std::string moduleName, std::string functionName)
{
	m_HookNames.push_back({ moduleName, functionName });

	return true;
}

bool Win32Hook::GetBytesCode(HANDLE hProcess, WIN32_HOOK_DATA* pHookData)
{
	pHookData->FunctionAddress = Utilities::GetExportedFunction(pHookData->ModuleName, pHookData->FunctionName);
	if (pHookData->FunctionAddress <= 0)
	{
		return false;
	}

	const int HOOK_BYTES = 16;

	ZeroMemory(pHookData->OriginalBytes, HOOK_BYTES);
	ZeroMemory(pHookData->HookBytes, HOOK_BYTES);

	memcpy(pHookData->OriginalBytes, (void*)pHookData->FunctionAddress, HOOK_BYTES);
	ReadProcessMemory(hProcess,
					  (void*)pHookData->FunctionAddress,
					  pHookData->HookBytes,
					  HOOK_BYTES,
					  nullptr);

	return true;
}

bool Win32Hook::AddWin32Hook(WIN32_HOOK_DATA* pHookData)
{
	return m_AllHooks.insert(std::pair<std::string, WIN32_HOOK_DATA*>(pHookData->FunctionName, pHookData)).second;
}

WIN32_HOOK_DATA* Win32Hook::GetWin32Hook(std::string functionName)
{
	return m_AllHooks[functionName];
}

bool Win32Hook::RestoreHook(std::string functionName)
{
	WIN32_HOOK_DATA* pHookData = GetWin32Hook(functionName);

	Utilities::WriteProtected(m_hProcess,
					   (void*)pHookData->FunctionAddress, 
					   pHookData->OriginalBytes, 
					   sizeof(pHookData->OriginalBytes));

	return true;
}

bool Win32Hook::PlaceHook(std::string functionName)
{
	WIN32_HOOK_DATA* pHookData = GetWin32Hook(functionName);

	Utilities::WriteProtected(m_hProcess,
					   (void*)pHookData->FunctionAddress, 
					   pHookData->HookBytes, 
					   sizeof(pHookData->HookBytes));

	return true;
}