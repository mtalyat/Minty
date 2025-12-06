#include "pch.h"
#include "AudioManager.h"
#include "Minty/Application/Application.h"
#include "Minty/Audio/AudioManagerInfo.h"
#ifdef MINTY_SOLOUD
#include "Platform/SoLoud/SoLoud_AudioManager.h"
#endif // MINTY_SOLOUD

using namespace Minty;

Unique<AudioManager> const& Minty::AudioManager::get_instance()
{
	return Application::get_singleton().get_audio_manager();
}

AudioManager& Minty::AudioManager::get_singleton()
{
	Unique<AudioManager> const& instance = Application::get_singleton().get_audio_manager();
	MINTY_ASSERT(instance, ErrorCode::Application_AudioManagerNotInitialized);
	return *instance;
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

Unique<AudioManager> Minty::AudioManager::create()
{
	AudioManagerInfo info{};
	return create(info);
}
