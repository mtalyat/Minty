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
		void add_static(Transform const& transform, Collider& collider, Layer const layer) override;
		void add_dynamic(Transform const& transform, Collider& collider, RigidBody& body, Layer const layer) override;
		void remove_static(Collider& collider) override;
		void remove_dynamic(Collider& collider, RigidBody& body) override;
		void set_dynamic(Transform const& transform, Collider const& collider, RigidBody const& body) override;
		void get_dynamic(Transform& transform, Collider const& collider, RigidBody& body) override;
		void clear() override;

#pragma endregion
	};
}