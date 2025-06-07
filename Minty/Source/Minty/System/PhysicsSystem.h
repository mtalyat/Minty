#pragma once
#include "Minty/System/System.h"

namespace Minty
{
	/// <summary>
	/// Handles physics in a Scene.
	/// </summary>
	class PhysicsSystem
		: public System
	{
#pragma region Constructors

	public:
		PhysicsSystem(SystemBuilder const& builder);

		~PhysicsSystem() override
		{
		}

#pragma endregion

#pragma region Methods

	private:
		// init entities that are not yet simulated
		void initialize_entities();

		// deinit entities marked for destruction
		void deinitialize_entities();

	public:
		/// <summary>
		/// Called when the Scene is loaded.
		/// </summary>
		void on_load() override;

		/// <summary>
		/// Called when the Scene is unloaded.
		/// </summary>
		void on_unload() override;

		/// <summary>
		/// Called when the Scene is updated.
		/// </summary>
		/// <param name="time"></param>
		void on_update(Time const& time) override;

#pragma endregion

	};
}