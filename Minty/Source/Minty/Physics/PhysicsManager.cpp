#include "pch.h"
#include "PhysicsManager.h"
#include "Minty/Component/ColliderComponent.h"
#include "Minty/Component/RigidBodyComponent.h"
#include "Minty/Component/SimulateComponent.h"
#include "Minty/Component/TransformComponent.h"
#include "Minty/Context/Context.h"
#include "Minty/Scene/Scene.h"
#include "Minty/Scene/SceneManager.h"
#ifdef MINTY_BULLET
#include "Platform/Bullet/Bullet_PhysicsManager.h"
#endif

using namespace Minty;

void Minty::PhysicsManager::update(Time const& time)
{
	// get time passed
	m_accumulator += time.get_elapsed();

	// only perform actions if it is time for at least one step
	if (m_accumulator >= DEFAULT_PHYSICS_TIME_STEP)
	{
		// sync world objects to the physics simulation
		Scene& scene = get_scene();
		EntityManager& entityManager = scene.get_entity_manager();
		for (auto const& [entity, transform, collider, body, simulate] : entityManager.view<TransformComponent const, ColliderComponent const, RigidBodyComponent const, SimulateComponent const>().each())
		{
			set_dynamic(transform.transform, *collider.collider, *body.rigidBody);
		}

		// take steps
		while (m_accumulator >= DEFAULT_PHYSICS_TIME_STEP)
		{
			step(DEFAULT_PHYSICS_TIME_STEP);
			m_accumulator -= DEFAULT_PHYSICS_TIME_STEP;
		}

		// sync physics simulation objects to the world
		for (auto&& [entity, transform, collider, body, simulate] : entityManager.view<TransformComponent, ColliderComponent const, RigidBodyComponent const, SimulateComponent const>().each())
		{
			get_dynamic(transform.transform, *collider.collider, *body.rigidBody);
		}
	}
}

Owner<PhysicsManager> Minty::PhysicsManager::create(Scene* scene, PhysicsManagerBuilder const& builder)
{
#if defined(MINTY_BULLET)
	return Owner<Bullet_PhysicsManager>(scene, builder);
#else
	return Owner<PhysicsManager>();
#endif
}

PhysicsManager& Minty::PhysicsManager::get_singleton()
{
	// get the active scene
	Ref<Scene> const& activeScene = Context::get_singleton().get_scene_manager().get_active();
	MINTY_ASSERT(activeScene != nullptr, "No active scene. Cannot get PhysicsManager.");
	return activeScene->get_physics_manager();
}
