#include "./Console.h"

void Console::Setup(std::string title)
{
	HWND hConsoleWindow = GetConsoleWindow();
	HMENU hSysMenu = GetSystemMenu(hConsoleWindow, FALSE);

	SetConsoleTitleA(title.c_str());

	// Disable size control for console window
	DWORD dwStyle = GetWindowLong(hConsoleWindow, GWL_STYLE);
	dwStyle &= ~WS_MAXIMIZEBOX;
	SetWindowLong(hConsoleWindow, GWL_STYLE, dwStyle);
	DeleteMenu(hSysMenu, SC_SIZE, MF_BYCOMMAND);

	// Disable input for console window 
	HANDLE hConsoleInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD PreviousMode;
	GetConsoleMode(hConsoleInput, &PreviousMode);
	SetConsoleMode(hConsoleInput, ENABLE_EXTENDED_FLAGS | (PreviousMode & ~ENABLE_QUICK_EDIT_MODE));
}

void Console::Log(std::string log)
{
	std::cout << log << std::endl;
}

void Console::Log(std::string log, ConsoleColor color)
{
	switch (color)
	{
		case ConsoleColor::Yellow:
		{
			std::cout << io_color::yellow;
			break;
		}
		case ConsoleColor::Red:
		{
			std::cout << io_color::red;
			break;
		}
		case ConsoleColor::Green:
		{
			std::cout << io_color::green;
			break;
		}
		case ConsoleColor::Blue:
		{
			std::cout << io_color::blue;
			break;
		}
		case ConsoleColor::Cyan:
		{
			std::cout << io_color::cyan;
			break;
		}
		case ConsoleColor::Magenta:
		{
			std::cout << io_color::magenta;
			break;
		}
		case ConsoleColor::White:
		{
			std::cout << io_color::white;
			break;
		}
		default:
		{
			std::cout << io_color::white;
			break;
		}
	}

	std::cout << VMPSTRA("[+] ") << log << std::endl;
}

void Console::Pause()
{
	system(VMPSTRA("pause >nul"));
}