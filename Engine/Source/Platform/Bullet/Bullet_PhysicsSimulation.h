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
		Bullet_PhysicsSimulation(PhysicsSimulationInfo const& info);

#pragma endregion

#pragma region Accessors

	public:
		Size get_size() const override;

		void set_gravity(Float3 const& gravity) override;

#pragma endregion

#pragma region Methods

	public:
		void step(Float const elapsedTime) override;
		void add_static(Entity const entity, Transform const& transform, Collider& collider, Layer const layer, Layer const layerMask) override;
		void add_dynamic(Entity const entity, RigidBody& body, Layer const layer, Layer const layerMask) override;
		void remove_static(Collider& collider) override;
		void remove_dynamic(RigidBody& body) override;
		Bool raycast(Float3 const& origin, Float3 const& direction, RaycastHit& hit, Layer const layer = LAYER_DEFAULT, Layer const layerMask = LAYER_MASK_ALL, Float const maxDistance = DEFAULT_PHYSICS_RAYCAST_DISTANCE) const override;
		void clear() override;

#pragma endregion
	};
}