#pragma once

#include "M_Audio.h"
#include <SDL_mixer.h>

namespace minty
{
	/// <summary>
	/// Holds data for a song/music.
	/// </summary>
	class MINTY_API Music
		: public Audio
	{
	private:
		Mix_Music* const mp_audio;

	public:
		Music(Mix_Music* const music)
			: mp_audio(music)
		{}

		Mix_Music* getAudio() const { return mp_audio; }
	};
}