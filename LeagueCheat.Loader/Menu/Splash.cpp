#include "./Menu.h"
#include "../Core/Core.h"

extern class Core* Core;
extern class PopupWindow* PopupWindow;
extern class D3DX9* D3DX9;

void Menu::RenderSplash()
{
	ImGuiIO& io = ImGui::GetIO();

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2(this->Width, this->Height));
	ImGui::Begin(
		"###consoleWindow",
		0,
		ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBringToFrontOnFocus
	);

	ImDrawList* pImDraw = ImGui::GetForegroundDrawList();

	ImVec2 windowPos = ImGui::GetWindowPos();
	ImVec2 windowSize = ImGui::GetWindowSize();

	pImDraw->AddCircleFilled(
		ImVec2(windowPos.x + (windowSize.x * 0.5) - 20, windowPos.y + 16),
		6,
		ImColor(250, 91, 75),
		360
	);
	pImDraw->AddCircleFilled(
		ImVec2(windowPos.x + (windowSize.x * 0.5), windowPos.y + 16),
		6,
		ImColor(255, 191, 56),
		360
	);
	pImDraw->AddCircleFilled(
		ImVec2(windowPos.x + (windowSize.x * 0.5) + 20, windowPos.y + 16),
		6,
		ImColor(108, 240, 83),
		360
	);

	ImGui::SetCursorPos(ImVec2(15, 32));
	ImGui::BeginChild(
		"###menuConsole",
		ImVec2(this->Width - 30.0f, this->Height - 46.0f),
		false,
		ImGuiWindowFlags_AlwaysVerticalScrollbar
	);

	if (ImGui::BeginTable("###tblConsole", 3))
	{
		ImGui::TableSetupColumn("###col1", ImGuiTableColumnFlags_WidthFixed, 4.0f);
		ImGui::TableSetupColumn("###col2");
		ImGui::TableSetupColumn("###col3", ImGuiTableColumnFlags_WidthFixed, 4.0f);

		ImGui::TableNextRow();
		ImGui::TableNextColumn();

		ImGui::TableNextColumn();

		for (CONSOLE_MESSAGE message : this->ConsoleMessages)
		{
			ImGui_Ex::TextWrappedColored(message.color, message.message.c_str());
		}

		ImGui::TableNextColumn();

		ImGui::EndTable();
	}

	if (this->IsConsoleScroll == true)
	{
		ImGui::SetScrollHereY(1.0f);
		this->IsConsoleScroll = false;
	}

	ImGui::EndChild();

	ImGui::End();
}

extern void RenderWindow();

void Menu::HandleSplash()
{
	Sleep(500);

	this->Print("Checking version...", D3DX9->Color.Orange400);

	this->Print("Checking resources...", D3DX9->Color.Orange400);

	this->Print("Checking core...", D3DX9->Color.Orange400);

	Sleep(500);

	TerminateThread(this->hRender, 0);
	PopupWindow->Hide();

	Core->IsImGuiCreated = false;

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	D3DX9->Cleanup();

	PopupWindow->Width = 500.0f;
	PopupWindow->Height = 160.0f;
	this->Width = PopupWindow->Width;
	this->Height = PopupWindow->Height;
	this->IsSplashPhase = false;
	this->IsLoginPhase = true;

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
}