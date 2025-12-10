#ifndef MINTY_SYSTEM_PHYSICSSYSTEM_H
#define MINTY_SYSTEM_PHYSICSSYSTEM_H

/**
 * @file PhysicsSystem.h
 * @brief Header file defining the PhysicsSystem class.
 * @author Mitchell Talyat
 */

#include "Minty/System/System.h"
#include "Minty/Physics/PhysicsSimulation.h"

namespace Minty
{
	/**
	 * @brief Handles physics in a Scene.
	 */
	class PhysicsSystem
		: public System
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a PhysicsSystem using the given SystemInfo.
		 */
		PhysicsSystem(SystemInfo const &info);

		~PhysicsSystem() override = default;

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the PhysicsSimulation used by this PhysicsSystem.
		 * @return The simulation.
		 */
		inline PhysicsSimulation &get_simulation() const { return *m_simulation; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Called when the Scene is loaded.
		 */
		void on_load() override;

		/**
		 * @brief Called when the Scene is unloaded.
		 */
		void on_unload() override;

		/**
		 * @brief Called when the Scene is frame updated.
		 * @param time The time information for the frame update.
		 */
		void on_frame_update(Timestep const time) override;

		/**
		 * @brief Called when the Scene is fixed updated.
		 * @param time The time information for the fixed update.
		 */
		void on_fixed_update(Timestep const time) override;

		/**
		 * @brief Called when the Scene is finalized.
		 */
		void on_finalize() override;

	private:
		// init entities that are not yet simulated
		void initialize_entities();

		// deinit entities marked for destruction
		void deinitialize_entities();

		void update_simulated_entities(Timestep const time);

		void update_simulation_from_world(Timestep const time);

		void update_world_from_simulation(Timestep const time);

#pragma endregion

#pragma region Variables

	private:
		Shared<PhysicsSimulation> m_simulation;
		Timestep m_lastUpdateTimestep;

#pragma endregion
	};
}

#endif // MINTY_SYSTEM_PHYSICSSYSTEM_H