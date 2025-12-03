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

    /// <summary>
	/// The arguments for an animation.
	/// </summary>
	struct AnimationInfo
	{
		/// <summary>
		/// The Asset ID.
		/// </summary>
		UUID id = UUID();

		/// <summary>
		/// The amount of time this animation takes to complete, in seconds.
		/// </summary>
		Float duration = 0.0f;

		/// <summary>
		/// When true, the animation will restart after it ends.
		/// </summary>
		Bool loop = false;

		/// <summary>
		/// The paths to the Entities to animate.
		/// </summary>
		Vector<EntityPath> entities;

		/// <summary>
		/// The components being modified by this Animation.
		/// </summary>
		Vector<String> components;

		/// <summary>
		/// The names of the variables being modified by this Animation that are rigid (not interpolated).
		/// </summary>
		Vector<String> rigidVariables;

		/// <summary>
		/// The names of the variables being modified by this Animation that are smooth (interpolated).
		/// </summary>
		Vector<String> smoothVariables;

		/// <summary>
		/// The values to set the variables to.
		/// </summary>
		Vector<Node> values;

		/// <summary>
		/// The actions to take during the Animation.
		/// </summary>
		Vector<AnimationAction> actions;

		/// <summary>
		/// The times and indices to the actions to take during the Animation.
		/// The times are expected to be in ascending order.
		/// There are to be no duplicate times.
		/// </summary>
		Vector<Tuple<Float, Vector<Size>>> steps;

		/// <summary>
		/// Indices to the actions to take to reset the Animation to the beginning.
		/// </summary>
		Vector<Size> resetSteps;
	};
}

#endif // MINTY_ANIMATION_ANIMATIONINFO_H