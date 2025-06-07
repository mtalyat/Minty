#include "pch.h"
#include "PhysicsSystem.h"
#include "Minty/Scene/Scene.h"
#include "Minty/Entity/EntityManager.h"
#include "Minty/Component/ColliderComponent.h"
#include "Minty/Component/RigidBodyComponent.h"
#include "Minty/Component/SimulateComponent.h"
#include "Minty/Component/TransformComponent.h"

using namespace Minty;

Minty::PhysicsSystem::PhysicsSystem(SystemBuilder const& builder)
	: System(builder)
{

}

void Minty::PhysicsSystem::initialize_entities()
{
	// get scene and managers
	Ref<Scene> const& scene = get_scene();
	MINTY_ASSERT(scene != nullptr, "Scene cannot be null.");
	EntityManager& entityManager = scene->get_entity_manager();
	PhysicsManager& physicsManager = scene->get_physics_manager();

	for (auto&& [entity, transform, collider] : entityManager.view<TransformComponent, ColliderComponent>(entt::exclude<RigidBodyComponent, SimulateComponent>).each())
	{
		// add to physics manager
		physicsManager.add_static(transform.transform, *collider.collider);

		// add simulate component
		entityManager.add_component<SimulateComponent>(entity);
	}
}

void Minty::PhysicsSystem::deinitialize_entities()
{

}

void Minty::PhysicsSystem::on_load()
{
	initialize_entities();
}

void Minty::PhysicsSystem::on_unload()
{
	deinitialize_entities();
}

void Minty::PhysicsSystem::on_update(Time const& time)
{
	// get scene and managers
	Ref<Scene> const& scene = get_scene();
	MINTY_ASSERT(scene != nullptr, "Scene cannot be null.");
	EntityManager& entityManager = scene->get_entity_manager();
	PhysicsManager& physicsManager = scene->get_physics_manager();

	// initialize any new entities
	initialize_entities();

	// update transforms from scene to physics engine
}
