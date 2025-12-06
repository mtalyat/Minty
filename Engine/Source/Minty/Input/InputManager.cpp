#include "pch.h"
#include "InputManager.h"
#include "Minty/Application/Application.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Input/InputManagerInfo.h"

using namespace Minty;

InputManager* InputManager::s_instance = nullptr;

InputManager& Minty::InputManager::get_singleton()
{
	Unique<InputManager> const& instance = Application::get_singleton().get_input_manager();
	MINTY_ASSERT(instance, ErrorCode::Application_InputManagerNotInitialized);
	return *instance;
}

Unique<InputManager> const &Minty::InputManager::get_instance()
{
	return Application::get_singleton().get_input_manager();
}

Unique<InputManager> Minty::InputManager::create(InputManagerInfo const& info)
{
	return Unique<InputManager>::create(info);
}

Unique<InputManager> Minty::InputManager::create()
{
	InputManagerInfo info{};
    return create(info);
}
