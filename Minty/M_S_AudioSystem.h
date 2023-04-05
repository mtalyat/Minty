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
		AudioSystem(entt::registry* const registry);

		~AudioSystem();

		void update() override;

		void emplace(std::string const& name, Music* const audio);

		void emplace(std::string const& name, Sound* const audio);

		void setVolume(int const channel, unsigned char const volume);

		void playSound(std::string const& name, int const channel = 0, int const loops = LOOP_ONCE, bool const oride = true);

		void playMusic(std::string const& name, int const loops = LOOP_FOREVER, bool const oride = true);
	};
}