#include "pch.hpp"
#include "Scene.hpp"
#include "Scene/Scene/SceneInfo.hpp"

using namespace Minty;

Minty::Scene::Scene(SceneInfo const &info)
    : mp_entityManager(new EntityManager(info.entityManagerInfo)),
      mp_systemManager(new SystemManager(info.systemManagerInfo))
{
}

Minty::Scene::Scene(Scene &&scene)
    : mp_entityManager(scene.mp_entityManager),
      mp_systemManager(scene.mp_systemManager)
{
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

        scene.mp_entityManager = nullptr;
        scene.mp_systemManager = nullptr;
    }
    return *this;
}

void Minty::Scene::on_frame_update(Timestep const &timestep)
{
}

void Minty::Scene::on_fixed_update(Timestep const &timestep)
{
}

void Minty::Scene::on_finalize()
{
}

void Minty::Scene::on_render()
{
}

void Minty::Scene::on_event(Event const &event)
{
}
