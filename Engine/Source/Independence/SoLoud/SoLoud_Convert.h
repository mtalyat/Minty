#pragma once

/**
 * @file SoLoud_Convert.h
 * @brief Header file defining the Converter specializations for SoLoud types.
 * @author Mitchell Talyat
 */

#include "Library/SoLoud/SoLoud.h"
#include "Core/Convert/Converter.h"
#include "Audio/AudioSource/Attenuation.h"

namespace Minty
{
    template<>
    struct Converter<Attenuation, unsigned int>
    {
        static Attenuation to_minty(unsigned int const& value);
        static unsigned int from_minty(Attenuation const& value);
    };
}