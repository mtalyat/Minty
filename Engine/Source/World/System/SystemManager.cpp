#include "pch.hpp"
#include "SystemManager.hpp"
#include "SystemManagerInfo.hpp"

using namespace Minty;

Registry<Pointer, SystemManager&> Minty::SystemManager::s_registeredSystems = {};

Minty::SystemManager::SystemManager(SystemManagerInfo const &info, Scene& scene)
    : mp_scene(&scene),
      m_systems(),
      m_frameUpdateHooks(),
      m_fixedUpdateHooks(),
      m_finalizeHooks(),
      m_renderHooks(),
      m_eventHooks(),
      m_loadHooks(),
      m_unloadHooks(),
      m_enableHooks(),
      m_disableHooks()
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
