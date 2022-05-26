#include "./PopupWindow.h"

PopupWindow::PopupWindow(LPCWSTR className, LPCWSTR windowName)
{
	this->ClassName = className;
	this->WindowName = windowName;
}

bool PopupWindow::Create(HINSTANCE hInstance, WNDPROC pWndProc, float width, float height)
{
	this->hInstance = hInstance;
	this->Width = width;
	this->Height = height;

	HWND hDesktop = GetDesktopWindow();
	RECT rect;
	GetWindowRect(hDesktop, &rect);

	WNDCLASSEXW wc;
	ZeroMemory(&wc, sizeof(wc));
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.lpfnWndProc = pWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(wc.hInstance, MAKEINTRESOURCE(IDI_1));
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = 0;
	wc.lpszMenuName = this->WindowName;
	wc.lpszClassName = this->ClassName;
	wc.hIconSm = LoadIcon(wc.hInstance, MAKEINTRESOURCE(IDI_2));

	float left = 0;
	float top = 0;

	for (float i = 0; i < (rect.right - rect.left); ++i)
	{
		if ((i + (this->Width / 2.0f)) == ((rect.right - rect.left) / 2.0f))
		{
			left = i;
			break;
		}
	}

	for (float i = 0; i < (rect.bottom - rect.top); ++i)
	{
		if ((i + (this->Height / 2.0f)) == ((rect.bottom - rect.top) / 2.0f))
		{
			top = i;
			break;
		}
	}

	RegisterClassEx(&wc);
	this->hWindow = CreateWindowW(this->ClassName, this->WindowName, WS_POPUP, left, top, this->Width, this->Height, NULL, NULL, wc.hInstance, NULL);
	if (this->hWindow == 0x0)
	{
		return false;
	}

	return true;
}

void PopupWindow::Cleanup() 
{
	DestroyWindow(this->hWindow);
	UnregisterClass(this->ClassName, this->hInstance);
}

void PopupWindow::Show()
{
	ShowWindow(this->hWindow, SW_SHOW);
	UpdateWindow(this->hWindow);
}

void PopupWindow::Hide()
{
	ShowWindow(this->hWindow, SW_HIDE);
}

void PopupWindow::Resize(float width, float height)
{
	this->Width = width;
	this->Height = height;

	HWND hDesktop = GetDesktopWindow();
	RECT rect;
	GetWindowRect(hDesktop, &rect);

	float left = 0;
	float top = 0;

	for (float i = 0; i < (rect.right - rect.left); ++i)
	{
		if ((i + (this->Width / 2.0f)) == ((rect.right - rect.left) / 2.0f))
		{
			left = i;
			break;
		}
	}

	for (float i = 0; i < (rect.bottom - rect.top); ++i)
	{
		if ((i + (this->Height / 2.0f)) == ((rect.bottom - rect.top) / 2.0f))
		{
			top = i;
			break;
		}
	}

	MoveWindow(this->hWindow, left, top, width, height, TRUE);
}