#pragma once

/**
 * @file AudioSourceComponent.hpp
 * @brief Header file defining the AudioSourceComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Audio/Attenuation.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Audio/AudioClip.h"

namespace Minty
{
	/**
	 * @brief A Component that holds the data for playing audio.
	 */
	struct AudioSourceComponent	
	{
		/**
		 * @brief The AudioClip to play.
		 */
		Ref<AudioClip> audioClip = nullptr;

		/**
		 * @brief When set to true, the audio will begin to play as soon as the Entity is able.
		 */
		Bool play = false;

		/**
		 * @brief The handle to the sound being played, if any.
		 */
		Handle handle = INVALID_HANDLE;

		/**
		 * @brief The volume to play the audio at.
		 */
		Float volume = DEFAULT_AUDIO_VOLUME;

		/**
		 * @brief The attenuation model to use for the audio.
		 */
		Attenuation attenuation = Attenuation::Default;

		/**
		 * @brief The attenuation rolloff value.
		 */
		Float attenuationRollOff = DEFAULT_AUDIO_ATTENUATION_ROLL_OFF;

		/**
		 * @brief The near distance for the audio source.
		 */
		Float minDistance = DEFAULT_AUDIO_MIN_DISTANCE;

		/**
		 * @brief The far distance for the audio source.
		 */
		Float maxDistance = DEFAULT_AUDIO_MAX_DISTANCE;
	};

	template<>
	struct Serializer<AudioSourceComponent>
	{
		static Bool serialize(Writer& writer, AudioSourceComponent const& value);
		static Bool deserialize(Reader& reader, AudioSourceComponent& value);
	};
}
