#pragma once

#include "../WinMain.h"
#include "../PopupWindow/PopupWindow.h"
#include "../Dependencies/imgui_ex/imgui_ex.h"
#include "../Utilities/Utilities.h"
#include "../D3DX9/D3DX9.h"
#include "../Resources/Roboto.h"
#include "../Resources/FontAwesome.h"
#include "../Menu/Menu.h"
#include "../Driver/Driver.h"

class Core
{
public:

	void ExitFailed(const char* log);

	std::string ArialUniPath;
	std::string RobotoPath;
	std::string FontAwesomePath;
	std::string ConfigPath;
	std::string CorePath;
	std::string ServicePath;

	void CreateResources();

	bool IsImGuiCreated = false;

	bool IsLoginSuccess = false;

	DWORD ProcessId = 0x0;
	HANDLE hProcess = 0x0;

	bool IsSectionProtected();

	void WriteProtected(DWORD addr, void* value, size_t size);
	bool ScanHook(HANDLE hProcess, LPCSTR ModuleName, LPCSTR FuncName);
	bool RestoreNtdll();
};