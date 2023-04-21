#include "pch.h"
#include "M_S_AudioSystem.h"
#include "M_Debug.h"

namespace minty
{
	AudioSystem::AudioSystem(entt::registry* const registry)
		: System(registry)
		, mp_musics(new std::unordered_map<std::string, Music*>())
		, mp_sounds(new std::unordered_map<std::string, Sound*>())
	{}

	AudioSystem::~AudioSystem()
	{
		// free all music and sounds
		for (auto& audio : *mp_musics)
		{
			Mix_FreeMusic(audio.second->audio());
		}

		for (auto& audio : *mp_sounds)
		{
			Mix_FreeChunk(audio.second->audio());
		}
	}

	void AudioSystem::update()
	{
	}

	void AudioSystem::emplace(std::string const& name, Music* const audio)
	{
		mp_musics->emplace(name, audio);
	}
	
	void AudioSystem::emplace(std::string const& name, Sound* const audio)
	{
		mp_sounds->emplace(name, audio);
	}

	void AudioSystem::setVolume(int const channel, unsigned char const volume)
	{
		Mix_Volume(channel, volume);
	}
	
	void AudioSystem::playSound(std::string const& name, int const channel, int const loops, bool const oride)
	{
		// get sound
		auto const& found = mp_sounds->find(name);

		if (found == mp_sounds->end())
		{
			// not found
			Debug::logError(38, "Sound not found: " + name);
			return;
		}

		if (!oride && Mix_Playing(channel))
		{
			// do not override existing music
			return;
		}

		Mix_Volume(found->second->volume(), channel);
		 Mix_PlayChannel(channel, found->second->audio(), loops);
	}

	void AudioSystem::stopSound(int const channel)
	{
		Mix_HaltChannel(channel);
	}
	
	void AudioSystem::playMusic(std::string const& name, int const loops, bool const oride)
	{
		// get music
		auto const& found = mp_musics->find(name);

		if (found == mp_musics->end())
		{
			// not found
			Debug::logError(37, "Music not found: " + name);
			return;
		}

		if (!oride && Mix_PlayingMusic())
		{
			// do not override existing music
			return;
		}

		Mix_VolumeMusic(found->second->volume());
		Mix_PlayMusic(found->second->audio(), loops);
	}

	void AudioSystem::stopMusic()
	{
		Mix_HaltMusic();
	}
}
