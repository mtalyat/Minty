#pragma once

/**
 * @file Windows_Window.h
 * @brief Windows-specific implementation of the Window class, responsible for creating and managing a window on the Windows platform for rendering and user interaction.
 * @author Mitchell Talyat
 */

#include "Core/Type/Int2.h"
#include "Library/GLFW/GLFW.h"

namespace Minty
{
    struct Windows_WindowData
    {
        GLFWwindow *p_window;
        Int2 restorePosition;
        Int2 restoreSize;
    };
}
