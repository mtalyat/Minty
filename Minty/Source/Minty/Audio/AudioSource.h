#pragma once
#include "Minty/Audio/Attenuation.h"
#include "Minty/Core/Constant.h"
#include "Minty/Core/Math.h"

namespace Minty
{
	/// <summary>
	/// Holds the data for an audio source.
	/// </summary>
	struct AudioSource
	{
		Float3 position = Float3(0.0f, 0.0f, 0.0f);
		Float3 velocity = Float3(0.0f, 0.0f, 0.0f);
		Attenuation attenuation = Attenuation::LinearDistance;
		Float attenuationRolloff = DEFAULT_AUDIO_ATTENUATION_ROLL_OFF;
		Float minDistance = DEFAULT_AUDIO_MIN_DISTANCE;
		Float maxDistance = DEFAULT_AUDIO_MAX_DISTANCE;
	};
}