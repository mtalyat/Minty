#pragma once
#include "Minty/Core/Math.h"

namespace Minty
{
	/// <summary>
	/// Holds the data for an audio listener.
	/// </summary>
	struct AudioListener
	{
		Float3 position = Float3(0.0f, 0.0f, 0.0f);
		Float3 forward = Float3(0.0f, 0.0f, 1.0f);
		Float3 up = Float3(0.0f, 1.0f, 0.0f);
		Float3 velocity = Float3(0.0f, 0.0f, 0.0f);
	};
}