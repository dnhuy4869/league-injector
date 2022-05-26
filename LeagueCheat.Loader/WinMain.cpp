#include "./WinMain.h"
#include "./Resources/Resources.h"
#include "./Core/Core.h"

class Core* Core;
class PopupWindow* PopupWindow;
Utilities* Utils;
class D3DX9* D3DX9;
class Menu* Menu;
class Driver* Driver;

void OnLoad()
{
	Core = new class Core();
	PopupWindow = new class PopupWindow(L"LoaderPopupClass", L"Loader");
	Utils = new Utilities();
	D3DX9 = new class D3DX9();
	Menu = new class Menu();
	Driver = new class Driver("LeagueCheat", "\\\\.\\LeagueCheat");
}

void OnUnload()
{
	delete Driver;
	delete Menu;
	delete D3DX9;
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
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void RenderWindow()
{
	while (true)
	{
		Sleep(10);

		D3DX9->BeginDraw();

		Menu->Render();

		D3DX9->EndDraw();
	}
}

void HandleWindow()
{
	Menu->Handle();
}

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPreviousInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	OnLoad();

	CHAR szBuffer[MAX_PATH];
	GetFullPathNameA("Loader_old_3304.exe", sizeof(szBuffer), szBuffer, nullptr);
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

	Core->CreateResources();

	GetPrivateProfileStringA(
		xorstr_("Core"),
		xorstr_("AuthKey"),
		0, 
		Menu->AuthKey,
		sizeof(Menu->AuthKey), 
		Core->ConfigPath.c_str()
	);

	PopupWindow->Width = 600.0f;
	PopupWindow->Height = 350.0f;
	if (!PopupWindow->Create(hInstance, PopupWndProc, PopupWindow->Width, PopupWindow->Height))
	{
		Core->ExitFailed(xorstr_("Create window failed"));
	}

	PopupWindow->Show();

	if (!D3DX9->Create(PopupWindow->hWindow))
	{
		Core->ExitFailed(xorstr_("Create d3dx9 failed"));
	}

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = NULL;
	ImGui_Ex::StyleColorDarkSlate();
	ImGui_ImplWin32_Init(PopupWindow->hWindow);
	ImGui_ImplDX9_Init(D3DX9->pDevice);

	io.Fonts->AddFontFromFileTTF(Core->RobotoPath.c_str(), 20.0f);

	Core->IsImGuiCreated = true;

	Menu->Width = PopupWindow->Width;
	Menu->Height = PopupWindow->Height;
	Menu->IsSplashPhase = true;

	Menu->IsSplashPhase = false;
	Menu->IsLoginPhase = false;
	Menu->hRender = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)RenderWindow, 0, 0, 0);
	Menu->hHandle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)HandleWindow, 0, 0, 0);

	MSG msg;
	RECT rect;
	POINT point;

	while (true)
	{
		Sleep(10);

		if (!PopupWindow->IsDestroyed)
		{
			if (PeekMessage(&msg, PopupWindow->hWindow, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
			{
				GetWindowRect(PopupWindow->hWindow, &rect);
				GetCursorPos(&point);
				if (
					(point.x >= rect.left) && (point.y >= rect.top)
					&& (point.x <= (rect.left + PopupWindow->Width))
					&& (point.y <= (rect.top + 26.0f))
					)
				{
					ReleaseCapture();
					SendMessage(PopupWindow->hWindow, 0x112, 0xf012, 0);
				}
			}
		}
		else
		{
			Sleep(1000);
		}
	}

	D3DX9->Cleanup();
	PopupWindow->Cleanup();

	OnUnload();
	return 0;
}