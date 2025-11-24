#include "pch.h"
#include "InputManager.h"
#include "Minty/Context/Context.h"

using namespace Minty;

InputManager* InputManager::s_instance = nullptr;

InputManager& Minty::InputManager::get_instance()
{
	return Context::get_singleton().get_input_manager();
}

Owner<InputManager> Minty::InputManager::create(InputManagerBuilder const& builder)
{
	return Owner<InputManager>(new InputManager(builder));
}
