#pragma once

#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include "../WinMain.h"
#include "../Dependencies/imgui_ex/imgui_ex.h"

struct D3DX9_COLOR
{
	ImColor White = ImColor(255, 255, 255);
	ImColor Black = ImColor(0, 0, 0);
	ImColor Red = ImColor(255, 0, 0);
	ImColor Green = ImColor(0, 255, 0);
	ImColor Blue = ImColor(0, 0, 255);
	ImColor Yellow = ImColor(255, 255, 0);
	ImColor Cyan = ImColor(0, 180, 255);
	ImColor Orange = ImColor(255, 165, 0);
	ImColor Maroon = ImColor(128, 0, 0);
	ImColor Magenta = ImColor(255, 0, 255);
	ImColor Olive = ImColor(128, 128, 0);
	ImColor Purple = ImColor(128, 0, 128);
	ImColor Chocolate = ImColor(255, 127, 36);
	ImColor Grey = ImColor(128, 128, 128);
	ImColor Grey400 = ImColor(156, 163, 175);
	ImColor Violet400 = ImColor(167, 139, 250);
	ImColor Violet500 = ImColor(139, 92, 246);
	ImColor Indigo500 = ImColor(99, 102, 241);
	ImColor GreenYellow = ImColor(173, 255, 47);
	ImColor Orange400 = ImColor(251, 146, 60);
	ImColor Red600 = ImColor(220, 38, 38);
	ImColor Green500 = ImColor(34, 197, 94);
};

class D3DX9
{
public:

	D3DX9_COLOR Color;

	LPDIRECT3D9 pD3D;
	LPDIRECT3DDEVICE9 pDevice;
	D3DPRESENT_PARAMETERS d3dpp;

	ImFont* pRootFont;
	ImFont* pRenderFont;
	ImFont* pIconFont;

	ImDrawList* pImDraw;

	bool Create(HWND hWindow);

	void Cleanup();

	void BeginDraw();

	void EndDraw();

	void Reset();

	void DrawLine(float x1, float y1, float x2, float y2, ImColor color, float thickness);

	void DrawCircle(float x, float y, float radius, ImColor color, float thickness);

	void DrawRect(float x, float y, float width, float height, ImColor color, float thickness);

	void DrawFilledRect(float x, float y, float width, float height, ImColor color);

	void DrawString(float fontSize, std::string text, float x, float y, ImColor color);

	void DrawString(float fontSize, char* text, float x, float y, ImColor color);
};