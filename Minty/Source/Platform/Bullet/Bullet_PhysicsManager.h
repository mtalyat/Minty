#pragma once
#include "Minty/Data/Transform.h"
#include "Minty/Library/Bullet.h"
#include "Minty/Physics/PhysicsManager.h"

namespace Minty
{
	class Bullet_PhysicsManager
		: public PhysicsManager
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
		Bullet_PhysicsManager(Scene* scene, PhysicsManagerBuilder const& builder);

		~Bullet_PhysicsManager() override;

#pragma endregion

#pragma region Methods

	public:
		void step(Float const elapsedTime) override;

		/// <summary>
		/// Called when the Manager is created.
		/// </summary>
		void initialize() override;

		/// <summary>
		/// Called when the Manager is destroyed.
		/// </summary>
		void dispose() override;

		void add_static(Transform const& transform, Collider& collider) override;

		void add_dynamic(Transform const& transform, Collider& collider, RigidBody& body) override;

		void remove_static(Collider& collider) override;

		void remove_dynamic(Collider& collider, RigidBody& body) override;

		void set_dynamic(Transform const& transform, Collider const& collider, RigidBody const& body) override;

		void get_dynamic(Transform& transform, Collider const& collider, RigidBody& body) override;

#pragma endregion

#pragma region Statics

	public:
		static btTransform to_bullet(Transform const& transform)
		{
			btTransform btTransform;
			btTransform.setIdentity();
			btTransform.setOrigin(to_bullet(transform.get_global_position()));
			btTransform.setRotation(to_bullet(transform.get_global_rotation()));
			return btTransform;
		}

		inline static btVector3 to_bullet(Float3 const& vector)
		{
			return btVector3(vector.x, vector.y, vector.z);
		}

		inline static btQuaternion to_bullet(Quaternion const& quaternion)
		{
			return btQuaternion(quaternion.x, quaternion.y, quaternion.z, quaternion.w);
		}

#pragma endregion

	};
}