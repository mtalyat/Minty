#include "pch.h"
#include "Console.h"

void Minty::Console::set_foreground_color(Color const color)
{
	std::cout << "\033[" << static_cast<int>(color) << "m";
}

void Minty::Console::set_background_color(Color const color)
{
	std::cout << "\033[" << static_cast<int>(color) + 10  << "m";
}

void Minty::Console::reset()
{
	std::cout << "\033[0m";
}
