// THIS FILE IS AUTO GENERATED
// DO NOT MODIFY THIS FILE DIRECTLY

#include "Minty/Application/Application.h"
#include "Minty/System/_System.h"

using namespace Minty;

void Minty::Application::register_systems()
{
    SystemManager::register_system<RenderSystem>("Render", 100);
    SystemManager::register_system<PhysicsSystem>("Physics", -100);
    SystemManager::register_system<AnimationSystem>("Animation", 1);
    SystemManager::register_system<AudioSystem>("Audio", 1);
}