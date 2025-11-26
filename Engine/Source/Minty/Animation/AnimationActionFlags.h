#ifndef MINTY_ANIMATION_ANIMATIONACTIONFLAGS_H
#define MINTY_ANIMATION_ANIMATIONACTIONFLAGS_H

/**
 * @file AnimationActionFlags.h
 * @brief Defines flags for actions to be taken during animation.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Enum.h"
#include "Minty/Core/Macro.h"
#include "Minty/Serialization/Parse.h"
#include "Minty/Serialization/ToString.h"

namespace Minty
{
	/**
	 * @brief Flags for actions to be taken during animation.
	 */
	enum class AnimationActionType
	{
		/**
		 * @brief No action.
		 */
		None = 0,

		/**
		 * @brief Add the associated component to the entity.
		 */
		Add = 1 << 0,

		/**
		 * @brief Remove the associated component from the entity.
		 */
		Remove = 1 << 1,

		/**
		 * @brief Enable interpolation for the action.
		 */
		Smooth = 1 << 2,
	};

	MINTY_ENABLE_ENUM_OPERATORS(AnimationActionType)

	String to_string(AnimationActionType const obj);
	AnimationActionType parse_to_animation_action_type(String const& string);
	Bool parse_try_animation_action_type(String const& string, AnimationActionType& value);
	template<>
	inline AnimationActionType parse_to<AnimationActionType>(String const& string) { return parse_to_animation_action_type(string); }
	template<>
	inline Bool parse_try<AnimationActionType>(String const& string, AnimationActionType& value) { return parse_try_animation_action_type(string, value); }
}

#endif // MINTY_ANIMATION_ANIMATIONACTIONFLAGS_H