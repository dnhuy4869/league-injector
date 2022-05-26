#pragma once

#include "../WinMain.h"
#include "../Dependencies/imgui_ex/imgui_ex.h"

struct CONSOLE_MESSAGE
{
	std::string message;
	ImColor color;
};

class Menu
{
public:

	HANDLE hRender;
	HANDLE hHandle;

	float Width = 600.0f;
	float Height = 350.0f;

	bool IsSplashPhase = false;
	bool IsLoginPhase = false;

	void Render();
	void Handle();

	bool IsConsoleScroll = false;
	std::vector<CONSOLE_MESSAGE> ConsoleMessages;
	void Print(std::string message, ImColor color = ImColor(255, 255, 255));
	void Print(CONSOLE_MESSAGE message);

	void RenderSplash();
	void HandleSplash();

	std::string DiscordLink = "https://discord.gg/XxYa32xAGx";
	std::string TelegramLink = "https://t.me/+UBD0dWOWWhMyODI1";

	std::string LoginStatus = xorstr_("Join discord for latest update");
	ImColor LoginStatusColor = ImColor(226, 232, 240);
	char AuthKey[50];
	bool IsLogging = false;

	void SetLoginStatus(std::string status, ImColor color = ImColor(226, 232, 240));

	void RenderLogin();
	void HandleLogin();

	void RenderConsole();
	void HandleConsole();
};