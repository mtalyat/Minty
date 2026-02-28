#include "pch.h"
#include "PhysicsSystem.h"
#include "Minty/Application/Application.h"
#include "Minty/Entity/EntityManager.h"
#include "Minty/Component/ColliderComponent.h"
#include "Minty/Component/DestroyTag.h"
#include "Minty/Component/EnabledTag.h"
#include "Minty/Component/MeshComponent.h"
#include "Minty/Component/RigidbodyComponent.h"
#include "Minty/Component/_PhysicsComponents.h"
#include "Minty/Component/PositionComponent.h"
#include "Minty/Component/RotationComponent.h"
#include "Minty/Component/ScaleComponent.h"
#include "Minty/Component/GravityComponent.h"
#include "Minty/Component/TransformComponent.h"
#include "Minty/Component/VelocityComponent.h"
#include "Minty/Component/SnapTag.h"
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

static Float3 get_position(TransformComponent const *const transformComp, PositionComponent const *const positionComp)
{
	if (positionComp)
	{
		return positionComp->position;
	}
	else if (transformComp)
	{
		return transformComp->transform.get_local_position();
	}
	else
	{
		return Math::ZERO;
	}
}

static void set_position(TransformComponent *const transformComp, PositionComponent *const positionComp, Float3 const &position)
{
	if (positionComp)
	{
		positionComp->position = position;
	}
	else if (transformComp)
	{
		transformComp->transform.set_local_position(position);
	}
}

static Quaternion get_rotation(TransformComponent const *const transformComp, RotationComponent const *const rotationComp)
{
	if (rotationComp)
	{
		return rotationComp->rotation;
	}
	else if (transformComp)
	{
		return transformComp->transform.get_local_rotation();
	}
	else
	{
		return Math::identity<Quaternion>();
	}
}

static void set_rotation(TransformComponent *const transformComp, RotationComponent *const rotationComp, Quaternion const &rotation)
{
	if (rotationComp)
	{
		rotationComp->rotation = rotation;
	}
	else if (transformComp)
	{
		transformComp->transform.set_local_rotation(rotation);
	}
}

static Float3 get_velocity(VelocityComponent const *const velocityComp)
{
	if (velocityComp)
	{
		return velocityComp->velocity;
	}
	else
	{
		return Math::ZERO;
	}
}

static void set_velocity(VelocityComponent *const velocityComp, Float3 const &velocity)
{
	if (velocityComp)
	{
		velocityComp->velocity = velocity;
	}
}

// update rigidbody values from entity components
static void set_rigidbody_values(Entity const entity, EntityManager &entityManager, Rigidbody &body)
{
	// if there is a parent, base this transform off of the parent's global transform
	TransformComponent const *const transformComp = entityManager.try_get_component<TransformComponent const>(entity);
	PositionComponent const *const positionComp = entityManager.try_get_component<PositionComponent const>(entity);
	RotationComponent const *const rotationComp = entityManager.try_get_component<RotationComponent const>(entity);
	VelocityComponent const *const velocityComp = entityManager.try_get_component<VelocityComponent const>(entity);
	Entity const parent = entityManager.get_parent(entity);
	TransformComponent const *const parentTransformComp = entityManager.try_get_component<TransformComponent const>(parent);
	PhysicsComponent &physicsComp = entityManager.get_or_add_component<PhysicsComponent>(entity);

	// set transform based on Position, Rotation, Scale components if they exist
	physicsComp.previousLocalPosition = get_position(transformComp, positionComp);
	physicsComp.previousLocalRotation = get_rotation(transformComp, rotationComp);
	physicsComp.previousVelocity = get_velocity(velocityComp);
	if (parentTransformComp)
	{
		physicsComp.previousGlobalPosition = parentTransformComp->transform.get_global_position() + physicsComp.previousLocalPosition;
		physicsComp.previousGlobalRotation = parentTransformComp->transform.get_global_rotation() + physicsComp.previousLocalRotation;
	}
	else
	{
		physicsComp.previousGlobalPosition = physicsComp.previousLocalPosition;
		physicsComp.previousGlobalRotation = physicsComp.previousLocalRotation;
	}
	body.set_simulation_position(physicsComp.previousGlobalPosition);
	body.set_simulation_rotation(physicsComp.previousGlobalRotation);
	body.set_simulation_linear_velocity(physicsComp.previousVelocity);
}

// update entity components from rigidbody values
static void get_rigidbody_values(Entity const entity, EntityManager &entityManager, Rigidbody &body)
{
	// if there is a parent, base this transform off of the parent's global transform
	TransformComponent *const transformComp = entityManager.try_get_component<TransformComponent>(entity);
	PositionComponent *const positionComp = entityManager.try_get_component<PositionComponent>(entity);
	RotationComponent *const rotationComp = entityManager.try_get_component<RotationComponent>(entity);
	VelocityComponent *const velocityComp = entityManager.try_get_component<VelocityComponent>(entity);
	Entity const parent = entityManager.get_parent(entity);
	TransformComponent const *const parentTransformComp = entityManager.try_get_component<TransformComponent const>(parent);
	PhysicsComponent const &physicsComp = entityManager.get_or_add_component<PhysicsComponent>(entity);

	// if a transform value was modified during a collision, then do not use the body's value: use the position

	Float3 localPosition = get_position(transformComp, positionComp);
	Float3 velocity = get_velocity(velocityComp);
	if (localPosition == physicsComp.previousLocalPosition)
	{
		// if the position was not modified during a collision, then update it based on the body's position
		if (parentTransformComp)
		{
			localPosition = body.get_simulation_position() - parentTransformComp->transform.get_global_position();
		}
		else
		{
			localPosition = body.get_simulation_position();
		}
		set_position(transformComp, positionComp, localPosition);
	}
	if(velocityComp && velocity == physicsComp.previousVelocity)
	{
		// if the velocity was not modified during a collision, then update it based on the body's velocity
		velocityComp->velocity = body.get_simulation_linear_velocity();
	}

	if (parentTransformComp)
	{
		if (rotationComp)
		{
			rotationComp->rotation = body.get_simulation_rotation() - parentTransformComp->transform.get_global_rotation();
		}
	}
	else
	{
		if (rotationComp)
		{
			rotationComp->rotation = body.get_simulation_rotation();
		}
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
	Layer layer, layerMask;

	// check for unregistered entities with physics components and register them

	// body and collider
	for (auto &&[entity, bodyComp, colliderComp] : entityManager.view<RigidbodyComponent const, ColliderComponent const, EnabledTag const>(entt::exclude<PhysicsRegisteredTag>).each())
	{
		if (!bodyComp.rigidbody)
		{
			MINTY_ERROR(ErrorCode::Component_InvalidState);
			continue;
		}

		if (!colliderComp.collider)
		{
			MINTY_ERROR(ErrorCode::Component_InvalidState);
			continue;
		}

		// get layer data
		layer = entityManager.get_layer(entity);
		layerMask = layerManager.get_mask(layer);

		// register the entity with the simulation, the position will be updated later since there is a rigidbody component
		m_simulation->register_entity(entity, layer, layerMask, *colliderComp.collider, *bodyComp.rigidbody);

		entityManager.add_component<PhysicsRegisteredTag>(entity);
	}

	// collider only
	for (auto &&[entity, colliderComp] : entityManager.view<ColliderComponent const, EnabledTag const>(entt::exclude<RigidbodyComponent, PhysicsRegisteredTag>).each())
	{
		if (!colliderComp.collider)
		{
			MINTY_ERROR(ErrorCode::Component_InvalidState);
			continue;
		}

		// get the world position of the entity for registering the collider in the correct place in the simulation
		Float3 worldPosition = Math::ZERO;
		TransformComponent const *const transformComp = entityManager.try_get_component<TransformComponent const>(entity);
		PositionComponent const *const positionComp = entityManager.try_get_component<PositionComponent const>(entity);
		if (positionComp)
		{
			worldPosition = positionComp->position;
		}
		else if (transformComp)
		{
			worldPosition = transformComp->transform.get_local_position();
		}

		// get layer data
		layer = entityManager.get_layer(entity);
		layerMask = layerManager.get_mask(layer);

		// register the entity with the simulation
		m_simulation->register_entity(entity, layer, layerMask, *colliderComp.collider, worldPosition);

		entityManager.add_component<PhysicsRegisteredTag>(entity);
	}

	// check for enabled entities with physics components that are not yet simulated and add them to the simulation
	for (auto &&[entity] : entityManager.view<PhysicsRegisteredTag const, EnabledTag const>(entt::exclude<PhysicsSimulationTag>).each())
	{
		m_simulation->add(entity);

		entityManager.add_component<PhysicsSimulationTag>(entity);
	}

	// check for disabled entities with physics components that are in the simulation and remove them from the simulation
	for (auto &&[entity] : entityManager.view<PhysicsSimulationTag const>(entt::exclude<EnabledTag>).each())
	{
		m_simulation->remove(entity);
		
		// if entity is dynamic, clear the physics component since that data is not being used and does not need to be saved
		entityManager.clear<PhysicsComponent>(entity);

		entityManager.remove_component<PhysicsSimulationTag>(entity);
	}
}

void Minty::PhysicsSystem::deinitialize_entities()
{
	// get scene and managers
	Ref<Scene> const &scene = get_scene_ref();
	MINTY_ASSERT(scene != nullptr, ErrorCode::Object_InvalidState);
	EntityManager &entityManager = scene->get_entity_manager();

	// clear simulation
	for (auto &&[entity] : entityManager.view<PhysicsSimulationTag const>().each())
	{
		m_simulation->remove(entity);
		
		// if entity is dynamic, clear the physics component since that data is not being used and does not need to be saved
		entityManager.clear<PhysicsComponent>(entity);

		entityManager.remove_component<PhysicsSimulationTag>(entity);
	}
	for (auto &&[entity] : entityManager.view<PhysicsRegisteredTag const>().each())
	{
		m_simulation->unregister_entity(entity);

		entityManager.remove_component<PhysicsRegisteredTag>(entity);
	}
}

void Minty::PhysicsSystem::update_simulated_entities(Timestep const time)
{
	Scene &scene = get_scene();
	EntityManager &entityManager = scene.get_entity_manager();

	// apply gravity to entities with GravityComponent
	for (auto const &[entity, bodyComp, gravityComp] : entityManager.view<RigidbodyComponent const, GravityComponent const, PhysicsSimulationTag const, EnabledTag const>().each())
	{
		// throw an error if no rigid body, somehow
		MINTY_ASSERT(bodyComp.rigidbody != nullptr, ErrorCode::Component_InvalidState);

		if (!bodyComp.rigidbody->is_dynamic())
		{
			// only apply to dynamic bodies
			continue;
		}

		// apply gravity force
		Float3 const gravityForce = gravityComp.scale * m_simulation->get_gravity();
		bodyComp.rigidbody->add_force(gravityForce, Force::Continuous);
	}
}

void Minty::PhysicsSystem::update_simulation_from_world(Timestep const time)
{
	Scene &scene = get_scene();
	EntityManager &entityManager = scene.get_entity_manager();

	for (auto const &[entity, bodyComp] : entityManager.view<RigidbodyComponent const, PhysicsSimulationTag const, EnabledTag const>().each())
	{
		if (bodyComp.rigidbody == nullptr)
		{
			MINTY_LOG_WARNING_F("Entity {} has no Rigidbody to update to simulation.", entityManager.to_string(entity));
			continue;
		}
		Rigidbody &body = *bodyComp.rigidbody;

		set_rigidbody_values(entity, entityManager, body);
	}
}

void Minty::PhysicsSystem::update_world_from_simulation(Timestep const time)
{
	Scene &scene = get_scene();
	EntityManager &entityManager = scene.get_entity_manager();

	for (auto &&[entity, bodyComp] : entityManager.view<RigidbodyComponent const, PhysicsSimulationTag const, EnabledTag const>().each())
	{
		if (bodyComp.rigidbody == nullptr)
		{
			MINTY_LOG_WARNING_F("Entity {} has no Rigidbody to update from simulation.", entityManager.to_string(entity));
			continue;
		}
		Rigidbody &body = *bodyComp.rigidbody;

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
	for (auto &&[entity, transformComp, physicsComp, bodyComp] : entityManager.view<TransformComponent, PhysicsComponent const, RigidbodyComponent const, PhysicsSimulationTag const, EnabledTag const>().each())
	{
		// if there is a parent, base this transform off of the parent's global transform
		TransformComponent const *parentTransformComp = entityManager.try_get_component<TransformComponent const>(entityManager.get_parent(entity));

		// set the transform based on Position, Rotation, Scale components if they exist
		if (parentTransformComp)
		{
			if (PositionComponent const *positionComp = entityManager.try_get_component<PositionComponent const>(entity))
			{
				Float3 const interpolatedPosition = Math::lerp(physicsComp.previousGlobalPosition, positionComp->position, alpha);
				transformComp.transform.set_local_position(interpolatedPosition - parentTransformComp->transform.get_global_position());
			}
			if (RotationComponent const *rotationComp = entityManager.try_get_component<RotationComponent const>(entity))
			{
				Quaternion const interpolatedRotation = Math::slerp(physicsComp.previousGlobalRotation, rotationComp->rotation, alpha);
				transformComp.transform.set_local_rotation(interpolatedRotation - parentTransformComp->transform.get_global_rotation());
			}
		}
		else
		{
			if (PositionComponent const *positionComp = entityManager.try_get_component<PositionComponent const>(entity))
			{
				Float3 const interpolatedPosition = Math::lerp(physicsComp.previousGlobalPosition, positionComp->position, alpha);
				transformComp.transform.set_local_position(interpolatedPosition);
			}
			if (RotationComponent const *rotationComp = entityManager.try_get_component<RotationComponent const>(entity))
			{
				Quaternion const interpolatedRotation = Math::slerp(physicsComp.previousGlobalRotation, rotationComp->rotation, alpha);
				transformComp.transform.set_local_rotation(interpolatedRotation);
			}
		}

		entityManager.dirty(entity);
	}

	// if a snap size is set, snap entities to the grid
	if (m_snapSize > 0.0f)
	{
		for (auto &&[entity, transformComp] : entityManager.view<TransformComponent, SnapTag const, PhysicsSimulationTag const, EnabledTag const>().each())
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

	// check for entities marked for destruction and remove them from the simulation
	for (auto &&[entity] : entityManager.view<DestroyTag const, PhysicsSimulationTag const>().each())
	{
		m_simulation->remove(entity);
		
		// if entity is dynamic, clear the physics component since that data is not being used and does not need to be saved
		entityManager.clear<PhysicsComponent>(entity);

		entityManager.remove_component<PhysicsSimulationTag>(entity);
	}
	for (auto &&[entity] : entityManager.view<DestroyTag const, PhysicsRegisteredTag const>().each())
	{
		m_simulation->unregister_entity(entity);

		entityManager.remove_component<PhysicsRegisteredTag>(entity);
	}
}
