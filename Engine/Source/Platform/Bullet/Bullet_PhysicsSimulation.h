#pragma once
#include "Minty/Library/Bullet.h"
#include "Minty/Physics/PhysicsSimulation.h"
#include "Minty/Data/Set.h"
#include "Minty/Data/Tuple.h"

namespace Minty
{
	// Collision pair for tracking collisions between objects
	struct CollisionPair
	{
		AnyConst a;
		AnyConst b;

		CollisionPair(AnyConst objA, AnyConst objB)
			: a(objA < objB ? objA : objB), b(objA < objB ? objB : objA)
		{
		}

		inline Bool operator==(CollisionPair const &other) const
		{
			return a == other.a && b == other.b;
		}

		inline Bool operator<(CollisionPair const &other) const
		{
			if (a != other.a)
				return a < other.a;
			return b < other.b;
		}

		inline Bool contains(AnyConst obj) const
		{
			return a == obj || b == obj;
		}
	};
}

// Hash function for CollisionPair
namespace std
{
	template <>
	struct hash<Minty::CollisionPair>
	{
		size_t operator()(Minty::CollisionPair const &pair) const
		{
			uintptr_t ptrA = reinterpret_cast<uintptr_t>(pair.a);
			uintptr_t ptrB = reinterpret_cast<uintptr_t>(pair.b);
			return ptrA ^ (ptrB << 1);
		}
	};
}

namespace Minty
{
	class Bullet_PhysicsSimulation
		: public PhysicsSimulation
	{
#pragma region Constructors

	public:
		Bullet_PhysicsSimulation(PhysicsSimulationInfo const &info);

		~Bullet_PhysicsSimulation() override;

#pragma endregion

#pragma region Accessors

	public:
		Size get_size() const override;

		void set_gravity(Float3 const &gravity) override;

#pragma endregion

#pragma region Methods

	public:
		void step(Float const elapsedTime) override;
		void add_static(Entity const entity, Transform const &transform, Collider &collider, Layer const layer, Layer const layerMask) override;
		void add_dynamic(Entity const entity, RigidBody &body, Layer const layer, Layer const layerMask) override;
		void remove_static(Collider &collider) override;
		void remove_dynamic(RigidBody &body) override;
		Bool raycast(Float3 const &origin, Float3 const &direction, RaycastHit &hit, Layer const layer = LAYER_DEFAULT, Layer const layerMask = LAYER_MASK_ALL, Float const maxDistance = DEFAULT_PHYSICS_RAYCAST_DISTANCE) const override;
		void clear() override;

	private:
		// removes all collisions involving the given object
		void remove_collisions_for_object(AnyConst object);

#pragma endregion

#pragma region Variables

	private:
		btBroadphaseInterface *mp_broadphase;
		btDefaultCollisionConfiguration *mp_collisionConfiguration;
		btCollisionDispatcher *mp_dispatcher;
		btSequentialImpulseConstraintSolver *mp_solver;
		btDiscreteDynamicsWorld *mp_dynamicsWorld;
		Set<CollisionPair> m_previousCollisions;
		Set<CollisionPair> m_currentCollisions;

#pragma endregion
	};
}