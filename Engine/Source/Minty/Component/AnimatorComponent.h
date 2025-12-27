#ifndef MINTY_COMPONENT_ANIMATORCOMPONENT_H
#define MINTY_COMPONENT_ANIMATORCOMPONENT_H

/**
 * @file AnimatorComponent.h
 * @brief Header file defining the AnimatorComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"
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
		: public Component
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

	template<>
	struct Serializer<AnimatorComponent>
	{
		static void serialize(Writer& writer, AnimatorComponent const& value);
		static void deserialize(Reader& reader, AnimatorComponent& value);
	};
}

#endif // MINTY_COMPONENT_ANIMATORCOMPONENT_H