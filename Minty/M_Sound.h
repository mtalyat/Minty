#pragma once

#include "M_Audio.h"
#include <SDL_mixer.h>

namespace minty
{
	/// <summary>
	/// Holds data for a sound effect.
	/// </summary>
	class MINTY_API Sound
		: public Audio
	{
	private:
		Mix_Chunk* const mp_audio;

	public:
		Sound(Mix_Chunk* const sound)
			: mp_audio(sound)
		{}

		Mix_Chunk* getAudio() const { return mp_audio; }
	};
}