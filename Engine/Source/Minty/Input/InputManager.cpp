#include "pch.h"
#include "InputManager.h"
#include "Minty/Application/Application.h"
#include "Minty/Input/InputManagerInfo.h"

using namespace Minty;

InputManager* InputManager::s_instance = nullptr;

InputManager& Minty::InputManager::get_instance()
{
	return Application::get_singleton().get_input_manager();
}

Unique<InputManager> Minty::InputManager::create(InputManagerInfo const& info)
{
	return Unique<InputManager>::create(info);
}
