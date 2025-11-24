#include "pch.h"
#include "AudioManager.h"
#include "Minty/Context/Context.h"
#ifdef MINTY_SOLOUD
#include "Platform/SoLoud/SoLoud_AudioManager.h"
#endif // MINTY_SOLOUD

using namespace Minty;

AudioManager& Minty::AudioManager::get_singleton()
{
	return Context::get_singleton().get_audio_manager();
}

Owner<AudioManager> Minty::AudioManager::create(AudioManagerInfo const& info)
{
#ifdef MINTY_SOLOUD
	return Owner<SoLoud_AudioManager>(info);
#else
	return Owner<AudioManager>();
#endif // MINTY_SOLOUD
}

void Minty::AudioManager::dispose()
{
	stop_all();

	Manager::dispose();
}
