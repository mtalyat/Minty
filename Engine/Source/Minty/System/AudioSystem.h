#ifndef MINTY_SYSTEM_AUDIOSYSTEM_H
#define MINTY_SYSTEM_AUDIOSYSTEM_H

/**
 * @file AudioSystem.h
 * @brief Header file defining the AudioSystem class.
 * @author Mitchell Talyat
 */

#include "Minty/System/System.h"

namespace Minty
{
	/**
	 * @brief Manages audio playback within a Scene.
	 */
	class AudioSystem
		: public System
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a new AudioSystem using the given SystemInfo.
		 */
		AudioSystem(SystemInfo const& info);

		~AudioSystem() override = default;

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Called when the Scene is unloaded.
		 */
		void on_unload() override;

		/**
		 * @brief Called when the Scene is finalized.
		 */
		void on_finalize() override;

#pragma endregion
	};
}

#endif // MINTY_SYSTEM_AUDIOSYSTEM_H