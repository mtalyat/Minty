#ifndef MINTY_LIBRARY_GLFW_H
#define MINTY_LIBRARY_GLFW_H

#include "Minty/Core/Macro.h"

#ifdef MINTY_WINDOWS
#include <Windows.h>
#endif // MINTY_WINDOWS

#ifdef MINTY_VULKAN
#define GLFW_INCLUDE_VULKAN
#endif // MINTY_VULKAN

#include <GLFW/glfw3.h>

#endif // MINTY_LIBRARY_GLFW_H