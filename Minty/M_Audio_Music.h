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
		// the music file
		Mix_Music* const mp_audio;

	public:
		/// <summary>
		/// Creates a new Music Audio clip.
		/// </summary>
		/// <param name="music"></param>
		Music(Mix_Music* const music)
			: mp_audio(music)
		{}

		/// <summary>
		/// Gets the audio.
		/// </summary>
		/// <returns>The audio clip.</returns>
		Mix_Music* audio() const { return mp_audio; }
	};
}