#pragma once

#include "Platform/Type/Primitive.hpp"
#include "Core/Type/Int2.hpp"
#include "Core/Data/StringView.hpp"

namespace Minty
{
    struct KeyboardState;
    struct MouseState;
    struct GamepadState;

    class Platform
    {
#pragma region Constructor

    public:
        Platform() = delete;

#pragma endregion

#pragma region Method

    public:
        // Initialize the platform
        static void initialize();
        static void shutdown();

        static void process_events();
        static void sync();

#pragma endregion
    };
}