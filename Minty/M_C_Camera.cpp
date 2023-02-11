#include "pch.h"
#include "M_C_Camera.h"
#include "M_Screen.h"

void minty::Camera::setCenter(float const x, float const y, Screen* const screen)
{
	setOffset(-x * screen->width, -y * screen->height);
}

void minty::Camera::setOffset(float const x, float const y)
{
	offsetX = x;
	offsetY = y;
}
