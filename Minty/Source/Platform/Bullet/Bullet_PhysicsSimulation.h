#pragma once
#include "Minty/Library/Bullet.h"
#include "Minty/Physics/PhysicsSimulation.h"

namespace Minty
{
	class Bullet_PhysicsSimulation
		: public PhysicsSimulation
	{
#pragma region Variables

	private:
		btBroadphaseInterface* mp_broadphase;
		btDefaultCollisionConfiguration* mp_collisionConfiguration;
		btCollisionDispatcher* mp_dispatcher;
		btSequentialImpulseConstraintSolver* mp_solver;
		btDiscreteDynamicsWorld* mp_dynamicsWorld;

#pragma endregion

#pragma region Constructors

	public:
		Bullet_PhysicsSimulation(PhysicsSimulationBuilder const& builder);

#pragma endregion

#pragma region Get Set

	public:
		Size get_size() const override;

		void set_gravity(Float3 const& gravity) override;

#pragma endregion

#pragma region Methods

	public:
		void step(Float const elapsedTime) override;
		void add_static(Entity const entity, Transform const& transform, Collider& collider, Layer const layer = LAYER_DEFAULT, Layer const layerMask = LAYER_ALL) override;
		void add_dynamic(Entity const entity, Transform const& transform, Collider& collider, RigidBody& body, Layer const layer = LAYER_DEFAULT, Layer const layerMask = LAYER_ALL) override;
		void remove_static(Collider& collider) override;
		void remove_dynamic(Collider& collider, RigidBody& body) override;
		void set_dynamic(Transform const& transform, Collider const& collider, RigidBody const& body) override;
		void get_dynamic(Transform& transform, Collider const& collider, RigidBody& body) override;
		Bool raycast(Float3 const& origin, Float3 const& direction, RaycastHit& hit, Layer const layerMask = LAYER_ALL, Float const maxDistance = DEFAULT_PHYSICS_RAYCAST_DISTANCE) const override;
		void clear() override;

#pragma endregion
	};
}