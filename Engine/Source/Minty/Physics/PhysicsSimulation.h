#ifndef MINTY_PHYSICS_PHYSICSSIMULATION_H
#define MINTY_PHYSICS_PHYSICSSIMULATION_H

/**
 * @file PhysicsSimulation.h
 * @brief Header file defining the PhysicsSimulation class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Constant.h"
#include "Minty/Core/Math.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Entity/Entity.h"

namespace Minty
{
	struct PhysicsSimulationInfo;
	class Transform;
	class Collider;
	class RigidBody;
	struct RaycastHit;

	/**
	 * @brief Simulates physics.
	 */
	class PhysicsSimulation
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a new PhysicsSimulation with the given arguments.
		 * @param info The arguments.
		 */
		PhysicsSimulation(PhysicsSimulationInfo const& info);

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Sets the gravity vector applied to all objects in the simulation.
		 * @param gravity The gravity vector.
		 */
		inline virtual void set_gravity(Float3 const& gravity) { m_gravity = gravity; }

		/**
		 * @brief Gets the gravity vector applied to all objects in the simulation.
		 * @return The gravity vector.
		 */
		inline Float3 const& get_gravity() const { return m_gravity; }

		/**
		 * @brief Gets the number of objects in the simulation.
		 * @return The number of objects.
		 */
		virtual Size get_size() const = 0;

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Performs a single step of physics simulation.
		 * @param elapsedTime The elapsed time since the last step.
		 */
		virtual void step(Float const elapsedTime) = 0;

		/**
		 * @brief Adds a static Collider to the physics simulation.
		 * @param entity The Entity.
		 * @param transform The Transform.
		 * @param collider The Collider.
		 * @param layer The Layer.
		 * @param layerMask The Layer mask.
		 */
		virtual void add_static(Entity const entity, Transform const& transform, Collider& collider, Layer const layer = LAYER_DEFAULT, Layer const layerMask = LAYER_MASK_ALL) = 0;

		/**
		 * @brief Adds a dynamic Collider with a RigidBody to the physics simulation.
		 * @param entity The Entity.
		 * @param transform The Transform.
		 * @param collider The Collider.
		 * @param body The RigidBody.
		 * @param layer The Layer.
		 * @param layerMask The Layer mask.
		 */
		virtual void add_dynamic(Entity const entity, Transform const& transform, Collider& collider, RigidBody& body, Layer const layer = LAYER_DEFAULT, Layer const layerMask = LAYER_MASK_ALL) = 0;

		/**
		 * @brief Removes a static Collider from the physics simulation.
		 * @param collider The Collider.
		 */
		virtual void remove_static(Collider& collider) = 0;

		/**
		 * @brief Removes a dynamic Collider with a RigidBody from the physics simulation.
		 * @param collider The Collider.
		 * @param body The RigidBody.
		 */
		virtual void remove_dynamic(Collider& collider, RigidBody& body) = 0;

		/**
		 * @brief Updates the transform of a dynamic Collider with a RigidBody in the physics simulation.
		 * @param transform The Transform.
		 * @param collider The Collider.
		 * @param body The RigidBody.
		 */
		virtual void set_dynamic(Transform const& transform, Collider const& collider, RigidBody const& body) = 0;

		/**
		 * @brief Updates the transform from a dynamic Collider with a RigidBody in the physics simulation.
		 * @param transform The Transform.
		 * @param collider The Collider.
		 * @param body The RigidBody.
		 */
		virtual void get_dynamic(Transform& transform, Collider const& collider, RigidBody& body) = 0;

		/**
		 * @brief Performs a raycast in the physics simulation.
		 * @param origin The origin of the ray.
		 * @param direction The direction of the ray.
		 * @param hit The RaycastHit information to be populated on a successful hit.
		 * @param layer The Layer.
		 * @param layerMask The Layer mask to use.
		 * @param maxDistance The maximum amount of distance to travel.
		 * @return True if an object was hit, otherwise false.
		 */
		virtual Bool raycast(Float3 const& origin, Float3 const& direction, RaycastHit& hit, Layer const layer = LAYER_DEFAULT, Layer const layerMask = LAYER_MASK_ALL, Float const maxDistance = DEFAULT_PHYSICS_RAYCAST_DISTANCE) const = 0;

		/**
		 * @brief Clears all physics objects from the simulation.
		 */
		virtual void clear() = 0;

		/**
		 * @brief Creates a new PhysicsSimulation with the given arguments.
		 * @param info The arguments.
		 * @return A PhysicsSimulation Owner.
		 */
		static Shared<PhysicsSimulation> create(PhysicsSimulationInfo const& info);

		/**
		 * @brief Creates a default PhysicsSimulation.
		 * @return A PhysicsSimulation Owner.
		 */
		static Shared<PhysicsSimulation> create();

#pragma endregion

#pragma region Variables

	private:
		Float3 m_gravity;

#pragma endregion
	};
}

#endif // MINTY_PHYSICS_PHYSICSSIMULATION_H