// THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

#include "Minty/Application/Application.h"
#include "Minty/System/_System.h"

using namespace Minty;

void Minty::Application::register_systems()
{
    SystemManager::register_system<AudioSystem>("Audio", 10000);
    SystemManager::register_system<PhysicsSystem>("Physics", 10000);
    SystemManager::register_system<RenderSystem>("Render", 10000);
    SystemManager::register_system<AnimationSystem>("Animation", 9999);
}
