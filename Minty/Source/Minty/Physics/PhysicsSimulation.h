#pragma once
#include "Minty/Core/Constant.h"
#include "Minty/Core/Math.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Transform.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Physics/Collider.h"
#include "Minty/Physics/RaycastHit.h"
#include "Minty/Physics/RigidBody.h"

namespace Minty
{
	class PhysicsManager;
	class LayerManager;

	/// <summary>
	/// The arguments to create a PhysicsSimulation.
	/// </summary>
	struct PhysicsSimulationBuilder
	{
		/// <summary>
		/// The gravity vector applied to all objects in the simulation.
		/// </summary>
		Float3 gravity = Float3(0.0f, DEFAULT_PHYSICS_GRAVITY, 0.0f);

		/// <summary>
		/// The PhysicsManager this PhysicsSimulation uses.
		/// </summary>
		Ref<PhysicsManager> physicsManager = nullptr;

		/// <summary>
		/// The LayerManager this PhysicsSimulation uses.
		/// </summary>
		Ref<LayerManager> layerManager = nullptr;
	};

	/// <summary>
	/// Simulates physics.
	/// </summary>
	class PhysicsSimulation
	{
#pragma region Variables

	private:
		Float3 m_gravity;
		Ref<PhysicsManager> m_physicsManager;
		Ref<LayerManager> m_layerManager;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new PhysicsSimulation with the given arguments.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		PhysicsSimulation(PhysicsSimulationBuilder const& builder);

#pragma endregion

#pragma region Get Set

	protected:
		inline PhysicsManager& get_physics_manager() const
		{
			return *m_physicsManager;
		}

		inline LayerManager& get_layer_manager() const
		{
			return *m_layerManager;
		}

	public:
		/// <summary>
		/// Sets the gravity vector applied to all objects in the simulation.
		/// </summary>
		/// <param name="gravity">The gravity vector.</param>
		inline virtual void set_gravity(Float3 const& gravity)
		{
			m_gravity = gravity;
		}

		/// <summary>
		/// Gets the gravity vector applied to all objects in the simulation.
		/// </summary>
		/// <returns>The gravity vector.</returns>
		inline Float3 const& get_gravity() const
		{
			return m_gravity;
		}

		/// <summary>
		/// Gets the number of objects in the simulation.
		/// </summary>
		/// <returns>The number of objects.</returns>
		virtual Size get_size() const = 0;

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Performs a single step of physics simulation.
		/// </summary>
		virtual void step(Float const elapsedTime) = 0;

		/// <summary>
		/// Adds a static Collider to the physics simulation.
		/// </summary>
		/// <param name="transform">The Transform.</param>
		/// <param name="collider">The Collider.</param>
		virtual void add_static(Entity const entity, Transform const& transform, Collider& collider, Layer const layer = LAYER_DEFAULT, Layer const layerMask = LAYER_ALL) = 0;

		/// <summary>
		/// Adds a dynamic Collider with a RigidBody to the physics simulation.
		/// </summary>
		/// <param name="transform">The Transform.</param>
		/// <param name="collider">The Collider.</param>
		/// <param name="body">The RigidBody.</param>
		virtual void add_dynamic(Entity const entity, Transform const& transform, Collider& collider, RigidBody& body, Layer const layer = LAYER_DEFAULT, Layer const layerMask = LAYER_ALL) = 0;

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

		/// <summary>
		/// Performs a raycast in the physics simulation.
		/// </summary>
		/// <param name="origin">The origin of the ray.</param>
		/// <param name="direction">The direction of the ray.</param>
		/// <param name="hit">The RaycastHit information to be populated on a successful hit.</param>
		/// <param name="layerMask">The Layer mask to use.</param>
		/// <param name="maxDistance">The maximum amount of distance to travel.</param>
		/// <returns>True if an object was hit, otherwise false.</returns>
		virtual Bool raycast(Float3 const& origin, Float3 const& direction, RaycastHit& hit, Layer const layerMask = LAYER_ALL, Float const maxDistance = DEFAULT_PHYSICS_RAYCAST_DISTANCE) const = 0;

		/// <summary>
		/// Clears all physics objects from the simulation.
		/// </summary>
		virtual void clear() = 0;

#pragma endregion

#pragma region Statics

		/// <summary>
		/// Creates a new PhysicsSimulation with the given arguments.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		/// <returns>A PhysicsSimulation Owner.</returns>
		static Owner<PhysicsSimulation> create(PhysicsSimulationBuilder const& builder);

#pragma endregion

	};
}