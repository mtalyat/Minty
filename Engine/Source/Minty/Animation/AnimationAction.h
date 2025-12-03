#ifndef MINTY_ANIMATION_ANIMATIONACTION_H
#define MINTY_ANIMATION_ANIMATIONACTION_H

/**
 * @file AnimationAction.h
 * @brief Defines the AnimationAction struct for animation actions.
 * @author Mitchell Talyat
 */

#include "Minty/Animation/AnimationActionFlags.h"
#include "Minty/Serialization/Parseable.h"
#include "Minty/Data/Tuple.h"
#include "Minty/Data/Vector.h"

namespace Minty
{
	/**
	 * @brief An action to be taken during an animation at a specific time.
	 */
	struct AnimationAction
		: public Parseable
	{
		/**
		 * @brief The index to the Entity to act upon.
		 */
		UInt entityIndex = 0;

		/**
		 * @brief The index to the Component to act upon.
		 */
		UInt componentIndex = 0;

		/**
		 * @brief The flags to use on this step.
		 */
		AnimationActionType type = AnimationActionType::None;

		/**
		 * @brief A vector of key-value variable-names and values to set when the time is reached.
		 */
		Vector<Tuple<UInt, UInt>> values;

		Bool parse(String const& text) override;
		String to_string() const override;
	};
}

#endif // MINTY_ANIMATION_ANIMATIONACTION_H