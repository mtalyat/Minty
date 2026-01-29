#ifndef MINTY_ANIMATION_ANIMATIONINFO_H
#define MINTY_ANIMATION_ANIMATIONINFO_H

/**
 * @file AnimationInfo.h
 * @brief Defines the AnimationInfo struct used for creating Animations.
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/Tuple.h"
#include "Minty/Data/UUID.h"
#include "Minty/Data/Vector.h"

namespace Minty
{
    class EntityPath;
    class Node;
    struct AnimationAction;

    /**
	 * @brief The arguments for an animation.
	 */
	struct AnimationInfo
	{
		/**
		 * @brief The Asset ID.
		 */
		UUID id = UUID();

		/**
		 * @brief The paths to the Entities to animate.
		 */
		Vector<EntityPath> entities;

		/**
		 * @brief The components being modified by this Animation.
		 */
		Vector<String> components;

		/**
		 * @brief The names of the variables being modified by this Animation that are rigid (not interpolated).
		 */
		Vector<String> rigidVariables;

		/**
		 * @brief The names of the variables being modified by this Animation that are smooth (interpolated).
		 */
		Vector<String> smoothVariables;

		/**
		 * @brief The values to set the variables to.
		 */
		Vector<Node> values;

		/**
		 * @brief The actions to take during the Animation.
		 */
		Vector<AnimationAction> actions;

		/**
		 * @brief The times and indices to the actions to take during the Animation.
		 * The times are expected to be in ascending order.
		 * There are to be no duplicate times.
		 */
		Vector<Tuple<Float, Vector<Size>>> steps;

		/**
		 * @brief Indices to the actions to take to reset the Animation to the beginning.
		 */
		Vector<Size> resetSteps;

		/**
		 * @brief The amount of time this animation takes to complete, in seconds.
		 */
		Float duration = 0.0f;

		/**
		 * @brief When true, the animation will restart after it ends.
		 */
		Bool loop = false;
	};
}

#endif // MINTY_ANIMATION_ANIMATIONINFO_H