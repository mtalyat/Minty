#include "pch.h"
#include "AudioClip.h"
#ifdef MINTY_SOLOUD
#include "Platform/SoLoud/SoLoud_AudioClip.h"
#endif // MINTY_SOLOUD

using namespace Minty;

Owner<AudioClip> Minty::AudioClip::create(AudioClipInfo const& info)
{
#ifdef MINTY_SOLOUD
	return Owner<SoLoud_AudioClip>(info);
#else
	return Owner<AudioClip>();
#endif // MINTY_SOLOUD
}
