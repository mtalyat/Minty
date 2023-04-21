#pragma once

#include "M_System.h"
#include "M_Music.h"
#include "M_Sound.h"
#include <unordered_map>
#include <climits>

#define LOOP_ONCE 0
#define LOOP_FOREVER INT_MAX

namespace minty
{
	/// <summary>
	/// Handles all audio within the Scene.
	/// </summary>
	class MINTY_API AudioSystem
		: public System
	{
	private:
		std::unordered_map<std::string, Music*>* mp_musics;
		std::unordered_map<std::string, Sound*>* mp_sounds;

	public:
		/// <summary>
		/// Creates a new AudioSystem.
		/// </summary>
		/// <param name="registry">The entity registry belonging to this System.</param>
		AudioSystem(entt::registry* const registry);

		~AudioSystem();

		void update() override;

		/// <summary>
		/// Adds a new Music Audio that can be played.
		/// </summary>
		/// <param name="name">The name of the Music.</param>
		/// <param name="audio">The Audio clip to be added.</param>
		void emplace(std::string const& name, Music* const audio);

		/// <summary>
		/// Adds a new Sound Audio that can be played.
		/// </summary>
		/// <param name="name">The name of the Sound.</param>
		/// <param name="audio">The Audio clip to be added.</param>
		void emplace(std::string const& name, Sound* const audio);

		/// <summary>
		/// Sets the volume for this given channel to the given volume.
		/// </summary>
		/// <param name="channel">The channel to set.</param>
		/// <param name="volume">The new volume for the channel.</param>
		void setVolume(int const channel, unsigned char const volume);

		/// <summary>
		/// Plays the given Sound.
		/// </summary>
		/// <param name="name">The name of the Sound to play.</param>
		/// <param name="channel">The channel to play the Sound on, or -1 to find the first empty channel.</param>
		/// <param name="loops">Does this Sound loop?</param>
		/// <param name="oride">Should this Sound override an already playing Sound on the given channel?</param>
		void playSound(std::string const& name, int const channel = -1, int const loops = LOOP_ONCE, bool const oride = true);

		/// <summary>
		/// Stops the sound on the given channel.
		/// </summary>
		/// <param name="channel">The channel to stop the sound on, or -1 for all channels.</param>
		void stopSound(int const channel = -1);

		/// <summary>
		/// Plays the given Music.
		/// </summary>
		/// <param name="name">The name of the Music to play.</param>
		/// <param name="loops">Does this Music loop?</param>
		/// <param name="oride">Should this Music override an already playing Music on the Music channel?</param>
		void playMusic(std::string const& name, int const loops = LOOP_FOREVER, bool const oride = true);

		/// <summary>
		/// Stops the currently playing Music.
		/// </summary>
		void stopMusic();
	};
}