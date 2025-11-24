#pragma once
#include "Minty/Core/Math.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Transform.h"
#include "Minty/Manager/Manager.h"
#include "Minty/Physics/Collider.h"
#include "Minty/Physics/RaycastHit.h"
#include "Minty/Physics/RigidBody.h"

namespace Minty
{
	/// <summary>
	/// The arguments for a PhysicsManager.
	/// </summary>
	struct PhysicsManagerInfo
	{
	};

	/// <summary>
	/// Handles physics in a Scene.
	/// </summary>
	class PhysicsManager
		: public Manager
	{
#pragma region Variables

	private:

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new PhysicsManager with the given arguments.
		/// </summary>
		/// <param name="info">The arguments.</param>
		PhysicsManager(PhysicsManagerInfo const& info)
			: Manager()
		{
		}

		~PhysicsManager() override
		{
		}

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Creates a new PhysicsManager with the given arguments.
		/// </summary>
		/// <param name="info">The arguments.</param>
		/// <returns>A PhysicsManager Owner.</returns>
		static Owner<PhysicsManager> create(PhysicsManagerInfo const& info);

		/// <summary>
		/// Gets the singleton PhysicsManager for the active Scene.
		/// </summary>
		/// <returns>The PhysicsManager.</returns>
		static PhysicsManager& get_singleton();

#pragma endregion
	};
}