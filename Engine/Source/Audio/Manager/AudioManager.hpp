#pragma once

/**
 * @file AudioManager.h
 * @brief Header file defining the AudioManager class.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Core/Data/Unique.hpp"
#include "Audio/Type/Handle.hpp"
#include "Resource/Type/Handle.hpp"

namespace Minty
{
	struct AudioSourceInfo;
	struct AudioListenerInfo;
	struct AudioManagerInfo;
	class AudioSource;
	class AudioListener;
	class AudioClip;
	class ResourceManager;
	struct ClipInfo;

	/**
	 * @brief The AudioManager is responsible for managing audio playback and settings.
	 */
	class AudioManager
	{
#pragma region Type

	private:
		struct Impl;

#pragma endregion

#pragma region Constructor

	public:
		AudioManager(AudioManagerInfo const &info);

		AudioManager(AudioManager const &) = delete;
		AudioManager(AudioManager &&) = delete;

		~AudioManager();

#pragma endregion

#pragma region Operator

	public:
		AudioManager &operator=(AudioManager const &) = delete;
		AudioManager &operator=(AudioManager &&) = delete;

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Checks if the audio with the given handle is valid.
		 */
		Bool is_valid(AudioHandle const handle) const;

		/**
		 * @brief Checks if the audio source with the given handle is valid.
		 */
		Bool is_valid(AudioSourceHandle const handle) const;

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Creates an audio clip from the given resource handle and returns its handle.
		 * @param resourceHandle The handle of the clip resource to create the audio clip from.
		 */
		ClipHandle create(ClipResourceHandle const resourceHandle);

		/**
		 * @brief Creates an audio clip from the given clip info and returns its handle.
		 * @param clipInfo The clip info to create the audio clip from.
		 */
		ClipHandle create(ClipInfo const &clipInfo);

		/**
		 * @brief Destroys the audio clip with the given handle.
		 * @param handle The handle of the audio clip to destroy.
		 */
		void destroy(ClipHandle const handle);

		/**
		 * @brief Creates a new audio source with the given info and returns its handle.
		 * @param info The audio source data to set.
		 * @return The handle of the created audio source.
		 */
		AudioSourceHandle create_source(AudioSourceInfo const &info);

		/**
		 * @brief Updates the audio source with the given handle.
		 * @param handle The handle of the audio source to update.
		 * @param info The audio source data to set.
		 */
		void update_source(AudioSourceHandle const handle, AudioSourceInfo const &info);

		/**
		 * @brief Destroys the audio source with the given handle.
		 * @param handle The handle of the audio source to destroy.
		 */
		void destroy_source(AudioSourceHandle const handle);

		/**
		 * @brief Updates the audio listener.
		 * @param info The audio listener data to set.
		 */
		void update_listener(AudioListenerInfo const &info);

		/**
		 * @brief Plays the given AudioClip in 2D space.
		 * @param clip The clip to play.
		 * @param volume The volume percentage to start at.
		 * @param pan The pan to start at. -1 is left, 1 is right.
		 * @param paused If true, the clip will pause immediately.
		 * @param bus The audio bus to play on.
		 * @return The handle to the clip that has begun to play.
		 */
		AudioHandle play(ClipHandle const clip, Float const volume = -1.0f, Float const pan = 0.0f, Bool const paused = false, UInt const bus = 0);

		/**
		 * @brief Plays the given AudioClip in 3D space.
		 * @param clip The clip to play.
		 * @param source The audio source data to set.
		 * @param volume The volume percentage to start at.
		 * @param paused If true, the clip will pause immediately.
		 * @param bus The audio bus to play on.
		 * @return The handle to the clip that has begun to play.
		 */
		AudioHandle play_object(ClipHandle const clip, AudioSourceInfo const &source, Float const volume = -1.0f, Bool const paused = false, UInt const bus = 0);

		/**
		 * @brief Plays the given AudioClip in the background.
		 * @param clip The clip to play.
		 * @param volume The volume percentage to start at.
		 * @param paused If true, the clip will pause immediately.
		 * @param bus The audio bus to play on.
		 * @return The handle to the clip that has begun to play.
		 */
		AudioHandle play_background(ClipHandle const clip, Float const volume = -1.0f, Bool const paused = false, UInt const bus = 0);

		/**
		 * @brief Stops the audio with the given handle.
		 * @param handle The handle to the audio.
		 */
		void stop(AudioHandle const handle);

		/**
		 * @brief Stops all audio.
		 */
		void stop_all();

		/**
		 * @brief Pauses or unpauses the audio with the given handle.
		 * @param handle The handle to the audio.
		 * @param paused If true, the audio will pause. If false, it will unpause.
		 */
		void set_pause(AudioHandle const handle, Bool const paused);

		/**
		 * @brief Pauses or unpauses all audio.
		 * @param paused If true, the audio will pause. If false, it will unpause.
		 */
		void set_pause_all(Bool const paused);

		/**
		 * @brief Gets whether the audio with the given handle is paused.
		 * @param handle The handle to the audio.
		 * @return True if the audio is paused, false otherwise.
		 */
		Bool get_pause(AudioHandle const handle) const;

		/**
		 * @brief Gets the singleton instance of the AudioManager.
		 * @return The singleton.
		 */
		static AudioManager &get_instance();

#pragma endregion

#pragma region Variables

	private:
		Impl *mp_impl;

		static AudioManager *s_instance;

#pragma endregion
	};
}
