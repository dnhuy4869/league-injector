#include "./Menu.h"

void Menu::Render()
{
	if (this->IsSplashPhase)
	{
		this->RenderSplash();
	}
	else if (this->IsLoginPhase)
	{
		this->RenderLogin();
	}
	else
	{
		this->RenderConsole();
	}
}

void Menu::Handle()
{
	if (this->IsSplashPhase)
	{
		this->HandleSplash();
	}
	else if (this->IsLoginPhase)
	{
		this->HandleLogin();
	}
	else
	{
		this->HandleConsole();
	}
}

void Menu::Print(std::string message, ImColor color)
{
	CONSOLE_MESSAGE consoleMess;
	consoleMess.message = message;
	consoleMess.color = color;
	this->ConsoleMessages.push_back(consoleMess);
	this->IsConsoleScroll = true;
}

void Menu::Print(CONSOLE_MESSAGE message)
{
	this->ConsoleMessages.push_back(message);
	this->IsConsoleScroll = true;
}