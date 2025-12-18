#ifndef MINTY_AUDIO_AUDIOCLIPINFO_H
#define MINTY_AUDIO_AUDIOCLIPINFO_H

/**
 * @file AudioClipInfo.h
 * @brief Header file defining the AudioClipInfo structure.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/UUID.h"

namespace Minty
{
    /**
     * @brief Structure containing information for creating an AudioClip.
     */
    struct AudioClipInfo
    {
        /**
         * @brief The ID of the AudioClip.
         */
        UUID id;

        /**
         * @brief The byte data of the AudioClip.
         */
        Byte* data = nullptr;

        /**
         * @brief The size of the audio data in bytes.
         */
        Size dataSize = 0;

        /**
         * @brief The starting volume of the AudioClip.
         */
        Float volume = 1.0f;

        /**
         * @brief If true, the AudioClip will loop.
         */
        Bool loop = false;

        /**
         * @brief The loop point of the AudioClip. 0.0 = start, 1.0 = end.
         */
        Float loopPoint = 0.0f;

        /**
         * @brief If true, the AudioClip can only be played once at a time.
         */
        Bool exclusive = false;
    };

}

#endif // MINTY_AUDIO_AUDIOCLIPINFO_H