#include "pch.h"
#include "SoLoud_AudioManager.h"

using namespace Minty;

void Minty::SoLoud_AudioManager::initialize()
{
	m_engine->init(SoLoud::Soloud::CLIP_ROUNDOFF | SoLoud::Soloud::LEFT_HANDED_3D);
	m_dirty = true;
}

void Minty::SoLoud_AudioManager::dispose()
{
	m_engine->deinit();
}

void Minty::SoLoud_AudioManager::finalize()
{
	// if something changed, apply those changes
	if (m_dirty)
	{
		m_engine->update3dAudio();
		m_dirty = false;
	}
}

Bool Minty::SoLoud_AudioManager::is_valid(Handle const handle) const
{
	return m_engine->isValidVoiceHandle(handle);
}

void Minty::SoLoud_AudioManager::set_audio_listener(AudioListener const& listener)
{
	m_engine->set3dListenerParameters(
		listener.position.x,
		listener.position.y,
		listener.position.z,
		listener.forward.x,
		listener.forward.y,
		listener.forward.z,
		listener.up.x,
		listener.up.y,
		listener.up.z,
		listener.velocity.x,
		listener.velocity.y,
		listener.velocity.z
	);
	m_dirty = true;
}

void Minty::SoLoud_AudioManager::set_audio_source(Handle const handle, AudioSource const& source)
{
	m_engine->set3dSourceParameters(
		handle,
		source.position.x,
		source.position.y,
		source.position.z,
		source.velocity.x,
		source.velocity.y,
		source.velocity.z
	);
	m_engine->set3dSourceAttenuation(
		handle,
		static_cast<unsigned int>(source.attenuation),
		source.attenuationRolloff
	);
	m_engine->set3dSourceMinMaxDistance(
		handle,
		source.minDistance,
		source.maxDistance
	);
	m_dirty = true;
}

void Minty::SoLoud_AudioManager::set_pause(Handle const handle, Bool const paused)
{
	m_engine->setPause(handle, paused);
}

Bool Minty::SoLoud_AudioManager::get_pause(Handle const handle) const
{
	return m_engine->getPause(handle);
}

void Minty::SoLoud_AudioManager::set_pause_all(Bool const paused)
{
	m_engine->setPauseAll(paused);
}

Handle Minty::SoLoud_AudioManager::play(Ref<AudioClip> const& clip, Float const volume, Float const pan, Bool const paused, UInt const bus)
{
	SoLoud::Wav* wav = static_cast<SoLoud::Wav*>(clip->get_native());
	return m_engine->play(
		*wav,
		volume,
		pan,
		paused,
		bus
	);
}

Handle Minty::SoLoud_AudioManager::play_object(Ref<AudioClip> const& clip, AudioSource const& source, Float const volume, Bool const paused, UInt const bus)
{
	SoLoud::Wav* wav = static_cast<SoLoud::Wav*>(clip->get_native());
	Handle handle = m_engine->play3d(
		*wav,
		source.position.x,
		source.position.y,
		source.position.z,
		source.velocity.x,
		source.velocity.y,
		source.velocity.z,
		volume,
		paused,
		bus
	);
	m_engine->set3dSourceAttenuation(
		handle,
		static_cast<unsigned int>(source.attenuation),
		source.attenuationRolloff
	);
	m_engine->set3dSourceMinMaxDistance(
		handle,
		source.minDistance,
		source.maxDistance
	);
	m_dirty = true;
	return handle;
}

Handle Minty::SoLoud_AudioManager::play_background(Ref<AudioClip> const& clip, Float const volume, Bool const paused, UInt const bus)
{
	SoLoud::Wav* wav = static_cast<SoLoud::Wav*>(clip->get_native());
	return m_engine->playBackground(
		*wav,
		volume,
		paused,
		bus
	);
}

void Minty::SoLoud_AudioManager::stop(Handle const handle)
{
	m_engine->stop(handle);
}

void Minty::SoLoud_AudioManager::stop_all()
{
	m_engine->stopAll();
}
