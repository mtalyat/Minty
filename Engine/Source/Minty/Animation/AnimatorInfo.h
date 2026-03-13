#ifndef MINTY_ANIMATION_ANIMATORINFO_H
#define MINTY_ANIMATION_ANIMATORINFO_H

/**
 * @file AnimatorInfo.h
 * @brief Defines the AnimatorInfo struct used for creating Animators.
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/UUID.h"

namespace Minty
{
    class FSM;

    /**
     * @brief The arguments for an Animator.
     */
	struct AnimatorInfo
	{
        /**
         * @brief The Asset ID.
         */
		UUID id = UUID();

        /**
         * @brief The FSM controlling the animations.
         */
		FSM* fsm = nullptr;

        /**
         * @brief The time scale for the Animator. A value of 1.0 means normal speed, 0.5 means half speed, etc.
         */
        Float timeScale = 1.0f;

        /**
         * @brief If true, animations will transition as soon as possible.
         * Otherwise, they will wait until the current animation is finished.
         */
		Bool force = false;
	};
}

#endif // MINTY_ANIMATION_ANIMATORINFO_H