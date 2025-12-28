#ifndef MINTY_ANIMATION_ANIMATIONACTIONFLAGS_H
#define MINTY_ANIMATION_ANIMATIONACTIONFLAGS_H

/**
 * @file AnimationActionFlags.h
 * @brief Defines flags for actions to be taken during animation.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Enum.h"
#include "Minty/Serialization/Parser.h"

namespace Minty
{
	/**
	 * @brief Flags for actions to be taken during animation.
	 */
	enum class AnimationActionFlags
	{
		/**
		 * @brief No action.
		 */
		None = 0x0,

		/**
		 * @brief Add the associated component to the entity.
		 */
		Add = 0x1,

		/**
		 * @brief Remove the associated component from the entity.
		 */
		Remove = 0x2,

		/**
		 * @brief Enable interpolation for the action.
		 */
		Smooth = 0x4,
	};

	MINTY_ENABLE_ENUM_OPERATORS(AnimationActionFlags)

	struct Parser<AnimationActionFlags>
	{
		static Bool parse(StringView const str, AnimationActionFlags &value);
		static String to_string(AnimationActionFlags const &value);
	};
}

#endif // MINTY_ANIMATION_ANIMATIONACTIONFLAGS_H