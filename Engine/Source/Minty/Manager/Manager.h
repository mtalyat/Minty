#ifndef MINTY_MANAGER_MANAGER_H
#define MINTY_MANAGER_MANAGER_H

/**
 * @file Manager.h
 * @brief Header file for the base Manager class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Time/Timestep.h"

namespace Minty
{
	class Event;

	/**
	 * @brief Base class for all Managers in the engine.
	 */
	class Manager
	{
#pragma region Constructors

	public:
		Manager() = default;
		virtual ~Manager() = default;

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Called once a frame.
		 * @param time The time information for the frame.
		 */
		virtual void frame_update(Timestep const time) {}

		/**
		 * @brief Called at a fixed interval.
		 * @param time The time information for the update.
		 */
		virtual void fixed_update(Timestep const time) {}

		/**
		 * @brief Called at the end of the frame to finalize operations.
		 */
		virtual void finalize() {}

		/**
		 * @brief Called once per frame to perform any rendering operations.
		 */
		virtual void render() {}

		/**
		 * @brief Synchronizes the Manager state.
		 */
		virtual void sync() {}

		/**
		 * @brief Handles an event sent to this Manager.
		 * @param event The event to handle.
		 */
		virtual void handle_event(Event& event) {}

#pragma endregion
	};
}

#endif // MINTY_MANAGER_MANAGER_H