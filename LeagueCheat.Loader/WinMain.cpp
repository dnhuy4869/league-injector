#include "./WinMain.h"
#include "./Resources/Resources.h"
#include "./Core/Core.h"

class Core* Core;
class PopupWindow* PopupWindow;
Utilities* Utils;

void OnLoad()
{
	Core = new class Core();
	PopupWindow = new class PopupWindow(xorstr_(L"LoaderPopupClass"), xorstr_(L"Loader"));
	Utils = new Utilities();
}

void OnUnload()
{
	delete Utils;
	delete PopupWindow;
	delete Core;
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT WINAPI PopupWndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (Core->IsImGuiCreated)
	{
		if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
			return true;
	}

	switch (msg)
	{
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU)
			return 0;
		break;
	case WM_QUIT:
		ExitProcess(WM_QUIT);
		return 0;
	case WM_CLOSE:
		ExitProcess(WM_CLOSE);
		return 0;
	case WM_DESTROY:
		ExitProcess(WM_DESTROY);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPreviousInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	OnLoad();

	CHAR szBuffer[MAX_PATH];
	GetFullPathNameA(xorstr_("Loader_old_3304.exe"), sizeof(szBuffer), szBuffer, nullptr);
	std::string oldLoaderPath = szBuffer;
	if (PathFileExistsA(oldLoaderPath.c_str()))
	{
		_unlink(oldLoaderPath.c_str());
	}

	CHAR szExeFileName[MAX_PATH];
	GetModuleFileNameA(NULL, szExeFileName, sizeof(szExeFileName));
	std::string fileName = Utils->GetFileName(szExeFileName);
	if (Utils->IsProcessRunning(Utils->string_to_wstring(fileName).c_str()))
	{
		Core->ExitFailed(xorstr_("Process is already running"));
	}

	PopupWindow->Width = 600.0f;
	PopupWindow->Height = 350.0f;

	if (!PopupWindow->Create(hInstance, PopupWndProc, PopupWindow->Width, PopupWindow->Height))
	{
		Core->ExitFailed(xorstr_("Create window failed"));
	}

	PopupWindow->Show();

	while (true)
	{
		Sleep(10);
	}

	OnUnload();
	return 0;
}