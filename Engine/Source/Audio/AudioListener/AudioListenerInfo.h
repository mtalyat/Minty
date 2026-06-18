#pragma once

/**
 * @file AudioListenerInfo.h
 * @brief Header file defining the AudioListenerInfo struct.
 * @author Mitchell Talyat
 */

#include "Core/Type/Float3.h"

namespace Minty
{
    /**
     * @brief Struct representing the data for an audio listener, which defines the position, velocity, and orientation of the listener in 3D space for spatial audio processing.
     */
    struct AudioListenerInfo
    {
        Float3 position;
        Float3 velocity;
        Float3 forward;
        Float3 up;
    };
}