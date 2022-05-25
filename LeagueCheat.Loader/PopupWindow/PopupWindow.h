#pragma once

#include "../WinMain.h";
#include "../Resources/Resources.h"
#include "../Dependencies/imgui_ex/imgui_ex.h"

class PopupWindow {
public:

	HWND hWindow;

	LPCWSTR ClassName;
	LPCWSTR WindowName;
	HINSTANCE hInstance;

	float Width;
	float Height;

	bool IsDestroyed = false;

	PopupWindow(LPCWSTR className, LPCWSTR windowName);

	bool Create(HINSTANCE hInstance, WNDPROC pWndProc, float width, float height);

	void Cleanup();

	void Show();

	void Hide();

	void Resize(float width, float height);
};