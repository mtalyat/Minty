#pragma once

/**
 * @file AnimatorComponent.hpp
 * @brief Header file defining the AnimatorComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Animation/Animator.h"
#include "Minty/Animation/Animation.h"

namespace Minty
{
	/**
	 * @brief Handles animating an Entity.
	 */
	struct AnimatorComponent
	{
		/**
		 * @brief The Animator to use for this Component.
		 */
		Ref<Animator> animator = nullptr;

		/**
		 * @brief The current Animation being played.
		 */
		Ref<Animation> animation = nullptr;

		/**
		 * @brief The current time in the Animation.
		 */
		Float time = 0.0f;
	};

	template <>
	struct Serializer<AnimatorComponent>
	{
		static Bool serialize(Writer &writer, AnimatorComponent const &value);
		static Bool deserialize(Reader &reader, AnimatorComponent &value);
	};
}
