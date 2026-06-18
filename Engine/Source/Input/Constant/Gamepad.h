#pragma once

/**
 * @file Input.h
 * @brief Header file for input-related contants.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"

namespace Minty
{
    /**
     * @brief The deadzone for joystick axes, below which the value will be rounded to zero.
     */
    constexpr Float JOYSTICK_DEADZONE = 0.1f;
}