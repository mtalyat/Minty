#ifndef MINTY_PHYSICS_PHYSICSMANAGER_H
#define MINTY_PHYSICS_PHYSICSMANAGER_H

/**
 * @file PhysicsManager.h
 * @brief Header file defining the PhysicsManager class.
 * @author Mitchell Talyat
 */

#include "Minty/Data/Pointer.h"
#include "Minty/Manager/Manager.h"

namespace Minty
{
	struct PhysicsManagerInfo;

	/**
	 * @brief Handles physics in a Scene.
	 */
	class PhysicsManager
		: public Manager
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a new PhysicsManager with the given arguments.
		 * @param info The arguments.
		 */
		PhysicsManager(PhysicsManagerInfo const& info);

		~PhysicsManager() override = default;

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Creates a new PhysicsManager with the given arguments.
		 * @param info The arguments.
		 * @return A PhysicsManager Owner.
		 */
		static Unique<PhysicsManager> create(PhysicsManagerInfo const& info);

		/**
		 * @brief Creates a new PhysicsManager with default settings.
		 * @return A PhysicsManager Owner.
		 */
		static Unique<PhysicsManager> create();

		/**
		 * @brief Gets the singleton PhysicsManager for the active Scene.
		 * @return The PhysicsManager.
		 */
		static PhysicsManager& get_singleton();

#pragma endregion
	};
}

#endif // MINTY_PHYSICS_PHYSICSMANAGER_H