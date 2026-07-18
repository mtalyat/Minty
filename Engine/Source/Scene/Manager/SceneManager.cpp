#include "pch.hpp"
#include "SceneManager.hpp"
#include "Scene/Manager/SceneManagerInfo.hpp"
#include "Scene/Scene/Scene.hpp"
#include "Event/Event/Event.hpp"

using namespace Minty;

Minty::SceneManager::SceneManager(SceneManagerInfo const &info)
{
}

Minty::SceneManager::~SceneManager()
{
}

SceneHandle Minty::SceneManager::create(SceneInfo const &info)
{
    // Create a Scene
    Scene scene(info);

    // Add the Scene to the HandlePool
    SceneHandle const handle = m_scenes.add(std::move(scene));

    // Return the handle
    return handle;
}

void Minty::SceneManager::destroy(SceneHandle const handle)
{
    MINTY_ASSERT(m_scenes.contains(handle), ErrorCodeEnum::Argument_KeyNotFound);

    // If the scene is active, remove it from the active scenes list
    deactivate(handle);

    // Remove the Scene from the HandlePool
    m_scenes.remove(handle);
}

Scene &Minty::SceneManager::at(SceneHandle const handle)
{
    MINTY_ASSERT(m_scenes.contains(handle), ErrorCodeEnum::Argument_KeyNotFound);

    return m_scenes.at(handle);
}

Scene const &Minty::SceneManager::at(SceneHandle const handle) const
{
    MINTY_ASSERT(m_scenes.contains(handle), ErrorCodeEnum::Argument_KeyNotFound);

    return m_scenes.at(handle);
}

void Minty::SceneManager::activate(SceneHandle const handle)
{
    MINTY_ASSERT(m_scenes.contains(handle), ErrorCodeEnum::Argument_KeyNotFound);

    // If the scene is not already active, add it to the active scenes list
    for (SceneHandle const activeScene : m_activeScenes)
    {
        if (activeScene == handle)
        {
            return; // Scene is already active
        }
    }

    // Get the scene data
    Scene &scene = at(handle);

    // Add the scene to the active scenes list
    m_activeScenes.add(handle, scene.get_priority());
}

void Minty::SceneManager::deactivate(SceneHandle const handle)
{
    MINTY_ASSERT(m_scenes.contains(handle), ErrorCodeEnum::Argument_KeyNotFound);

    // If the scene is active, remove it from the active scenes list
    for (Size i = 0; i < m_activeScenes.get_size(); ++i)
    {
        if (m_activeScenes[i] == handle)
        {
            m_activeScenes.remove(i);
            return;
        }
    }
}

void Minty::SceneManager::on_frame_update(Timestep const &timestep)
{
    // Update all active scenes
    for (SceneHandle const handle : m_activeScenes)
    {
        Scene &scene = at(handle);
        scene.on_frame_update(timestep);
    }
}

void Minty::SceneManager::on_fixed_update(Timestep const &timestep)
{
    // Update all active scenes
    for (SceneHandle const handle : m_activeScenes)
    {
        Scene &scene = at(handle);
        scene.on_fixed_update(timestep);
    }
}

void Minty::SceneManager::on_finalize()
{
    // Finalize all active scenes
    for (SceneHandle const handle : m_activeScenes)
    {
        Scene &scene = at(handle);
        scene.on_finalize();
    }
}

void Minty::SceneManager::on_render()
{
    // Render all active scenes
    for (SceneHandle const handle : m_activeScenes)
    {
        Scene &scene = at(handle);
        scene.on_render();
    }
}

void Minty::SceneManager::on_event(Event &event)
{
    // Send the event to all active scenes until it has been handled
    for (SceneHandle const handle : m_activeScenes)
    {
        // Stop sending the event if it has been handled
        if (event.is_handled())
        {
            break;
        }

        // Send the event to the scene
        Scene &scene = at(handle);
        scene.on_event(event);
    }
}
