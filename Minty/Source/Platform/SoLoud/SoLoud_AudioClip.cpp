#include "pch.h"
#include "SoLoud_AudioClip.h"

using namespace Minty;

Minty::SoLoud_AudioClip::SoLoud_AudioClip(AudioClipBuilder const& builder)
	: AudioClip(builder)
	, mp_clip(new SoLoud::Wav())
{
	// load clip
	SoLoud::result result = mp_clip->loadMem(static_cast<unsigned char const*>(builder.data.get_data()), static_cast<unsigned int>(builder.data.get_size()), true, false);

	MINTY_ASSERT(result == SoLoud::SO_NO_ERROR, F("Failed to load audio clip: {}. Error: {}", builder.id, result));

	// set data
	mp_clip->setVolume(builder.volume);
	mp_clip->setLooping(builder.loop);
	mp_clip->setLoopPoint(builder.loopPoint);
	mp_clip->setSingleInstance(builder.exclusive);
}

Minty::SoLoud_AudioClip::~SoLoud_AudioClip()
{
	delete mp_clip;
}
