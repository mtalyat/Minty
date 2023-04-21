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
		/// <summary>
		/// Creates a new Sound Audio clip.
		/// </summary>
		/// <param name="sound"></param>
		Sound(Mix_Chunk* const sound)
			: mp_audio(sound)
		{}

		/// <summary>
		/// Gets the audio.
		/// </summary>
		/// <returns>The audio clip.</returns>
		Mix_Chunk* audio() const { return mp_audio; }
	};
}