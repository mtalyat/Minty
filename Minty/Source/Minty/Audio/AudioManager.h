#pragma once
#include "Minty/Audio/AudioClip.h"
#include "Minty/Audio/AudioListener.h"
#include "Minty/Audio/AudioSource.h"
#include "Minty/Context/Manager.h"
#include "Minty/Data/Pointer.h"

namespace Minty
{
	/// <summary>
	/// The arguments used to create an AudioManager.
	/// </summary>
	struct AudioManagerBuilder
	{

	};

	/// <summary>
	/// Handles audio playback and management.
	/// </summary>
	class AudioManager
		: public Manager
	{
#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new AudioManager using the given AudioManagerBuilder.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		AudioManager(AudioManagerBuilder const& builder)
			: Manager()
		{
		}

		virtual ~AudioManager()
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Checks if the given handle is valid.
		/// </summary>
		/// <param name="handle">The Handle.</param>
		/// <returns>True if the Handle points to a valid audio clip.</returns>
		virtual Bool is_valid(Handle const handle) const = 0;

		/// <summary>
		/// Sets the audio listener data.
		/// </summary>
		/// <param name="listener">The listener data.</param>
		virtual void set_audio_listener(AudioListener const& listener) = 0;

		/// <summary>
		/// Sets the audio source data for the source with the given Handle.
		/// </summary>
		/// <param name="handle">The Handle for the desired audio source.</param>
		/// <param name="source">The source data.</param>
		virtual void set_audio_source(Handle const handle, AudioSource const& source) = 0;

		/// <summary>
		/// Sets the pause state of the audio with the given handle.
		/// </summary>
		/// <param name="handle">The handle to the audio.</param>
		/// <param name="paused">The pause state.</param>
		virtual void set_pause(Handle const handle, Bool const paused) = 0;

		/// <summary>
		/// Gets the pause state of the audio with the given handle.
		/// </summary>
		/// <param name="handle">The handle to the audio.</param>
		/// <returns>The pause state.</returns>
		virtual Bool get_pause(Handle const handle) const = 0;

		/// <summary>
		/// Sets the pause state of all audio.
		/// </summary>
		/// <param name="paused">The pause state.</param>
		virtual void set_pause_all(Bool const paused) = 0;

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Called when this AudioManager is destroyed.
		/// </summary>
		void dispose() override;

		/// <summary>
		/// Plays the given AudioClip in 2D space.
		/// </summary>
		/// <param name="clip">The clip to play.</param>
		/// <param name="volume">The volume percentage to start at.</param>
		/// <param name="pan">The pan to start at. -1 is left, 1 is right.</param>
		/// <param name="paused">If true, the clip will pause immediately.</param>
		/// <param name="bus">The audio bus to play on.</param>
		/// <returns>The handle to the clip that has begun to play.</returns>
		virtual Handle play(Ref<AudioClip> const& clip, Float const volume = -1.0f, Float const pan = 0.0f, Bool const paused = false, UInt const bus = 0) = 0;

		/// <summary>
		/// Plays the given AudioClip in 3D space.
		/// </summary>
		/// <param name="clip">The clip to play.</param>
		/// <param name="source">The audio source data to set.</param>
		/// <param name="volume">The volume percentage to start at.</param>
		/// <param name="paused">If true, the clip will pause immediately.</param>
		/// <param name="bus">The audio bus to play on.</param>
		/// <returns>The handle to the clip that has begun to play.</returns>
		virtual Handle play_object(Ref<AudioClip> const& clip, AudioSource const& source, Float const volume = -1.0f, Bool const paused = false, UInt const bus = 0) = 0;

		/// <summary>
		/// Plays the given AudioClip in the background.
		/// </summary>
		/// <param name="clip">The clip to play.</param>
		/// <param name="volume">The volume percentage to start at.</param>
		/// <param name="paused">If true, the clip will pause immediately.</param>
		/// <param name="bus">The audio bus to play on.</param>
		/// <returns>The handle to the clip that has begun to play.</returns>
		virtual Handle play_background(Ref<AudioClip> const& clip, Float const volume = -1.0f, Bool const paused = false, UInt const bus = 0) = 0;

		/// <summary>
		/// Stops the audio with the given handle.
		/// </summary>
		/// <param name="handle">The handle to the audio.</param>
		virtual void stop(Handle const handle) = 0;

		/// <summary>
		/// Stops all audio.
		/// </summary>
		virtual void stop_all() = 0;

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Gets the singleton instance of the AudioManager.
		/// </summary>
		/// <returns>The singleton.</returns>
		static AudioManager& get_singleton();

		/// <summary>
		/// Creates a new AudioManager using the given AudioManagerBuilder.
		/// </summary>
		/// <param name="builder">The arguments.</param>
		static Owner<AudioManager> create(AudioManagerBuilder const& builder = {});

#pragma endregion
	};
}