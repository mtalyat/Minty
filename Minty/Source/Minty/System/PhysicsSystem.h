#pragma once
#include "Minty/System/System.h"
#include "Minty/Physics/PhysicsSimulation.h"

namespace Minty
{
	/// <summary>
	/// Handles physics in a Scene.
	/// </summary>
	class PhysicsSystem
		: public System
	{
#pragma region Variables

	private:
		Owner<PhysicsSimulation> m_simulation;
		Float m_accumulator;

#pragma endregion

#pragma region Constructors

	public:
		PhysicsSystem(SystemBuilder const& builder);

		~PhysicsSystem() override
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the PhysicsSimulation used by this PhysicsSystem.
		/// </summary>
		/// <returns>The simulation.</returns>
		PhysicsSimulation& get_simulation() const
		{
			return *m_simulation;
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

		/// <summary>
		/// Called when the Scene is finalized.
		/// </summary>
		void on_finalize() override;

#pragma endregion
	};
}