#include "pch.h"
#include "AudioManager.h"
#include "Minty/Application/Application.h"
#ifdef MINTY_SOLOUD
#include "Platform/SoLoud/SoLoud_AudioManager.h"
#endif // MINTY_SOLOUD

using namespace Minty;

AudioManager& Minty::AudioManager::get_singleton()
{
	return Application::get_singleton().get_audio_manager();
}

Unique<AudioManager> Minty::AudioManager::create(AudioManagerInfo const& info)
{
#ifdef MINTY_SOLOUD
	return Unique<SoLoud_AudioManager>::create(info);
#else
	MINTY_NOT_IMPLEMENTED();
	return Unique<AudioManager>();
#endif // MINTY_SOLOUD
}
