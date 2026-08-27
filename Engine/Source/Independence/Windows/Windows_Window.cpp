#include "Windows_Window.hpp"
#include "Core/Debug/DebugF.hpp"
#include "Window/Window/WindowInfo.hpp"
#include "Window/Window/Window.hpp"
#include "Input/Manager/InputManager.hpp"

using namespace Minty;

struct Windows_CallbackData
{
    Window *window;
};

Minty::Window::Impl::Impl(WindowInfo const &info, Window *const owner)
    : mp_owner(owner),
      mp_window(nullptr)
{
    // Create the GLFW window
    mp_window = glfwCreateWindow(
        info.size.x,
        info.size.y,
        info.title.get_data(),
        nullptr,  // Monitor
        nullptr); // Share
    MINTY_ASSERT(mp_window, ErrorCodeEnum::Window_CreationFailed);

    // Set user pointer for callback functions
    Windows_CallbackData *callbackData = new Windows_CallbackData();
    callbackData->window = owner;
    glfwSetWindowUserPointer(mp_window, callbackData);

    // Set window values
    glfwSetWindowTitle(mp_window, info.title.get_data());
    glfwSetWindowPos(mp_window, info.position.x, info.position.y);
    glfwSetWindowSize(mp_window, info.size.x, info.size.y);

    // Set callbacks
    glfwSetFramebufferSizeCallback(mp_window, [](GLFWwindow *window, Int width, Int height)
                                   {
			Windows_CallbackData* callbackData = static_cast<Windows_CallbackData*>(glfwGetWindowUserPointer(window));
			MINTY_ASSERT(callbackData, ErrorCodeEnum::InvalidUserData);
            MINTY_ASSERT(callbackData->window, ErrorCodeEnum::InvalidUserData);
			callbackData->window->on_resize(Int2(width, height)); });

    glfwSetWindowCloseCallback(mp_window, [](GLFWwindow *window)
                               {
			Windows_CallbackData* callbackData = static_cast<Windows_CallbackData*>(glfwGetWindowUserPointer(window));
			MINTY_ASSERT(callbackData, ErrorCodeEnum::InvalidUserData);
            MINTY_ASSERT(callbackData->window, ErrorCodeEnum::InvalidUserData);
            callbackData->window->on_close(); });

    glfwSetWindowFocusCallback(mp_window, [](GLFWwindow *window, Int focused)
                               {
        Windows_CallbackData* callbackData = static_cast<Windows_CallbackData*>(glfwGetWindowUserPointer(window));
            MINTY_ASSERT(callbackData, ErrorCodeEnum::InvalidUserData);
            MINTY_ASSERT(callbackData->window, ErrorCodeEnum::InvalidUserData);
            if (focused)
            {
                callbackData->window->on_focus();
            }
            else
            {
                callbackData->window->on_lost_focus();
            } });

    glfwSetWindowIconifyCallback(mp_window, [](GLFWwindow *window, Int iconified)
                                 {
        Windows_CallbackData* callbackData = static_cast<Windows_CallbackData*>(glfwGetWindowUserPointer(window));
            MINTY_ASSERT(callbackData, ErrorCodeEnum::InvalidUserData);
            MINTY_ASSERT(callbackData->window, ErrorCodeEnum::InvalidUserData);
            if (iconified)
            {
                callbackData->window->on_minimize();
            }
            else
            {
                callbackData->window->on_restore();
            } });

    glfwSetWindowMaximizeCallback(mp_window, [](GLFWwindow *window, Int maximized)
                                  {
        Windows_CallbackData* callbackData = static_cast<Windows_CallbackData*>(glfwGetWindowUserPointer(window));
            MINTY_ASSERT(callbackData, ErrorCodeEnum::InvalidUserData);
            MINTY_ASSERT(callbackData->window, ErrorCodeEnum::InvalidUserData);
            if (maximized)
            {
                callbackData->window->on_maximize();
            }
            else
            {
                callbackData->window->on_restore();
            } });

    glfwSetKeyCallback(mp_window, [](GLFWwindow *window, Int key, Int scancode, Int action, Int mods)
                       {
			Windows_CallbackData* callbackData = static_cast<Windows_CallbackData*>(glfwGetWindowUserPointer(window));
			MINTY_ASSERT(callbackData, ErrorCodeEnum::InvalidUserData);
            MINTY_ASSERT(callbackData->window, ErrorCodeEnum::InvalidUserData);
            callbackData->window->on_key(static_cast<KeyEnum>(key), static_cast<KeyActionEnum>(action), static_cast<KeyModifierFlagsEnum>(mods)); });

    glfwSetMouseButtonCallback(mp_window, [](GLFWwindow *window, Int button, Int action, Int mods)
                               {
			Windows_CallbackData* callbackData = static_cast<Windows_CallbackData*>(glfwGetWindowUserPointer(window));
			MINTY_ASSERT(callbackData, ErrorCodeEnum::InvalidUserData);
            MINTY_ASSERT(callbackData->window, ErrorCodeEnum::InvalidUserData);
            callbackData->window->on_mouse_button(static_cast<MouseButtonEnum>(button), static_cast<MouseActionEnum>(action)); });

    glfwSetCursorPosCallback(mp_window, [](GLFWwindow *window, WFloat x, WFloat y)
                             {
			Windows_CallbackData* callbackData = static_cast<Windows_CallbackData*>(glfwGetWindowUserPointer(window));
			MINTY_ASSERT(callbackData, ErrorCodeEnum::InvalidUserData);
            MINTY_ASSERT(callbackData->window, ErrorCodeEnum::InvalidUserData);
            callbackData->window->on_mouse_move(Float2(static_cast<Float>(x), static_cast<Float>(y))); });

    glfwSetScrollCallback(mp_window, [](GLFWwindow *window, WFloat xOffset, WFloat yOffset)
                          {
			Windows_CallbackData* callbackData = static_cast<Windows_CallbackData*>(glfwGetWindowUserPointer(window));
			MINTY_ASSERT(callbackData, ErrorCodeEnum::InvalidUserData);
            MINTY_ASSERT(callbackData->window, ErrorCodeEnum::InvalidUserData);
            callbackData->window->on_mouse_scroll(Float2(static_cast<Float>(xOffset), static_cast<Float>(yOffset))); });

    // TODO: set icon
}

Minty::Window::Impl::~Impl()
{
    // Destroy the GLFW window
    glfwDestroyWindow(mp_window);
}

Int2 Minty::Window::Impl::get_size() const
{
    Int2 size;
    glfwGetWindowSize(mp_window, &size.x, &size.y);
    return size;
}

void Minty::Window::Impl::set_size(Int2 const size)
{
    glfwSetWindowSize(mp_window, size.x, size.y);
}

Int2 Minty::Window::Impl::get_position() const
{
    Int2 position;
    glfwGetWindowPos(mp_window, &position.x, &position.y);
    return position;
}

void Minty::Window::Impl::set_position(Int2 const position)
{
    glfwSetWindowPos(mp_window, position.x, position.y);
}

Int2 Minty::Window::Impl::get_framebuffer_size() const
{
    Int2 size;
    glfwGetFramebufferSize(mp_window, &size.x, &size.y);
    return size;
}

Bool Minty::Window::Impl::is_open() const
{
    return !glfwWindowShouldClose(mp_window);
}

void Minty::Window::Impl::maximize()
{
    glfwMaximizeWindow(mp_window);
}

void Minty::Window::Impl::minimize()
{
    glfwIconifyWindow(mp_window);
}

void Minty::Window::Impl::restore()
{
    glfwRestoreWindow(mp_window);
}

void Minty::Window::Impl::close()
{
    glfwSetWindowShouldClose(mp_window, GLFW_TRUE);
}
