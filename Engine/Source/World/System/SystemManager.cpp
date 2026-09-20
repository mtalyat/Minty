#include "pch.hpp"
#include "SystemManager.hpp"
#include "SystemManagerInfo.hpp"

using namespace Minty;

Registry<Pointer, SystemManager &> Minty::SystemManager::s_registeredSystems = {};

Minty::SystemManager::SystemManager(SystemManagerInfo const &info, Scene &scene)
    : mp_scene(&scene),
      m_systems(),
      m_createHooks(),
      m_destroyHooks(),
      m_loadHooks(),
      m_unloadHooks(),
      m_enableHooks(),
      m_disableHooks(),
      m_frameUpdateHooks(),
      m_fixedUpdateHooks(),
      m_finalizeHooks(),
      m_renderHooks(),
      m_eventHooks()
{
}

void Minty::SystemManager::on_frame_update(Timestep const &timestep)
{
    for (UpdateEventHook const &hook : m_frameUpdateHooks)
    {
        hook.func(hook.system, timestep);
    }
}

void Minty::SystemManager::on_fixed_update(Timestep const &timestep)
{
    for (UpdateEventHook const &hook : m_fixedUpdateHooks)
    {
        hook.func(hook.system, timestep);
    }
}

void Minty::SystemManager::on_finalize()
{
    for (EventHook const &hook : m_finalizeHooks)
    {
        hook.func(hook.system);
    }
}

void Minty::SystemManager::on_render()
{
    for (EventHook const &hook : m_renderHooks)
    {
        hook.func(hook.system);
    }
}

void Minty::SystemManager::on_event(Event &event)
{
    for (EventEventHook const &hook : m_eventHooks)
    {
        // Check if the event has already been handled before calling the hook
        if (event.is_handled())
        {
            break;
        }

        hook.func(hook.system, event);
    }
}

void Minty::SystemManager::trigger_promotion(StatusEnum const status)
{
    switch (status)
    {
    case StatusEnum::Created:
        on_create();
        break;
    case StatusEnum::Loaded:
        on_load();
        break;
    case StatusEnum::Enabled:
        on_enable();
        break;
    default:
        MINTY_NOT_IMPLEMENTED();
        break;
    }
}

void Minty::SystemManager::trigger_demotion(StatusEnum const status)
{
    switch (status)
    {
    case StatusEnum::Unloaded:
        on_unload();
        break;
    case StatusEnum::Disabled:
        on_disable();
        break;
    case StatusEnum::Destroyed:
        on_destroy();
        break;
    default:
        MINTY_NOT_IMPLEMENTED();
        break;
    }
}

void Minty::SystemManager::on_create()
{
    for (EventHook const &hook : m_createHooks)
    {
        hook.func(hook.system);
    }
}

void Minty::SystemManager::on_destroy()
{
    for (EventHook const &hook : m_destroyHooks)
    {
        hook.func(hook.system);
    }
}

void Minty::SystemManager::on_load()
{
    for (EventHook const &hook : m_loadHooks)
    {
        hook.func(hook.system);
    }
}

void Minty::SystemManager::on_unload()
{
    for (EventHook const &hook : m_unloadHooks)
    {
        hook.func(hook.system);
    }
}

void Minty::SystemManager::on_enable()
{
    for (EventHook const &hook : m_enableHooks)
    {
        hook.func(hook.system);
    }
}

void Minty::SystemManager::on_disable()
{
    for (EventHook const &hook : m_disableHooks)
    {
        hook.func(hook.system);
    }
}
