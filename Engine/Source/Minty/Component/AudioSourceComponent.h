#pragma once
#include "Minty/Component/Component.h"
#include "Minty/Audio/AudioClip.h"
#include "Minty/Audio/AudioSource.h"

namespace Minty
{
	/// <summary>
	/// A Component that holds the data for playing audio.
	/// </summary>
	struct AudioSourceComponent
		: public Component
	{
		/// <summary>
		/// The AudioClip to play.
		/// </summary>
		Ref<AudioClip> audioClip = nullptr;

		/// <summary>
		/// When set to true, the audio will begin to play as soon as the Entity is able.
		/// </summary>
		Bool play = false;

		/// <summary>
		/// The handle to the sound being played, if any.
		/// </summary>
		Handle handle = INVALID_HANDLE;

		/// <summary>
		/// The volume to play the audio at.
		/// </summary>
		Float volume = DEFAULT_AUDIO_VOLUME;

		/// <summary>
		/// The attenuation model to use for the audio.
		/// </summary>
		Attenuation attenuation = Attenuation::Default;

		/// <summary>
		/// The attenuation rolloff value.
		/// </summary>
		Float attenuationRollOff = DEFAULT_AUDIO_ATTENUATION_ROLL_OFF;

		/// <summary>
		/// The near distance for the audio source.
		/// </summary>
		Float minDistance = DEFAULT_AUDIO_MIN_DISTANCE;

		/// <summary>
		/// The far distance for the audio source.
		/// </summary>
		Float maxDistance = DEFAULT_AUDIO_MAX_DISTANCE;

		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;
	};
}