#include "pch.h"
#include "AudioClip.h"
#ifdef MINTY_SOLOUD
#include "Platform/SoLoud/SoLoud_AudioClip.h"
#endif // MINTY_SOLOUD

using namespace Minty;

Owner<AudioClip> Minty::AudioClip::create(AudioClipBuilder const& builder)
{
#ifdef MINTY_SOLOUD
	return Owner<SoLoud_AudioClip>(builder);
#else
	return Owner<AudioClip>();
#endif // MINTY_SOLOUD
}
