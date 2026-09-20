#include "pch.hpp"
#include "Scene.hpp"
#include "Scene/Scene/SceneInfo.hpp"

using namespace Minty;

Minty::Scene::Scene()
    : mp_entityManager(new EntityManager({}, *this)),
      mp_systemManager(new SystemManager({}, *this)),
      m_priority(0),
      m_name(),
      m_status()
{
}

Minty::Scene::Scene(SceneInfo const &info)
    : mp_entityManager(new EntityManager(info.entityManagerInfo, *this)),
      mp_systemManager(new SystemManager(info.systemManagerInfo, *this)),
      m_priority(info.priority),
      m_name(info.name),
      m_status()
{
}

Minty::Scene::Scene(Scene &&scene)
    : mp_entityManager(scene.mp_entityManager),
      mp_systemManager(scene.mp_systemManager),
      m_priority(scene.m_priority),
      m_name(scene.m_name),
      m_status(scene.m_status)
{
    if (mp_entityManager)
    {
        mp_entityManager->set_scene(*this);
    }
    if (mp_systemManager)
    {
        mp_systemManager->set_scene(*this);
    }

    scene.mp_entityManager = nullptr;
    scene.mp_systemManager = nullptr;
}

Scene &Minty::Scene::operator=(Scene &&scene)
{
    if (this != &scene)
    {
        delete mp_entityManager;
        delete mp_systemManager;

        mp_entityManager = scene.mp_entityManager;
        mp_systemManager = scene.mp_systemManager;
        m_priority = scene.m_priority;
        m_name = scene.m_name,
        m_status = scene.m_status;

        if (mp_entityManager)
        {
            mp_entityManager->set_scene(*this);
        }
        if (mp_systemManager)
        {
            mp_systemManager->set_scene(*this);
        }

        scene.mp_entityManager = nullptr;
        scene.mp_systemManager = nullptr;
    }
    return *this;
}

void Minty::Scene::on_frame_update(Timestep const &timestep)
{
    mp_systemManager->on_frame_update(timestep);
}

void Minty::Scene::on_fixed_update(Timestep const &timestep)
{
    mp_systemManager->on_fixed_update(timestep);
}

void Minty::Scene::on_finalize()
{
    mp_entityManager->on_finalize();
    mp_systemManager->on_finalize();
}

void Minty::Scene::on_render()
{
    mp_systemManager->on_render();
}

void Minty::Scene::on_event(Event &event)
{
    mp_systemManager->on_event(event);
}

void Minty::Scene::trigger_promotion(StatusEnum const status)
{
    if (m_status.promote_parent_to(status))
    {
        mp_systemManager->trigger_promotion(m_status);
    }
}

void Minty::Scene::trigger_demotion(StatusEnum const status)
{
    if (m_status.demote_parent_to(status))
    {
        mp_systemManager->trigger_demotion(m_status);
    }
}

void Minty::Scene::on_create()
{
    if(m_status.promote_to(StatusEnum::Created))
    {
        mp_systemManager->trigger_promotion(StatusEnum::Created);
    }
}

void Minty::Scene::on_destroy()
{
    if(m_status.demote_to(StatusEnum::Destroyed))
    {
        mp_systemManager->trigger_demotion(StatusEnum::Destroyed);
    }
}

void Minty::Scene::on_load()
{
    if(m_status.promote_to(StatusEnum::Loaded))
    {
        mp_systemManager->trigger_promotion(StatusEnum::Loaded);
    }
}

void Minty::Scene::on_unload()
{
    if(m_status.demote_to(StatusEnum::Unloaded))
    {
        mp_systemManager->trigger_demotion(StatusEnum::Unloaded);
    }
}

void Minty::Scene::on_enable()
{
    if(m_status.promote_to(StatusEnum::Enabled))
    {
        mp_systemManager->trigger_promotion(StatusEnum::Enabled);
    }
}

void Minty::Scene::on_disable()
{
    if(m_status.demote_to(StatusEnum::Disabled))
    {
        mp_systemManager->trigger_demotion(StatusEnum::Disabled);
    }
}
