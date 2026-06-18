#pragma once

/**
 * @file AudioSourceInfo.h
 * @brief Header file defining the AudioSourceInfo struct.
 * @author Mitchell Talyat
 */

#include "Attenuation.h"
#include "Core/Type/Float3.h"

namespace Minty
{
    /**
     * @brief Struct representing the data for an audio source, which defines the position, velocity, and attenuation properties of the source in 3D space for spatial audio processing.
     */
    struct AudioSourceInfo
    {
        Float3 position;
        Float3 velocity;
        Attenuation attenuation;
        Float attenuationRolloff;
        Float minDistance;
        Float maxDistance;
    };
}