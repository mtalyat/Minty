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
	struct PhysicsManagerBuilder
	{
		/// <summary>
		/// The layer collision matrix.
		/// </summary>
		Vector<Tuple<String, Layer, Layer>> layerCollisions = {
			{ "None", LAYER_NONE, LAYER_NONE },
			{ "Default", LAYER_DEFAULT, LAYER_ALL }
		};
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
		/// <param name="builder">The arguments.</param>
		PhysicsManager(PhysicsManagerBuilder const& builder)
			: Manager()
		{
		}

		~PhysicsManager() override
		{
		}

#pragma endregion

#pragma region Get Set

	public:

#pragma endregion

#pragma region Methods

	public:

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Creates a new PhysicsManager with the given arguments.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		/// <returns>A PhysicsManager Owner.</returns>
		static Owner<PhysicsManager> create(PhysicsManagerBuilder const& builder);

		/// <summary>
		/// Gets the singleton PhysicsManager for the active Scene.
		/// </summary>
		/// <returns>The PhysicsManager.</returns>
		static PhysicsManager& get_singleton();

#pragma endregion
	};
}