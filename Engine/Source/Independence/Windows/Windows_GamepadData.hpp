#pragma once

/**
 * @file GamepadData.h
 * @brief Header file defining the GamepadData struct, which encapsulates the state of a gamepad connected to a Windows_Window.
 * @author Mitchell Talyat
 */

#include "Library/GLFW/GLFW.hpp"
#include "Platform/Type/Primitive.hpp"

namespace Minty
{
    struct GamepadData
    {
        GLFWgamepadstate state;
        Char const *name;
    };
}