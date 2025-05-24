#pragma once
#include "Minty/Core/Macro.h"

namespace Minty
{
	/// <summary>
	/// Determines what additional actions are taken during an animation step.
	/// </summary>
	enum class AnimationStepFlags
	{
		/// <summary>
		/// No additional action taken.
		/// </summary>
		None = 0b0000,

		/// <summary>
		/// Add the associated component to the entity.
		/// </summary>
		Add = 0b0001,

		/// <summary>
		/// Remove the associated component from the entity.
		/// </summary>
		Remove = 0b0010,

		/// <summary>
		/// All additional steps are taken.
		/// </summary>
		All = 0b1111,
	};

	MINTY_ENUM_FLAGS_OPERATORS(AnimationStepFlags)
}