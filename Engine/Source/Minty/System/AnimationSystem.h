#ifndef MINTY_SYSTEM_ANIMATIONSYSTEM_H
#define MINTY_SYSTEM_ANIMATIONSYSTEM_H

/**
 * @file AnimationSystem.h
 * @brief Header file defining the AnimationSystem class.
 * @author Mitchell Talyat
 */

#include "Minty/System/System.h"

namespace Minty
{
	/**
	 * @brief Controls the animation of entities.
	 */
	class AnimationSystem
		: public System
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates an AnimationSystem using the given arguments.
		 * @param info The arguments.
		 */
		AnimationSystem(SystemInfo const& info)
			: System(info)
		{}

		~AnimationSystem() override = default;

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Called when the Scene is updated.
		 * @param time
		 */
		void on_frame_update(Timestep const& time) override;

#pragma endregion
	};
}

#endif // MINTY_SYSTEM_ANIMATIONSYSTEM_H