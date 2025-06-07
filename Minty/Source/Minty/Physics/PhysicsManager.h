#pragma once
#include "Minty/Core/Math.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Manager/SubManager.h"
#include "Minty/Physics/Collider.h"
#include "Minty/Physics/RaycastHit.h"
#include "Minty/Physics/RigidBody.h"
#include "Minty/Data/Transform.h"

namespace Minty
{
	/// <summary>
	/// The arguments for a PhysicsManager.
	/// </summary>
	struct PhysicsManagerBuilder
	{
		/// <summary>
		/// The gravity vector applied to all Entities in the Scene.
		/// </summary>
		Float3 gravity = Float3(0.0f, DEFAULT_PHYSICS_GRAVITY, 0.0f);
	};

	/// <summary>
	/// Handles physics in a Scene.
	/// </summary>
	class PhysicsManager
		: public SubManager
	{
#pragma region Variables

	private:
		// accumulated time pass ed
		Float m_accumulator = 0.0f;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new PhysicsManager with the given arguments.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		PhysicsManager(Scene* scene, PhysicsManagerBuilder const& builder)
			: SubManager(scene)
			, m_accumulator(0.0f)
		{
		}

		~PhysicsManager() override
		{
		}

#pragma endregion

#pragma region Methods

	public:	
		/// <summary>
		/// Called every frame.
		/// </summary>
		void update(Time const& time) override;

		/// <summary>
		/// Performs a single step of physics simulation.
		/// </summary>
		virtual void step(Float const elapsedTime) = 0;

		/// <summary>
		/// Casts a ray into the world and attempts to collide with any Entities that have a Collider Component.
		/// </summary>
		/// <param name="origin"></param>
		/// <param name="direction"></param>
		/// <param name="hit"></param>
		/// <param name="maxDistance"></param>
		/// <param name="layerMask"></param>
		/// <returns></returns>
		//Bool raycast(Float3 const& origin, Float3 const& direction, RaycastHit& hit, Float maxDistance = Math::INF, Layer const layerMask = LAYER_ALL) const;

		/// <summary>
		/// Adds a static Collider to the physics simulation.
		/// </summary>
		/// <param name="transform">The Transform.</param>
		/// <param name="collider">The Collider.</param>
		virtual void add_static(Transform const& transform, Collider& collider) = 0;

		/// <summary>
		/// Adds a dynamic Collider with a RigidBody to the physics simulation.
		/// </summary>
		/// <param name="transform">The Transform.</param>
		/// <param name="collider">The Collider.</param>
		/// <param name="body">The RigidBody.</param>
		virtual void add_dynamic(Transform const& transform, Collider& collider, RigidBody& body) = 0;

		/// <summary>
		/// Removes a static Collider from the physics simulation.
		/// </summary>
		/// <param name="collider">The Collider.</param>
		virtual void remove_static(Collider& collider) = 0;

		/// <summary>
		/// Removes a dynamic Collider with a RigidBody from the physics simulation.
		/// </summary>
		/// <param name="collider">The Collider.</param>
		/// <param name="body">The RigidBody.</param>
		virtual void remove_dynamic(Collider& collider, RigidBody& body) = 0;

		/// <summary>
		/// Updates the transform of a dynamic Collider with a RigidBody in the physics simulation.
		/// </summary>
		/// <param name="transform">The Transform.</param>
		/// <param name="collider">The Collider.</param>
		/// <param name="body">The RigidBody.</param>
		virtual void set_dynamic(Transform const& transform, Collider const& collider, RigidBody const& body) = 0;
		
		/// <summary>
		/// Updates the transform from a dynamic Collider with a RigidBody in the physics simulation.
		/// </summary>
		/// <param name="transform">The Transform.</param>
		/// <param name="collider">The Collider.</param>
		/// <param name="body">The RigidBody.</param>
		virtual void get_dynamic(Transform& transform, Collider const& collider, RigidBody& body) = 0;

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Creates a new PhysicsManager with the given arguments.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		/// <returns>A PhysicsManager Owner.</returns>
		static Owner<PhysicsManager> create(Scene* scene, PhysicsManagerBuilder const& builder);

		/// <summary>
		/// Gets the singleton PhysicsManager for the active Scene.
		/// </summary>
		/// <returns>The PhysicsManager.</returns>
		static PhysicsManager& get_singleton();

#pragma endregion

	};
}