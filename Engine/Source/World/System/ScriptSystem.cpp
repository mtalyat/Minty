#include "pch.hpp"
#include "ScriptSystem.hpp"
#include "Scene/Scene/Scene.hpp"
#include "World/Entity/EntityManager.hpp"
#include "World/Component/ScriptComponent.hpp"
#include "Script/Manager/ScriptManager.hpp"
#include "Script/Script/ScriptLocalContext.hpp"

using namespace Minty;

Minty::ScriptSystem::ScriptSystem(Scene &scene)
    : mp_scene(&scene)
{
}

void Minty::ScriptSystem::on_load()
{
    // Call all scripts attached to entities with the on_load method
    EntityManager &entityManager = mp_scene->get_entity_manager();
    ScriptManager &scriptManager = ScriptManager::get_instance();
    ScriptLocalContext localContext{};
    for (auto &&[entity, scriptComp] : entityManager.view<ScriptComponent const>().each())
    {
        // Update context for the current entity
        localContext.entity = entity;

        // Call all attached scripts for the current entity
        for (ScriptComponentData const& data : scriptComp.scripts)
        {
            if (data.enabled)
            {
                scriptManager.call_load(data.handle, localContext);
            }
        }
    }
}

void Minty::ScriptSystem::on_unload()
{
    // Call all scripts attached to entities with the on_unload method
    EntityManager &entityManager = mp_scene->get_entity_manager();
    ScriptManager &scriptManager = ScriptManager::get_instance();
    ScriptLocalContext localContext{};
    for (auto &&[entity, scriptComp] : entityManager.view<ScriptComponent const>().each())
    {
        // Update context for the current entity
        localContext.entity = entity;

        // Call all attached scripts for the current entity
        for (ScriptComponentData const& data : scriptComp.scripts)
        {
            if (data.enabled)
            {
                scriptManager.call_unload(data.handle, localContext);
            }
        }
    }
}

void Minty::ScriptSystem::on_enable()
{
    // Call all scripts attached to entities with the on_enable method
    EntityManager &entityManager = mp_scene->get_entity_manager();
    ScriptManager &scriptManager = ScriptManager::get_instance();
    ScriptLocalContext localContext{};
    for (auto &&[entity, scriptComp] : entityManager.view<ScriptComponent const>().each())
    {
        // Update context for the current entity
        localContext.entity = entity;

        // Call all attached scripts for the current entity
        for (ScriptComponentData const& data : scriptComp.scripts)
        {
            if (data.enabled)
            {
                scriptManager.call_enable(data.handle, localContext);
            }
        }
    }
}

void Minty::ScriptSystem::on_disable()
{
    // Call all scripts attached to entities with the on_disable method
    EntityManager &entityManager = mp_scene->get_entity_manager();
    ScriptManager &scriptManager = ScriptManager::get_instance();
    ScriptLocalContext localContext{};
    for (auto &&[entity, scriptComp] : entityManager.view<ScriptComponent const>().each())
    {
        // Update context for the current entity
        localContext.entity = entity;

        // Call all attached scripts for the current entity
        for (ScriptComponentData const& data : scriptComp.scripts)
        {
            if (data.enabled)
            {
                scriptManager.call_disable(data.handle, localContext);
            }
        }
    }
}

void Minty::ScriptSystem::on_frame_update(Timestep const &timestep)
{
    // Call all scripts attached to entities with the on_frame_update method
    EntityManager &entityManager = mp_scene->get_entity_manager();
    ScriptManager &scriptManager = ScriptManager::get_instance();
    ScriptLocalContext localContext{};
    for (auto &&[entity, scriptComp] : entityManager.view<ScriptComponent const>().each())
    {
        // Update context for the current entity
        localContext.entity = entity;

        // Call all attached scripts for the current entity
        for (ScriptComponentData const& data : scriptComp.scripts)
        {
            if (data.enabled)
            {
                scriptManager.call_frame_update(data.handle, localContext);
            }
        }
    }
}

void Minty::ScriptSystem::on_fixed_update(Timestep const &timestep)
{
    // Call all scripts attached to entities with the on_fixed_update method
    EntityManager &entityManager = mp_scene->get_entity_manager();
    ScriptManager &scriptManager = ScriptManager::get_instance();
    ScriptLocalContext localContext{};
    for (auto &&[entity, scriptComp] : entityManager.view<ScriptComponent const>().each())
    {
        // Update context for the current entity
        localContext.entity = entity;

        // Call all attached scripts for the current entity
        for (ScriptComponentData const& data : scriptComp.scripts)
        {
            if (data.enabled)
            {
                scriptManager.call_fixed_update(data.handle, localContext);
            }
        }
    }
}

void Minty::ScriptSystem::on_finalize()
{
    // Call all scripts attached to entities with the on_finalize method
    EntityManager &entityManager = mp_scene->get_entity_manager();
    ScriptManager &scriptManager = ScriptManager::get_instance();
    ScriptLocalContext localContext{};
    for (auto &&[entity, scriptComp] : entityManager.view<ScriptComponent const>().each())
    {
        // Update context for the current entity
        localContext.entity = entity;

        // Call all attached scripts for the current entity
        for (ScriptComponentData const& data : scriptComp.scripts)
        {
            if (data.enabled)
            {
                scriptManager.call_finalize(data.handle, localContext);
            }
        }
    }
}

void Minty::ScriptSystem::on_render()
{
    // Call all scripts attached to entities with the on_render method
    EntityManager &entityManager = mp_scene->get_entity_manager();
    ScriptManager &scriptManager = ScriptManager::get_instance();
    ScriptLocalContext localContext{};
    for (auto &&[entity, scriptComp] : entityManager.view<ScriptComponent const>().each())
    {
        // Update context for the current entity
        localContext.entity = entity;

        // Call all attached scripts for the current entity
        for (ScriptComponentData const& data : scriptComp.scripts)
        {
            if (data.enabled)
            {
                scriptManager.call_render(data.handle, localContext);
            }
        }
    }
}

void Minty::ScriptSystem::on_event(Event &event)
{
    // Call all scripts attached to entities with the on_event method
    EntityManager &entityManager = mp_scene->get_entity_manager();
    ScriptManager &scriptManager = ScriptManager::get_instance();
    ScriptLocalContext localContext{};
    for (auto &&[entity, scriptComp] : entityManager.view<ScriptComponent const>().each())
    {
        // Update context for the current entity
        localContext.entity = entity;

        // Call all attached scripts
        for (ScriptComponentData const& data : scriptComp.scripts)
        {
            if (data.enabled)
            {
                scriptManager.call_event(data.handle, localContext, event);
            }
        }
    }
}
