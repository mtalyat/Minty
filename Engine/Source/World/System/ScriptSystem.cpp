#include "pch.hpp"
#include "ScriptSystem.hpp"
#include "Scene/Scene/Scene.hpp"
#include "World/Entity/EntityManager.hpp"
#include "World/Component/ScriptComponent.hpp"
#include "Script/Manager/ScriptManager.hpp"

using namespace Minty;

Minty::ScriptSystem::ScriptSystem(Scene &scene)
    : mp_scene(&scene)
{
}

void Minty::ScriptSystem::on_load()
{
    // Call all scripts attached to entities with the on_load method
    EntityManager& entityManager = mp_scene->get_entity_manager();
    ScriptManager &scriptManager = ScriptManager::get_instance();
    for(auto&& [entity, scriptComp] : entityManager.view<ScriptComponent const>().each())
    {
        for(ScriptHandle const handle : scriptComp.scripts)
        {
            scriptManager.call_load(handle);
        }
    }
}

void Minty::ScriptSystem::on_unload()
{
    // Call all scripts attached to entities with the on_unload method
    EntityManager& entityManager = mp_scene->get_entity_manager();
    ScriptManager &scriptManager = ScriptManager::get_instance();
    for(auto&& [entity, scriptComp] : entityManager.view<ScriptComponent const>().each())
    {
        for(ScriptHandle const handle : scriptComp.scripts)
        {
            scriptManager.call_unload(handle);
        }
    }
}

void Minty::ScriptSystem::on_enable()
{
    // Call all scripts attached to entities with the on_enable method
    EntityManager& entityManager = mp_scene->get_entity_manager();
    ScriptManager &scriptManager = ScriptManager::get_instance();
    for(auto&& [entity, scriptComp] : entityManager.view<ScriptComponent const>().each())
    {
        for(ScriptHandle const handle : scriptComp.scripts)
        {
            scriptManager.call_enable(handle);
        }
    }
}

void Minty::ScriptSystem::on_disable()
{
    // Call all scripts attached to entities with the on_disable method
    EntityManager& entityManager = mp_scene->get_entity_manager();
    ScriptManager &scriptManager = ScriptManager::get_instance();
    for(auto&& [entity, scriptComp] : entityManager.view<ScriptComponent const>().each())
    {
        for(ScriptHandle const handle : scriptComp.scripts)
        {
            scriptManager.call_disable(handle);
        }
    }
}

void Minty::ScriptSystem::on_frame_update(Timestep const &timestep)
{
    // Call all scripts attached to entities with the on_frame_update method
    EntityManager& entityManager = mp_scene->get_entity_manager();
    ScriptManager &scriptManager = ScriptManager::get_instance();
    for(auto&& [entity, scriptComp] : entityManager.view<ScriptComponent const>().each())
    {
        for(ScriptHandle const handle : scriptComp.scripts)
        {
            scriptManager.call_frame_update(handle);
        }
    }
}

void Minty::ScriptSystem::on_fixed_update(Timestep const &timestep)
{
    // Call all scripts attached to entities with the on_fixed_update method
    EntityManager& entityManager = mp_scene->get_entity_manager();
    ScriptManager &scriptManager = ScriptManager::get_instance();
    for(auto&& [entity, scriptComp] : entityManager.view<ScriptComponent const>().each())
    {
        for(ScriptHandle const handle : scriptComp.scripts)
        {
            scriptManager.call_fixed_update(handle);
        }
    }
}

void Minty::ScriptSystem::on_finalize()
{
    // Call all scripts attached to entities with the on_finalize method
    EntityManager& entityManager = mp_scene->get_entity_manager();
    ScriptManager &scriptManager = ScriptManager::get_instance();
    for(auto&& [entity, scriptComp] : entityManager.view<ScriptComponent const>().each())
    {
        for(ScriptHandle const handle : scriptComp.scripts)
        {
            scriptManager.call_finalize(handle);
        }
    }
}

void Minty::ScriptSystem::on_render()
{
    // Call all scripts attached to entities with the on_render method
    EntityManager& entityManager = mp_scene->get_entity_manager();
    ScriptManager &scriptManager = ScriptManager::get_instance();
    for(auto&& [entity, scriptComp] : entityManager.view<ScriptComponent const>().each())
    {
        for(ScriptHandle const handle : scriptComp.scripts)
        {
            scriptManager.call_render(handle);
        }
    }
}

void Minty::ScriptSystem::on_event(Event &event)
{
    // Call all scripts attached to entities with the on_event method
    EntityManager& entityManager = mp_scene->get_entity_manager();
    ScriptManager &scriptManager = ScriptManager::get_instance();
    for(auto&& [entity, scriptComp] : entityManager.view<ScriptComponent const>().each())
    {
        for(ScriptHandle const handle : scriptComp.scripts)
        {
            scriptManager.call_event(handle);
        }
    }
}
