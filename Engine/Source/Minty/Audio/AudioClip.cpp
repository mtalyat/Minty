#include "pch.h"
#include "AudioClip.h"
#include "Minty/Audio/AudioClipInfo.h"
#ifdef MINTY_SOLOUD
#include "Platform/SoLoud/SoLoud_AudioClip.h"
#endif // MINTY_SOLOUD

using namespace Minty;

Minty::AudioClip::AudioClip(AudioClipInfo const &info)
	: Asset(info.id)
{
}

Shared<AudioClip> Minty::AudioClip::create(AudioClipInfo const &info)
{
#ifdef MINTY_SOLOUD
	return Shared<SoLoud_AudioClip>::create(info);
#else
	return Shared<AudioClip>();
#endif // MINTY_SOLOUD
}
