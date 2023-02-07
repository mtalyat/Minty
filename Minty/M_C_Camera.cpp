#include "pch.h"
#include "M_C_Camera.h"
#include "M_Screen.h"

void minty::Camera::setCenter(float const x, float const y, Screen* const screen)
{
	setOffset(math_floorToInt(-x * screen->width), math_floorToInt(-y * screen->height));
}

void minty::Camera::setOffset(int const x, int const y)
{
	offsetX = x;
	offsetY = y;
}
