#include "platform.hpp"
#include "Library/GLFW/GLFW.hpp"
#include "Core/Debug/DebugF.hpp"
#include "Input/Key/KeyboardState.hpp"
#include "Input/Mouse/MouseState.hpp"
#include "Input/Gamepad/GamepadState.hpp"
#include "Input/Constant/Gamepad.hpp"
#include "Input/Manager/InputManager.hpp"

using namespace Minty;

static void GLFW_error_callback(int error_code, const char* description)
{
    MINTY_LOG_ERROR_F("GLFW Error {}: {}", error_code, description);
}

void Minty::Platform::initialize()
{
    // Initialize GLFW
    if (!glfwInit())
    {
        MINTY_ABORT(ErrorCodeEnum::Library_InitializationFailed);
    }
    glfwSetErrorCallback(GLFW_error_callback);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
}

void Minty::Platform::shutdown()
{
    // Terminate GLFW
    glfwTerminate();
}

void Minty::Platform::process_events()
{
    // Poll for and process events
    glfwPollEvents();

    // Update gamepad states
    InputManager& inputManager = InputManager::get_instance();
    for (Int i = 0; i < static_cast<Int>(MAX_GAMEPADS); ++i)
    {
        Bool connected = glfwJoystickPresent(i) == GLFW_TRUE;
        inputManager.set_gamepad_connected(i, connected);

        if (connected)
        {
            // Update buttons
            Int buttonCount;
            const UInt8* buttons = glfwGetJoystickButtons(i, &buttonCount);
            for (Int j = 0; j < buttonCount; ++j)
            {
                inputManager.set_gamepad_button(i, static_cast<GamepadButtonEnum>(j), buttons[j] == GLFW_PRESS);
            }

            // Update axes
            Int axisCount;
            const Float* axes = glfwGetJoystickAxes(i, &axisCount);
            for (Int j = 0; j < axisCount; ++j)
            {
                inputManager.set_gamepad_axis(i, static_cast<GamepadAxisEnum>(j), axes[j]);
            }
        }
    }
}

void Minty::Platform::sync()
{
    glfwWaitEvents();
}
