#include "pch.hpp"
#include "Scene.hpp"
#include "Scene/Scene/SceneInfo.hpp"

using namespace Minty;

Minty::Scene::Scene(SceneInfo const &info)
    : mp_entityManager(new EntityManager(info.entityManagerInfo, *this)),
      mp_systemManager(new SystemManager(info.systemManagerInfo, *this)),
      m_priority(info.priority),
        m_name(info.name)
{
}

Minty::Scene::Scene(Scene &&scene)
    : mp_entityManager(scene.mp_entityManager),
      mp_systemManager(scene.mp_systemManager),
      m_priority(scene.m_priority),
      m_name(scene.m_name)
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
        m_name = scene.m_name;

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

void Minty::Scene::on_load()
{
    mp_systemManager->on_load();
}

void Minty::Scene::on_unload()
{
    mp_systemManager->on_unload();
}

void Minty::Scene::on_enable()
{
    mp_systemManager->on_enable();
}

void Minty::Scene::on_disable()
{
    mp_systemManager->on_disable();
}
