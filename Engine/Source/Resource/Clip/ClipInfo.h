#pragma once

/**
 * @file ClipInfo.h
 * @brief Defines the ClipInfo struct which contains information about an audio clip resource.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"
#include "Core/Data/ConstantContainer.h"

namespace Minty
{
    /**
     * @brief The ClipInfo struct contains information about an audio clip resource, including its volume, pitch, loop point, and looping behavior.
     */
    struct ClipInfo
    {
        /**
         * @brief The raw audio data of the clip.
         */
        Span<Byte> data = {};
        
        /**
         * @brief The volume of the audio clip, ranging from 0.0f (silent) to 1.0f (full volume).
         */
        Float volume = 1.0f;

        /**
         * @brief The loop point of the audio clip, specified as a value between 0.0f and 1.0f representing the normalized position in the clip where looping should occur.
         */
        Float loopPoint = 0.0f;
        
        /**
         * @brief Whether the audio clip should loop when it reaches the end.
         */
        Bool looping = false;

        /**
         * @brief Whether the audio clip is exclusive, meaning it cannot be played simultaneously with other clips.
         */
        Bool exclusive = false;
    };
}