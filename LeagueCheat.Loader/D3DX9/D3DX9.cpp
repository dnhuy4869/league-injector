#include "./D3DX9.h"

bool D3DX9::Create(HWND hWindow)
{
	if ((this->pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
	{
		return false;
	}

	ZeroMemory(&this->d3dpp, sizeof(this->d3dpp));
	this->d3dpp.Windowed = TRUE;
	this->d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	this->d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	this->d3dpp.EnableAutoDepthStencil = TRUE;
	this->d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	this->d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

	if (this->pD3D->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL, 
		hWindow,
		D3DCREATE_HARDWARE_VERTEXPROCESSING, 
		&this->d3dpp,
		&this->pDevice
	) < 0)
	{
		return false;
	}

	this->pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	this->pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	this->pDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);

	return true;
}

void D3DX9::Cleanup()
{
	if (this->pDevice) { this->pDevice->Release(); this->pDevice = NULL; }
	if (this->pD3D) { this->pD3D->Release(); this->pD3D = NULL; }
}

void D3DX9::BeginDraw()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	this->pImDraw = ImGui::GetBackgroundDrawList();
}

void D3DX9::EndDraw()
{
	ImGui::EndFrame();
	this->pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);

	if (this->pDevice->BeginScene() >= 0)
	{
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		this->pDevice->EndScene();
	}
	
	this->pDevice->Present(NULL, NULL, NULL, NULL);
}

void D3DX9::Reset()
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	this->pDevice->Reset(&this->d3dpp);
	ImGui_ImplDX9_CreateDeviceObjects();

	this->pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	this->pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	this->pDevice->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);
}

void D3DX9::DrawLine(float x1, float y1, float x2, float y2, ImColor color, float thickness)
{
	this->pImDraw->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), color, thickness);
}

void D3DX9::DrawCircle(float x, float y, float radius, ImColor color, float thickness)
{
	this->pImDraw->AddCircle(ImVec2(x, y), radius, color, 0, thickness);
}

void D3DX9::DrawRect(float x, float y, float width, float height, ImColor color, float thickness)
{
	this->pImDraw->AddRect(ImVec2(x, y), ImVec2(x + width, y + height), color, 0, 0, thickness);
}

void D3DX9::DrawFilledRect(float x, float y, float width, float height, ImColor color)
{
	this->pImDraw->AddRectFilled(ImVec2(x, y), ImVec2(x - width, y - height), color);
}

void D3DX9::DrawString(float fontSize, std::string text, float x, float y, ImColor color)
{
	ImVec2 textSize = this->pRenderFont->CalcTextSizeA(fontSize, FLT_MAX, 0.0f, text.c_str());
	this->pImDraw->AddText(
		this->pRenderFont, fontSize,
		ImVec2(x - textSize.x / 2.0f + 1.0f, y + 1.0f),
		this->Color.Black, 
		text.c_str()
	);
	this->pImDraw->AddText(
		this->pRenderFont,
		fontSize, 
		ImVec2(x - textSize.x / 2.0f - 1.0f, y - 1.0f),
		this->Color.Black, 
		text.c_str()
	);
	this->pImDraw->AddText(
		this->pRenderFont, 
		fontSize, 
		ImVec2(x - textSize.x / 2.0f + 1.0f, y - 1.0f),
		this->Color.Black, 
		text.c_str()
	);
	this->pImDraw->AddText(
		this->pRenderFont, 
		fontSize, 
		ImVec2(x - textSize.x / 2.0f - 1.0f, y + 1.0f),
		this->Color.Black, 
		text.c_str()
	);
	this->pImDraw->AddText(
		this->pRenderFont, 
		fontSize, 
		ImVec2(x - textSize.x / 2.0f, y),
		color, 
		text.c_str()
	);
}

void D3DX9::DrawString(float fontSize, char* text, float x, float y, ImColor color)
{
	ImVec2 textSize = this->pRenderFont->CalcTextSizeA(fontSize, FLT_MAX, 0.0f, text);
	this->pImDraw->AddText(
		this->pRenderFont, fontSize,
		ImVec2(x - textSize.x / 2.0f + 1.0f, y + 1.0f),
		this->Color.Black,
		text
	);
	this->pImDraw->AddText(
		this->pRenderFont,
		fontSize,
		ImVec2(x - textSize.x / 2.0f - 1.0f, y - 1.0f),
		this->Color.Black,
		text
	);
	this->pImDraw->AddText(
		this->pRenderFont,
		fontSize,
		ImVec2(x - textSize.x / 2.0f + 1.0f, y - 1.0f),
		this->Color.Black,
		text
	);
	this->pImDraw->AddText(
		this->pRenderFont,
		fontSize,
		ImVec2(x - textSize.x / 2.0f - 1.0f, y + 1.0f),
		this->Color.Black,
		text
	);
	this->pImDraw->AddText(
		this->pRenderFont,
		fontSize,
		ImVec2(x - textSize.x / 2.0f, y),
		color,
		text
	);
}