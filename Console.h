#pragma once

#include <iostream>

#include "./ThirdParty/io_color.h"
#include "./Common/VMProtect.h"

enum class ConsoleColor
{
	Yellow,
	Red,
	Green,
	Blue,
	Cyan,
	Magenta,
	White,
};

class Console abstract final
{
	public:

	static void Setup(std::string title);

	static void Log(std::string log);

	static void Log(std::string log, ConsoleColor color);

	static void Pause();

	static void Clear();
};