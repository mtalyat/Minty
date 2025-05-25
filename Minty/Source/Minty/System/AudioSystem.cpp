#include "pch.h"
#include "AudioSystem.h"
#include "Minty/Audio/AudioManager.h"
#include "Minty/Component/AudioListenerComponent.h"
#include "Minty/Component/AudioSourceComponent.h"
#include "Minty/Component/EnabledComponent.h"
#include "Minty/Component/TransformComponent.h"
#include "Minty/Entity/EntityManager.h"
#include "Minty/Scene/Scene.h"

using namespace Minty;

Minty::AudioSystem::AudioSystem(SystemBuilder const& builder)
	: System(builder)
{
}

void Minty::AudioSystem::on_unload()
{
	// stop all audio when system unloads
	AudioManager& audioManager = AudioManager::get_singleton();
	audioManager.stop_all();

	System::on_unload();
}

void Minty::AudioSystem::on_finalize()
{
	// get the managers
	AudioManager& audioManager = AudioManager::get_singleton();
	EntityManager& entityManager = m_scene->get_entity_manager();

	// get the audio listener
	Size count = 0;
	for (auto const& [entity, audioListenerComp] : entityManager.view<AudioListenerComponent>().each())
	{
		// ignore if not the first
		if (count > 0)
		{
			MINTY_ABORT("More than one AudioListenerComponent in the Scene.");
			continue;
		}

		// get the listener data
		AudioListener listenerData;
		TransformComponent* transformComp = entityManager.try_get_component<TransformComponent>(entity);
		if (transformComp)
		{
			// get data for the listener
			listenerData.set_position(transformComp->transform.get_global_position());
			Quaternion rotation = transformComp->transform.get_global_rotation();
			listenerData.set_forward(Math::forward(rotation));
			listenerData.set_up(Math::up(rotation));
		}
		else
		{
			// no transform data, set to defaults
			listenerData.set_position(Math::ZERO);
			listenerData.set_forward(Math::FORWARD);
			listenerData.set_up(Math::UP);
		}
		
		// set the listener data
		audioManager.set_audio_listener(listenerData);

		count++;
	}

	// if no audio listener was found, warn
	if (count == 0)
	{
		MINTY_WARNING("No Audio Listener found in the Scene.");
	}

	// if any entities were disabled, stop their audio
	for (auto const& [entity, audioSourceComp] : entityManager.view<AudioSourceComponent>(entt::exclude_t<EnabledComponent>()).each())
	{
		// ignore if already not playing
		if (audioSourceComp.handle == INVALID_HANDLE)
		{
			continue;
		}

		// stop the audio
		audioManager.stop(audioSourceComp.handle);
		audioSourceComp.handle = INVALID_HANDLE;
	}

	// track progress of audio sources and update them
	for (auto const& [entity, audioSourceComp, enabledComp] : entityManager.view<AudioSourceComponent, EnabledComponent const>().each())
	{
		// start playing if supposed to
		if (audioSourceComp.play)
		{
			audioSourceComp.play = false;

			// if no clip or already playing, ignore
			if (audioSourceComp.audioClip == nullptr || audioSourceComp.handle != INVALID_HANDLE)
			{
				continue;
			}

			// get the audio source data
			Float3 position;
			TransformComponent* transformComp = entityManager.try_get_component<TransformComponent>(entity);
			if (transformComp)
			{
				// get data for the source
				position = transformComp->transform.get_global_position();
			}
			else
			{
				// no transform data, set to defaults
				position = Math::ZERO;
			}

			AudioSource sourceData(
				position,
				Math::ZERO,
				audioSourceComp.attenuation,
				audioSourceComp.attenuationRollOff,
				audioSourceComp.minDistance,
				audioSourceComp.maxDistance
			);

			// play the audio
			audioSourceComp.handle = audioManager.play_object(
				audioSourceComp.audioClip,
				sourceData,
				audioSourceComp.volume
			);

			// done
			continue;
		}

		// ignore if not playing
		if (audioSourceComp.handle == INVALID_HANDLE)
		{
			continue;
		}

		// check if still playing
		if (!audioManager.is_valid(audioSourceComp.handle))
		{
			// done playing
			audioSourceComp.handle = INVALID_HANDLE;
			continue;
		}

		// get the audio source data
		AudioSource sourceData;
		TransformComponent* transformComp = entityManager.try_get_component<TransformComponent>(entity);
		if (transformComp)
		{
			// get data for the source
			sourceData.set_position(transformComp->transform.get_global_position());
			sourceData.set_velocity(Math::ZERO);
		}
		else
		{
			// no transform data, set to defaults
			sourceData.set_position(Math::ZERO);
			sourceData.set_velocity(Math::ZERO);
		}
		sourceData.set_attenuation(audioSourceComp.attenuation);
		sourceData.set_attenuation_rolloff(audioSourceComp.attenuationRollOff);
		sourceData.set_min_distance(audioSourceComp.minDistance);
		sourceData.set_max_distance(audioSourceComp.maxDistance);

		// set the audio source data
		audioManager.set_audio_source(audioSourceComp.handle, sourceData);
	}
}
