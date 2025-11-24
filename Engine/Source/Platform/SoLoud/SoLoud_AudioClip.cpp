#include "pch.h"
#include "SoLoud_AudioClip.h"
#include "Minty/Core/Format.h"

using namespace Minty;

Minty::SoLoud_AudioClip::SoLoud_AudioClip(AudioClipInfo const& info)
	: AudioClip(info)
	, mp_clip(new SoLoud::Wav())
{
	// load clip
	SoLoud::result result = mp_clip->loadMem(static_cast<unsigned char const*>(info.data.get_data()), static_cast<unsigned int>(info.data.get_size()), true, false);

	MINTY_ASSERT(result == SoLoud::SO_NO_ERROR, F("Failed to load audio clip: {}. Error: {}", info.id, result));

	// set data
	mp_clip->setVolume(info.volume);
	mp_clip->setLooping(info.loop);
	mp_clip->setLoopPoint(info.loopPoint);
	mp_clip->setSingleInstance(info.exclusive);
}

Minty::SoLoud_AudioClip::~SoLoud_AudioClip()
{
	delete mp_clip;
}
