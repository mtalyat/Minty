#include "pch.h"
#include "AudioManager.h"

using namespace Minty;

#ifdef MINTY_SOLOUD
#include "Independence/SoLoud/SoLoud_AudioManager.h"
struct AudioManager::Impl
{
    SoLoud_AudioManager renderManager;
};
#else
#error "No audio manager implementation defined for the current platform."
#endif // MINTY_SOLOUD

AudioManager* AudioManager::s_instance = nullptr;

Minty::AudioManager::AudioManager(AudioManagerInfo const &info)
	: mp_impl()
{
	mp_impl = new Impl(info);
}

Minty::AudioManager::~AudioManager()
{
    delete mp_impl;
}

Bool Minty::AudioManager::is_valid(AudioHandle const handle) const
{
    return mp_impl->renderManager.is_valid(handle);
}

Bool Minty::AudioManager::is_valid(AudioSourceHandle const handle) const
{
    return mp_impl->renderManager.is_valid(handle);
}

ClipHandle Minty::AudioManager::create(ClipResourceHandle const resourceHandle)
{
    return mp_impl->renderManager.create(resourceHandle);
}

ClipHandle Minty::AudioManager::create(ClipInfo const &clipInfo)
{
    return mp_impl->renderManager.create(clipInfo);
}

void Minty::AudioManager::destroy(ClipHandle const handle)
{
    mp_impl->renderManager.destroy(handle);
}

AudioSourceHandle Minty::AudioManager::create_source(AudioSourceInfo const &info)
{
	return mp_impl->renderManager.create_source(info);
}

void Minty::AudioManager::update_source(AudioSourceHandle const handle, AudioSourceInfo const &info)
{
	mp_impl->renderManager.update_source(handle, info);
}

void Minty::AudioManager::destroy_source(AudioSourceHandle const handle)
{
	mp_impl->renderManager.destroy_source(handle);
}

void Minty::AudioManager::update_listener(AudioListenerInfo const &info)
{
	mp_impl->renderManager.update_listener(info);
}

AudioHandle Minty::AudioManager::play(ClipHandle const clip, Float const volume, Float const pan, Bool const paused, UInt const bus)
{
    return mp_impl->renderManager.play(clip, volume, pan, paused, bus);
}

AudioHandle Minty::AudioManager::play_object(ClipHandle const clip, AudioSourceInfo const &source, Float const volume, Bool const paused, UInt const bus)
{
    return mp_impl->renderManager.play_object(clip, source, volume, paused, bus);
}

AudioHandle Minty::AudioManager::play_background(ClipHandle const clip, Float const volume, Bool const paused, UInt const bus)
{
    return mp_impl->renderManager.play_background(clip, volume, paused, bus);
}

void Minty::AudioManager::stop(AudioHandle const handle)
{
    mp_impl->renderManager.stop(handle);
}

void Minty::AudioManager::stop_all()
{
    mp_impl->renderManager.stop_all();
}

void Minty::AudioManager::set_pause(AudioHandle const handle, Bool const paused)
{
    mp_impl->renderManager.set_pause(handle, paused);
}

void Minty::AudioManager::set_pause_all(Bool const paused)
{
    mp_impl->renderManager.set_pause_all(paused);
}

Bool Minty::AudioManager::get_pause(AudioHandle const handle) const
{
    return mp_impl->renderManager.get_pause(handle);
}

AudioManager &Minty::AudioManager::get_instance()
{
	MINTY_ASSERT(s_instance, ErrorCodeEnum::Singleton_DoesNotExist);
	return *s_instance;
}