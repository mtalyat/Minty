#pragma once

/**
 * @file SoLoud_AudioClip.h
 * @brief Header file for the SoLoud implementation of the AudioClip.
 * @author Mitchell Talyat
 */

#include "Library/SoLoud/SoLoud.hpp"
#include "Platform/Type/Primitive.hpp"

namespace Minty
{
    struct SoLoud_ClipData
    {
        SoLoud::Wav wav;
    };
}