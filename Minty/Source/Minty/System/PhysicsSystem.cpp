#include "pch.h"
#include "PhysicsSystem.h"
#include "Minty/Context/Context.h"
#include "Minty/Entity/EntityManager.h"
#include "Minty/Component/ColliderComponent.h"
#include "Minty/Component/DestroyComponent.h"
#include "Minty/Component/EnabledComponent.h"
#include "Minty/Component/MeshComponent.h"
#include "Minty/Component/RigidBodyComponent.h"
#include "Minty/Component/SimulateComponent.h"
#include "Minty/Component/TransformComponent.h"
#include "Minty/Physics/PhysicsManager.h"
#include "Minty/Scene/Scene.h"

using namespace Minty;

Minty::PhysicsSystem::PhysicsSystem(SystemBuilder const& builder)
	: System(builder)
	, m_simulation()
	, m_accumulator(0.0f)
{
	Context& context = Context::get_singleton();
	
	// create the simulation based on data from the physics manager
	PhysicsSimulationBuilder simulationBuilder{};
	simulationBuilder.physicsManager = context.get_physics_manager_ref();
	simulationBuilder.layerManager = context.get_layer_manager_ref();
	m_simulation = PhysicsSimulation::create(simulationBuilder);
}

void Minty::PhysicsSystem::initialize_entities()
{
	// get scene and managers
	Ref<Scene> const& scene = get_scene();
	MINTY_ASSERT(scene != nullptr, "Scene cannot be null.");
	EntityManager& entityManager = scene->get_entity_manager();
	LayerManager& layerManager = LayerManager::get_singleton();

	// check for disabled entities
	for (auto&& [entity, collider, simulate] : entityManager.view<ColliderComponent, SimulateComponent const>(entt::exclude<RigidBodyComponent, EnabledComponent>).each())
	{
		MINTY_ASSERT(collider.collider != nullptr, F("Collider cannot be null. Entity: {}", entityManager.get_name(entity)));
		MINTY_ASSERT(collider.collider->is_static(), "Collider must be static if it does not have a RigidBody.");
		
		// remove from physics simulation
		m_simulation->remove_static(*collider.collider);

		// remove simulate component
		entityManager.remove_component<SimulateComponent>(entity);
	}

	// check for enabled, non-simulated entities
	for (auto&& [entity, transform, collider, enabled] : entityManager.view<TransformComponent, ColliderComponent, EnabledComponent>(entt::exclude<RigidBodyComponent, SimulateComponent, DestroyComponent>).each())
	{
		MINTY_ASSERT(collider.collider != nullptr, F("Collider cannot be null. Entity: {}", entityManager.get_name(entity)));
		MINTY_ASSERT(collider.collider->is_static(), "Collider must be static if it does not have a RigidBody.");
		MINTY_ASSERT(collider.collider->get_shape() != Shape::Empty, "Collider must have a non-empty shape.");

		// add to physics simulation
		Layer layer = entityManager.get_layer(entity);
		m_simulation->add_static(entity, transform.transform, *collider.collider, layer, layerManager.get_mask(layer));

		// add simulate component
		entityManager.add_component<SimulateComponent>(entity);
	}
}

void Minty::PhysicsSystem::deinitialize_entities()
{
	// get scene and managers
	Ref<Scene> const& scene = get_scene();
	MINTY_ASSERT(scene != nullptr, "Scene cannot be null.");
	EntityManager& entityManager = scene->get_entity_manager();

	// clear simulation
	for (auto&& [entity, transform, collider, body, simulate] : entityManager.view<TransformComponent const, ColliderComponent const, RigidBodyComponent const, SimulateComponent const>().each())
	{
		// remove from physics simulation
		m_simulation->remove_dynamic(*collider.collider, *body.rigidBody);

		// remove simulate component
		entityManager.remove_component<SimulateComponent>(entity);
	}
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

	// initialize any new entities
	initialize_entities();

	// accumulate time for physics
	m_accumulator += time.get_elapsed();

	// if time for at least one step, perform update
	if (m_accumulator >= DEFAULT_PHYSICS_TIME_STEP)
	{
		// update the physics simulation data with the world data
		for (auto const& [entity, transform, collider, body, simulate] : entityManager.view<TransformComponent const, ColliderComponent const, RigidBodyComponent const, SimulateComponent const>().each())
		{
			m_simulation->set_dynamic(transform.transform, *collider.collider, *body.rigidBody);
		}

		// perform the physics steps
		while (m_accumulator >= DEFAULT_PHYSICS_TIME_STEP)
		{
			m_simulation->step(DEFAULT_PHYSICS_TIME_STEP);
			m_accumulator -= DEFAULT_PHYSICS_TIME_STEP;
		}

		// update the world data with the physics simulation data
		for (auto&& [entity, transform, collider, body, simulate] : entityManager.view<TransformComponent, ColliderComponent const, RigidBodyComponent const, SimulateComponent const>().each())
		{
			m_simulation->get_dynamic(transform.transform, *collider.collider, *body.rigidBody);
		}
	}
}

void Minty::PhysicsSystem::on_finalize()
{
	// get scene and managers
	Ref<Scene> const& scene = get_scene();
	MINTY_ASSERT(scene != nullptr, "Scene cannot be null.");
	EntityManager& entityManager = scene->get_entity_manager();

	// remove any entities marked for destruction from the physics simulation
	for (auto&& [entity, transform, collider, body, simulate, destroy] : entityManager.view<TransformComponent const, ColliderComponent const, RigidBodyComponent const, SimulateComponent const, DestroyComponent const>().each())
	{
		// remove from physics manager
		m_simulation->remove_dynamic(*collider.collider, *body.rigidBody);

		// remove simulate component
		entityManager.remove_component<SimulateComponent>(entity);
	}
}
