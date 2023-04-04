#include "pch.h"
#include "M_Audio.h"
#include <SDL_mixer.h>

namespace minty
{
	Audio::Audio()
		: m_volume(MIX_MAX_VOLUME)
	{}
}
