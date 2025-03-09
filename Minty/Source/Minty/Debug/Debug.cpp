#include "pch.h"
#include "Debug.h"

void Minty::Debug::set_foreground_color(Color const color)
{
	std::cout << "\033[" << static_cast<int>(color) << "m";
}

void Minty::Debug::set_background_color(Color const color)
{
	std::cout << "\033[" << static_cast<int>(color) + 10  << "m";
}

void Minty::Debug::reset()
{
	std::cout << "\033[0m";
}
