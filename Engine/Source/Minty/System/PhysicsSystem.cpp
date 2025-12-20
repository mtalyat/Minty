#include "pch.h"
#include "PhysicsSystem.h"
#include "Minty/Application/Application.h"
#include "Minty/Entity/EntityManager.h"
#include "Minty/Component/ColliderComponent.h"
#include "Minty/Component/DestroyComponent.h"
#include "Minty/Component/EnabledComponent.h"
#include "Minty/Component/MeshComponent.h"
#include "Minty/Component/RigidBodyComponent.h"
#include "Minty/Component/_PhysicsComponents.h"
#include "Minty/Component/PositionComponent.h"
#include "Minty/Component/RotationComponent.h"
#include "Minty/Component/ScaleComponent.h"
#include "Minty/Component/GravityComponent.h"
#include "Minty/Component/TransformComponent.h"
#include "Minty/Component/VelocityComponent.h"
#include "Minty/Component/SnapComponent.h"
#include "Minty/Debug/Trace.h"
#include "Minty/Physics/PhysicsManager.h"
#include "Minty/Scene/Scene.h"
#include "Minty/Physics/PhysicsSimulation.h"
#include "Minty/Layer/LayerManager.h"
#include "Minty/Physics/PhysicsManager.h"
#include "Minty/Physics/PhysicsSimulationInfo.h"
#include "Minty/Physics/Collider.h"
#include "Minty/Time/TimeController.h"

using namespace Minty;

// update rigidbody values from entity components
static void set_rigidbody_values(Entity const entity, EntityManager &entityManager, RigidBody &body)
{
	// if there is a parent, base this transform off of the parent's global transform
	TransformComponent const * const transformComp = entityManager.try_get_component<TransformComponent const>(entity);
	PositionComponent const * const positionComp = entityManager.try_get_component<PositionComponent const>(entity);
	RotationComponent const * const rotationComp = entityManager.try_get_component<RotationComponent const>(entity);
	TransformComponent const * const parentTransformComp = entityManager.try_get_component<TransformComponent const>(entityManager.get_parent(entity));

	// save previous transform for interpolation
	PhysicsComponent &physicsComp = entityManager.get_or_add_component<PhysicsComponent>(entity);

	// set transform based on Position, Rotation, Scale components if they exist
	if (parentTransformComp)
	{
		if(positionComp)
		{
			body.set_position(parentTransformComp->transform.get_global_position() + positionComp->position);
		}
		else if (transformComp)
		{
			body.set_position(parentTransformComp->transform.get_global_position() + transformComp->transform.get_local_position());
		}
		else
		{
			body.set_position(parentTransformComp->transform.get_global_position());
		}
		physicsComp.previousPosition = body.get_position();
		if (rotationComp)
		{
			body.set_rotation(parentTransformComp->transform.get_global_rotation() + rotationComp->rotation);
		}
		else if (transformComp)
		{
			body.set_rotation(parentTransformComp->transform.get_global_rotation() + transformComp->transform.get_local_rotation());
		}
		else
		{
			body.set_rotation(parentTransformComp->transform.get_global_rotation());
		}
		physicsComp.previousRotation = body.get_rotation();
	}
	else
	{
		if (positionComp)
		{
			body.set_position(positionComp->position);
			physicsComp.previousPosition = positionComp->position;
		} else if (transformComp)
		{
			body.set_position(transformComp->transform.get_local_position());
			physicsComp.previousPosition = transformComp->transform.get_local_position();
		}
		if (rotationComp)
		{
			body.set_rotation(rotationComp->rotation);
			physicsComp.previousRotation = rotationComp->rotation;
		} else if (transformComp)
		{
			body.set_rotation(transformComp->transform.get_local_rotation());
			physicsComp.previousRotation = transformComp->transform.get_local_rotation();
		}
	}

	if (VelocityComponent const *velocityComp = entityManager.try_get_component<VelocityComponent const>(entity))
	{
		body.set_linear_velocity(velocityComp->velocity);
	}
}

// update entity components from rigidbody values
static void get_rigidbody_values(Entity const entity, EntityManager &entityManager, RigidBody &body)
{
	// if there is a parent, convert global transform to local
	TransformComponent const *parentTransformComp = entityManager.try_get_component<TransformComponent const>(entityManager.get_parent(entity));

	// set the entity's Position, Rotation, Scale components if they exist
	if (parentTransformComp)
	{
		if (PositionComponent *positionComp = entityManager.try_get_component<PositionComponent>(entity))
		{
			positionComp->position = body.get_position() - parentTransformComp->transform.get_global_position();
		}
		if (RotationComponent *rotationComp = entityManager.try_get_component<RotationComponent>(entity))
		{
			rotationComp->rotation = body.get_rotation() - parentTransformComp->transform.get_global_rotation();
		}
	}
	else
	{
		if (PositionComponent *positionComp = entityManager.try_get_component<PositionComponent>(entity))
		{
			positionComp->position = body.get_position();
		}
		if (RotationComponent *rotationComp = entityManager.try_get_component<RotationComponent>(entity))
		{
			rotationComp->rotation = body.get_rotation();
		}
	}

	if (VelocityComponent *velocityComp = entityManager.try_get_component<VelocityComponent>(entity))
	{
		velocityComp->velocity = body.get_linear_velocity();
	}
}

Minty::PhysicsSystem::PhysicsSystem(SystemInfo const &info)
	: System(info), m_simulation(), m_lastUpdateTimestep(-1.0f, -1.0f)
{
	Application &app = Application::get_singleton();

	// create the simulation based on data from the physics manager
	PhysicsSimulationInfo simulationInfo{};
	m_simulation = PhysicsSimulation::create(simulationInfo);
}

void Minty::PhysicsSystem::initialize_entities()
{
	// get scene and managers
	Ref<Scene> const &scene = get_scene_ref();
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
	for (auto &&[entity, bodyComp, simulateComp] : entityManager.view<RigidBodyComponent, SimulateComponent const>(entt::exclude<EnabledComponent>).each())
	{
		MINTY_ASSERT_F(bodyComp.rigidBody != nullptr, ErrorCode::Component_InvalidState, entityManager.get_name(entity));

		// remove from physics simulation
		m_simulation->remove_dynamic(*bodyComp.rigidBody);

		// update entity components from rigidbody values
		get_rigidbody_values(entity, entityManager, *bodyComp.rigidBody);

		// remove simulate component
		entityManager.remove_component<SimulateComponent>(entity);
	}

	// check for enabled, non-simulated entities
	for (auto &&[entity, colliderComp, enabledComp] : entityManager.view<ColliderComponent, EnabledComponent const>(entt::exclude<RigidBodyComponent, SimulateComponent, DestroyComponent>).each())
	{
		MINTY_ASSERT_F(colliderComp.collider != nullptr, ErrorCode::Component_InvalidState, entityManager.to_string(entity));
		MINTY_ASSERT_F(colliderComp.collider->is_static(), ErrorCode::Component_InvalidState, entityManager.to_string(entity));					// "Collider must be static if it does not have a RigidBody. Entity: {}", entityManager.get_name(entity)
		MINTY_ASSERT_F(colliderComp.collider->get_shape() != Shape::Empty, ErrorCode::Component_InvalidState, entityManager.to_string(entity)); // "Collider must have a non-empty shape. Entity: {}", entityManager.get_name(entity)

		// add to physics simulation
		TransformComponent const *const transformComp = entityManager.try_get_component<TransformComponent const>(entity);
		Layer const layer = entityManager.get_layer(entity);
		Layer const mask = layerManager.get_mask(layer);
		if (transformComp != nullptr)
		{
			m_simulation->add_static(entity, transformComp->transform, *colliderComp.collider, layer, mask);
		}
		else
		{
			Transform defaultTransform{};
			m_simulation->add_static(entity, defaultTransform, *colliderComp.collider, layer, mask);
		}

		// add simulate component
		entityManager.add_component<SimulateComponent>(entity);
	}
	for (auto &&[entity, bodyComp, enabledComp] : entityManager.view<RigidBodyComponent, EnabledComponent const>(entt::exclude<SimulateComponent, DestroyComponent>).each())
	{
		MINTY_ASSERT_F(bodyComp.rigidBody != nullptr, ErrorCode::Component_InvalidState, entityManager.get_name(entity));

		// add to physics simulation
		Layer const layer = entityManager.get_layer(entity);
		Layer const mask = layerManager.get_mask(layer);
		m_simulation->add_dynamic(entity, *bodyComp.rigidBody, layer, mask);

		// update rigidbody values from entity components
		set_rigidbody_values(entity, entityManager, *bodyComp.rigidBody);

		// add simulate component
		entityManager.add_component<SimulateComponent>(entity);
	}
}

void Minty::PhysicsSystem::deinitialize_entities()
{
	// get scene and managers
	Ref<Scene> const &scene = get_scene_ref();
	MINTY_ASSERT(scene != nullptr, ErrorCode::Object_InvalidState);
	EntityManager &entityManager = scene->get_entity_manager();

	// clear simulation
	for (auto &&[entity, bodyComp, simulateComp] : entityManager.view<RigidBodyComponent const, SimulateComponent const>().each())
	{
		if (!bodyComp.rigidBody)
		{
			MINTY_ERROR(ErrorCode::Component_InvalidState);
			continue;
		}

		// remove from physics simulation
		m_simulation->remove_dynamic(*bodyComp.rigidBody);

		if (bodyComp.rigidBody->is_dynamic())
		{
			// update entity components from rigidbody values
			get_rigidbody_values(entity, entityManager, *bodyComp.rigidBody);
		}

		// remove simulate component
		entityManager.remove_component<SimulateComponent>(entity);
	}
}

void Minty::PhysicsSystem::update_simulated_entities(Timestep const time)
{
	Scene &scene = get_scene();
	EntityManager &entityManager = scene.get_entity_manager();

	// apply gravity to entities with GravityComponent
	for (auto const &[entity, bodyComp, gravityComp, simulateComp, enabledComp] : entityManager.view<RigidBodyComponent const, GravityComponent const, SimulateComponent const, EnabledComponent const>().each())
	{
		// throw an error if no rigid body, somehow
		MINTY_ASSERT(bodyComp.rigidBody != nullptr, ErrorCode::Component_InvalidState);

		if (!bodyComp.rigidBody->is_dynamic())
		{
			// only apply to dynamic bodies
			continue;
		}

		// apply gravity force
		Float3 const gravityForce = gravityComp.scale * m_simulation->get_gravity();
		bodyComp.rigidBody->add_force(gravityForce, Force::Continuous);
	}
}

void Minty::PhysicsSystem::update_simulation_from_world(Timestep const time)
{
	Scene &scene = get_scene();
	EntityManager &entityManager = scene.get_entity_manager();

	for (auto const &[entity, bodyComp, simulateComp, enabledComp] : entityManager.view<RigidBodyComponent const, SimulateComponent const, EnabledComponent const>().each())
	{
		if (bodyComp.rigidBody == nullptr)
		{
			MINTY_LOG_WARNING_F("Entity {} has no RigidBody to update to simulation.", entityManager.to_string(entity));
			continue;
		}
		RigidBody &body = *bodyComp.rigidBody;

		set_rigidbody_values(entity, entityManager, body);
	}
}

void Minty::PhysicsSystem::update_world_from_simulation(Timestep const time)
{
	Scene &scene = get_scene();
	EntityManager &entityManager = scene.get_entity_manager();

	for (auto &&[entity, bodyComp, simulateComp, enabledComp] : entityManager.view<RigidBodyComponent const, SimulateComponent const, EnabledComponent const>().each())
	{
		if (bodyComp.rigidBody == nullptr)
		{
			MINTY_LOG_WARNING_F("Entity {} has no RigidBody to update from simulation.", entityManager.to_string(entity));
			continue;
		}
		RigidBody &body = *bodyComp.rigidBody;

		get_rigidbody_values(entity, entityManager, body);
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

void Minty::PhysicsSystem::on_frame_update(Timestep const time)
{
	// if no previous update time, skip interpolation
	if (m_lastUpdateTimestep.get_total() < 0.0f)
	{
		return;
	}

	Scene &scene = get_scene();
	EntityManager &entityManager = scene.get_entity_manager();

	Float const alpha = (time.get_total() - m_lastUpdateTimestep.get_total()) / m_lastUpdateTimestep.get_elapsed();

	// for each entity with a transform and physics components, lerp from the old data to the new data for smooth rendering
	for (auto &&[entity, transformComp, physicsComp, bodyComp, simulateComp, enabledComp] : entityManager.view<TransformComponent, PhysicsComponent const, RigidBodyComponent const, SimulateComponent const, EnabledComponent const>().each())
	{
		// if there is a parent, base this transform off of the parent's global transform
		TransformComponent const *parentTransformComp = entityManager.try_get_component<TransformComponent const>(entityManager.get_parent(entity));

		// set the transform based on Position, Rotation, Scale components if they exist
		if (parentTransformComp)
		{
			if (PositionComponent const *positionComp = entityManager.try_get_component<PositionComponent const>(entity))
			{
				Float3 const interpolatedPosition = Math::lerp(physicsComp.previousPosition, positionComp->position, alpha);
				transformComp.transform.set_local_position(interpolatedPosition - parentTransformComp->transform.get_global_position());
			}
			if (RotationComponent const *rotationComp = entityManager.try_get_component<RotationComponent const>(entity))
			{
				Quaternion const interpolatedRotation = Math::slerp(physicsComp.previousRotation, rotationComp->rotation, alpha);
				transformComp.transform.set_local_rotation(interpolatedRotation - parentTransformComp->transform.get_global_rotation());
			}
			if (ScaleComponent const *scaleComp = entityManager.try_get_component<ScaleComponent const>(entity))
			{
				Float3 const interpolatedScale = Math::lerp(physicsComp.previousScale, scaleComp->scale, alpha);
				transformComp.transform.set_local_scale(interpolatedScale / parentTransformComp->transform.get_global_scale());
			}
		}
		else
		{
			if (PositionComponent const *positionComp = entityManager.try_get_component<PositionComponent const>(entity))
			{
				Float3 const interpolatedPosition = Math::lerp(physicsComp.previousPosition, positionComp->position, alpha);
				transformComp.transform.set_local_position(interpolatedPosition);
			}
			if (RotationComponent const *rotationComp = entityManager.try_get_component<RotationComponent const>(entity))
			{
				Quaternion const interpolatedRotation = Math::slerp(physicsComp.previousRotation, rotationComp->rotation, alpha);
				transformComp.transform.set_local_rotation(interpolatedRotation);
			}
			if (ScaleComponent const *scaleComp = entityManager.try_get_component<ScaleComponent const>(entity))
			{
				Float3 const interpolatedScale = Math::lerp(physicsComp.previousScale, scaleComp->scale, alpha);
				transformComp.transform.set_local_scale(interpolatedScale);
			}
		}

		entityManager.dirty(entity);
	}

	// if a snap size is set, snap entities to the grid
	if (m_snapSize > 0.0f)
	{
		for (auto &&[entity, transformComp, snapComp, simulateComp, enabledComp] : entityManager.view<TransformComponent, SnapComponent const, SimulateComponent const, EnabledComponent const>().each())
		{
			Transform &transform = transformComp.transform;
			Float3 snapped = Math::snap(transform.get_local_position(), m_snapSize);
			transform.set_local_position(snapped);
			entityManager.dirty(entity);
		}
	}
}

void Minty::PhysicsSystem::on_fixed_update(Timestep const time)
{
	MINTY_TRACE_SCOPE();

	// update time
	m_lastUpdateTimestep = time;

	// initialize any new entities
	initialize_entities();

	// update simulated entities
	update_simulated_entities(time);

	// update the physics simulation data with the world data
	update_simulation_from_world(time);

	// perform a physics step
	m_simulation->step(time.get_elapsed());

	// update the world data with the physics simulation data
	update_world_from_simulation(time);
}

void Minty::PhysicsSystem::on_finalize()
{
	MINTY_TRACE_SCOPE();

	// get scene and managers
	Ref<Scene> const &scene = get_scene_ref();
	MINTY_ASSERT(scene != nullptr, ErrorCode::Object_InvalidState);
	EntityManager &entityManager = scene->get_entity_manager();

	// remove any entities marked for destruction from the physics simulation
	for (auto &&[entity, simulateComp, destroyComp] : entityManager.view<SimulateComponent const, DestroyComponent const>().each())
	{
		// remove from physics simulation
		RigidBodyComponent const *bodyComp = entityManager.try_get_component<RigidBodyComponent>(entity);
		if (bodyComp != nullptr && bodyComp->rigidBody != nullptr)
		{
			m_simulation->remove_dynamic(*bodyComp->rigidBody);
		}
		else
		{
			ColliderComponent const *colliderComp = entityManager.try_get_component<ColliderComponent>(entity);
			MINTY_ASSERT_F(colliderComp != nullptr && colliderComp->collider != nullptr, ErrorCode::Component_InvalidState, entityManager.get_name(entity));
			m_simulation->remove_static(*colliderComp->collider);
		}

		// remove simulate component
		entityManager.remove_component<SimulateComponent>(entity);
	}
}
