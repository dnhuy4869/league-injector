#include "./Menu.h"
#include "../Core/Core.h"

extern class Core* Core;
extern class D3DX9* D3DX9;
extern class PopupWindow* PopupWindow;

extern void RenderWindow();
extern void HandleWindow();

void Menu::SetLoginStatus(std::string status, ImColor color)
{
	this->LoginStatus = status;
	this->LoginStatusColor = color;
}

void Menu::RenderLogin()
{
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2(this->Width, this->Height));
	ImGui::Begin(
		xorstr_("###loginWindow"),
		0,
		ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollWithMouse |
		ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBringToFrontOnFocus
	);

	ImDrawList* pImDraw = ImGui::GetForegroundDrawList();

	ImVec2 windowPos = ImGui::GetWindowPos();
	ImVec2 windowSize = ImGui::GetWindowSize();

	pImDraw->AddCircleFilled(
		ImVec2((windowSize.x * 0.5) - 20, windowPos.y + 16),
		6,
		ImColor(250, 91, 75),
		360
	);
	pImDraw->AddCircleFilled(
		ImVec2((windowSize.x * 0.5), windowPos.y + 16),
		6,
		ImColor(255, 191, 56),
		360
	);
	pImDraw->AddCircleFilled(
		ImVec2((windowSize.x * 0.5) + 20, windowPos.y + 16),
		6,
		ImColor(108, 240, 83),
		360
	);

	float posX = (windowSize.x - 480.0f) * 0.5;

	ImGui::SetCursorPos(ImVec2(posX, 40.0f));
	ImGui::TextColored(this->LoginStatusColor, this->LoginStatus.c_str());

	ImGui::SetCursorPos(ImVec2(posX, 70.0f));
	ImGui::SetNextItemWidth(480.0f);
	ImGui::InputText(
		xorstr_("###inputKey"),
		this->AuthKey,
		IM_ARRAYSIZE(this->AuthKey),
		ImGuiInputTextFlags_Password | ImGuiInputTextFlags_AutoSelectAll
	);

	ImGui::SetCursorPos(ImVec2(posX, 108.0f));
	ImGui::BeginGroup();
	if (ImGui::Button(xorstr_("Buy key###btnBuyKey"), ImVec2(236.0f, 40.0f)))
	{
		ShellExecuteA(NULL, xorstr_("open"), this->DiscordLink.c_str(), NULL, NULL, SW_HIDE);
	}

	ImGui::SameLine();

	if (ImGui::Button(xorstr_("Login###btnLogin"), ImVec2(236.0f, 40.0f)))
	{
		if (!this->IsLogging)
		{
			this->hHandle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)HandleWindow, 0, 0, 0);
			this->IsLogging = true;
		}
	}
	ImGui::EndGroup();

	ImGui::End();
}

void Menu::HandleLogin()
{
	WritePrivateProfileStringA(
		xorstr_("Core"),
		xorstr_("AuthKey"), 
		this->AuthKey, 
		Core->ConfigPath.c_str()
	);

	this->SetLoginStatus(xorstr_("Waiting reponse from server..."), D3DX9->Color.Orange400);

	Sleep(500);

	/*this->SetLoginStatus(xorstr_("An error occur when executing request"), D3DX9->Color.Red600);
	IsLogging = false;*/

	this->SetLoginStatus(xorstr_("Activated successfully, starting..."), D3DX9->Color.Green500);

	Sleep(500);

	this->ConsoleMessages.clear();

	TerminateThread(this->hRender, 0);
	PopupWindow->Hide();

	Core->IsImGuiCreated = false;

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	D3DX9->Cleanup();

	PopupWindow->Width = 600.0f;
	PopupWindow->Height = 350.0f;
	this->Width = PopupWindow->Width;
	this->Height = PopupWindow->Height;
	this->IsSplashPhase = false;
	this->IsLoginPhase = false;

	PopupWindow->Show();
	PopupWindow->Resize(PopupWindow->Width, PopupWindow->Height);

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

	this->hRender = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)RenderWindow, 0, 0, 0);
	this->hHandle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)HandleWindow, 0, 0, 0);

	Core->IsLoginSuccess = true;
	IsLogging = false;
}