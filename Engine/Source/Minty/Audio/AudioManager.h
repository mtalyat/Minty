#ifndef MINTY_AUDIO_AUDIOMANAGER_H
#define MINTY_AUDIO_AUDIOMANAGER_H

/**
 * @file AudioManager.h
 * @brief Header file defining the AudioManager class.
 * @author Mitchell Talyat
 */

#include "Minty/Manager/Manager.h"
#include "Minty/Data/Pointer.h"

namespace Minty
{
	class AudioSource;
	class AudioListener;
	class AudioClip;
	struct AudioManagerInfo;

	/**
	 * @brief The AudioManager is responsible for managing audio playback and settings.
	 */
	class AudioManager
		: public Manager
	{
#pragma region Constructors

	public:
		AudioManager(AudioManagerInfo const& info)
			: Manager() {}

		virtual ~AudioManager() = default;

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Checks if the given handle is valid.
		 * @param handle The handle to check.
		 */
		virtual Bool is_valid(Handle const handle) const = 0;

		/**
		 * @brief Sets the audio listener data.
		 * @param listener The listener data.
		 */
		virtual void set_audio_listener(AudioListener const& listener) = 0;

		/**
		 * @brief Sets the audio source data for the source with the given Handle.
		 * @param handle The Handle for the desired audio source.
		 * @param source The source data.
		 */
		virtual void set_audio_source(Handle const handle, AudioSource const& source) = 0;

		/**
		 * @brief Sets the pause state of the audio with the given handle.
		 * @param handle The handle to the audio.
		 * @param paused The pause state.
		 */
		virtual void set_pause(Handle const handle, Bool const paused) = 0;

		/**
		 * @brief Gets the pause state of the audio with the given handle.
		 * @param handle The handle to the audio.
		 * @return The pause state.
		 */
		virtual Bool get_pause(Handle const handle) const = 0;

		/**
		 * @brief Sets the pause state of all audio.
		 * @param paused The pause state.
		 */
		virtual void set_pause_all(Bool const paused) = 0;

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Plays the given AudioClip in 2D space.
		 * @param clip The clip to play.
		 * @param volume The volume percentage to start at.
		 * @param pan The pan to start at. -1 is left, 1 is right.
		 * @param paused If true, the clip will pause immediately.
		 * @param bus The audio bus to play on.
		 * @return The handle to the clip that has begun to play.
		 */
		virtual Handle play(Ref<AudioClip> const& clip, Float const volume = -1.0f, Float const pan = 0.0f, Bool const paused = false, UInt const bus = 0) = 0;

		/**
		 * @brief Plays the given AudioClip in 3D space.
		 * @param clip The clip to play.
		 * @param source The audio source data to set.
		 * @param volume The volume percentage to start at.
		 * @param paused If true, the clip will pause immediately.
		 * @param bus The audio bus to play on.
		 * @return The handle to the clip that has begun to play.
		 */
		virtual Handle play_object(Ref<AudioClip> const& clip, AudioSource const& source, Float const volume = -1.0f, Bool const paused = false, UInt const bus = 0) = 0;

		/**
		 * @brief Plays the given AudioClip in the background.
		 * @param clip The clip to play.
		 * @param volume The volume percentage to start at.
		 * @param paused If true, the clip will pause immediately.
		 * @param bus The audio bus to play on.
		 * @return The handle to the clip that has begun to play.
		 */
		virtual Handle play_background(Ref<AudioClip> const& clip, Float const volume = -1.0f, Bool const paused = false, UInt const bus = 0) = 0;

		/**
		 * @brief Stops the audio with the given handle.
		 * @param handle The handle to the audio.
		 */
		virtual void stop(Handle const handle) = 0;

		/**
		 * @brief Stops all audio.
		 */
		virtual void stop_all() = 0;
		
		/**
		 * @brief Gets the singleton instance of the AudioManager.
		 * @return The singleton.
		 */
		static Unique<AudioManager> const& get_instance();

		/**
		 * @brief Gets the singleton instance of the AudioManager.
		 * @return A reference to the AudioManager.
		 */
		static AudioManager& get_singleton();

		/**
		 * @brief Creates a new AudioManager using the given AudioManagerInfo.
		 * @param info The arguments.
		 */
		static Unique<AudioManager> create(AudioManagerInfo const& info);

		/**
		 * @brief Creates a new AudioManager with default settings.
		 */
		static Unique<AudioManager> create();

#pragma endregion
	};
}

#endif // MINTY_AUDIO_AUDIOMANAGER_H