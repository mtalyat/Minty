#pragma once

#include "M_Main.h"

namespace minty
{
	/// <summary>
	/// A component for an entity that will be destroyed after x seconds.
	/// </summary>
	struct MINTY_API DestroyTimer
	{
		/// <summary>
		/// The amount of time remaining in seconds before the entity is destroyed.
		/// </summary>
		float timer;
	};
}