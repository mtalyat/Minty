#include "pch.h"
#include "PhysicsSystem.h"
#include "Minty/Application/Application.h"
#include "Minty/Entity/EntityManager.h"
#include "Minty/Component/ColliderComponent.h"
#include "Minty/Component/DestroyComponent.h"
#include "Minty/Component/EnabledComponent.h"
#include "Minty/Component/MeshComponent.h"
#include "Minty/Component/RigidBodyComponent.h"
#include "Minty/Component/SimulateComponent.h"
#include "Minty/Component/TransformComponent.h"
#include "Minty/Debug/Trace.h"
#include "Minty/Physics/PhysicsManager.h"
#include "Minty/Scene/Scene.h"
#include "Minty/Physics/PhysicsSimulation.h"
#include "Minty/Layer/LayerManager.h"
#include "Minty/Physics/PhysicsManager.h"
#include "Minty/Physics/PhysicsSimulationInfo.h"
#include "Minty/Physics/Collider.h"

using namespace Minty;

Minty::PhysicsSystem::PhysicsSystem(SystemInfo const &info)
	: System(info), m_simulation()
{
	Application &app = Application::get_singleton();

	// create the simulation based on data from the physics manager
	PhysicsSimulationInfo simulationInfo{};
	m_simulation = PhysicsSimulation::create(simulationInfo);
}

void Minty::PhysicsSystem::initialize_entities()
{
	// get scene and managers
	Ref<Scene> const &scene = get_scene();
	MINTY_ASSERT(scene != nullptr, ErrorCode::Object_InvalidState);
	EntityManager &entityManager = scene->get_entity_manager();
	LayerManager &layerManager = LayerManager::get_singleton();

	// check for disabled entities
	for (auto &&[entity, colliderComp, simulateComp] : entityManager.view<ColliderComponent, SimulateComponent const>(entt::exclude<RigidBodyComponent, EnabledComponent>).each())
	{
		MINTY_ASSERT_F(colliderComp.collider != nullptr, ErrorCode::Component_InvalidState, entityManager.get_name(entity));
		MINTY_ASSERT_F(colliderComp.collider->is_static(), ErrorCode::Component_InvalidState); // "Collider must be static if it does not have a RigidBody. Entity: {}", entityManager.get_name(entity)

		// remove from physics simulation
		m_simulation->remove_static(*colliderComp.collider);

		// remove simulate component
		entityManager.remove_component<SimulateComponent>(entity);
	}

	// check for enabled, non-simulated entities
	for (auto &&[entity, transformComp, colliderComp, enabledComp] : entityManager.view<TransformComponent, ColliderComponent, EnabledComponent const>(entt::exclude<RigidBodyComponent, SimulateComponent, DestroyComponent>).each())
	{
		MINTY_ASSERT_F(colliderComp.collider != nullptr, ErrorCode::Component_InvalidState, entityManager.get_name(entity));
		MINTY_ASSERT_F(colliderComp.collider->is_static(), ErrorCode::Component_InvalidState);				 // "Collider must be static if it does not have a RigidBody. Entity: {}", entityManager.get_name(entity)
		MINTY_ASSERT_F(colliderComp.collider->get_shape() != Shape::Empty, ErrorCode::Component_InvalidState); // "Collider must have a non-empty shape. Entity: {}", entityManager.get_name(entity)

		// add to physics simulation
		Layer layer = entityManager.get_layer(entity);
		m_simulation->add_static(entity, transformComp.transform, *colliderComp.collider, layer, layerManager.get_mask(layer));

		// add simulate component
		entityManager.add_component<SimulateComponent>(entity);
	}
}

void Minty::PhysicsSystem::deinitialize_entities()
{
	// get scene and managers
	Ref<Scene> const &scene = get_scene();
	MINTY_ASSERT(scene != nullptr, ErrorCode::Object_InvalidState);
	EntityManager &entityManager = scene->get_entity_manager();

	// clear simulation
	for (auto &&[entity, transformComp, colliderComp, bodyComp, simulateComp] : entityManager.view<TransformComponent const, ColliderComponent const, RigidBodyComponent const, SimulateComponent const>().each())
	{
		// remove from physics simulation
		m_simulation->remove_dynamic(*colliderComp.collider, *bodyComp.rigidBody);

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

void Minty::PhysicsSystem::on_fixed_update(Timestep const &time)
{
	MINTY_TRACE_SCOPE();

	// initialize any new entities
	initialize_entities();
	
	Ref<Scene> const &scene = get_scene();
	MINTY_ASSERT(scene != nullptr, ErrorCode::Object_InvalidState);
	EntityManager &entityManager = scene->get_entity_manager();

	// update the physics simulation data with the world data
	for (auto const &[entity, transformComp, colliderComp, bodyComp, simulateComp, enabledComp] : entityManager.view<TransformComponent const, ColliderComponent const, RigidBodyComponent const, SimulateComponent const, EnabledComponent const>().each())
	{
		m_simulation->set_dynamic(transformComp.transform, *colliderComp.collider, *bodyComp.rigidBody);
	}

	// update the world data with the physics simulation data
	for (auto &&[entity, transformComp, colliderComp, bodyComp, simulateComp, enabledComp] : entityManager.view<TransformComponent, ColliderComponent const, RigidBodyComponent const, SimulateComponent const, EnabledComponent const>().each())
	{
		m_simulation->get_dynamic(transformComp.transform, *colliderComp.collider, *bodyComp.rigidBody);
	}
}

void Minty::PhysicsSystem::on_finalize()
{
	MINTY_TRACE_SCOPE();

	// get scene and managers
	Ref<Scene> const &scene = get_scene();
	MINTY_ASSERT(scene != nullptr, ErrorCode::Object_InvalidState);
	EntityManager &entityManager = scene->get_entity_manager();

	// remove any entities marked for destruction from the physics simulation
	for (auto &&[entity, transformComp, colliderComp, bodyComp, simulateComp, destroyComp] : entityManager.view<TransformComponent const, ColliderComponent const, RigidBodyComponent const, SimulateComponent const, DestroyComponent const>().each())
	{
		// remove from physics manager
		m_simulation->remove_dynamic(*colliderComp.collider, *bodyComp.rigidBody);

		// remove simulate component
		entityManager.remove_component<SimulateComponent>(entity);
	}
}
