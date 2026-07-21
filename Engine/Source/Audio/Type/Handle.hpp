#pragma once

/**
 * @file Handle.hpp
 * @brief Header file defining the Handle type for Audio layer.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Core/Type/Handle.hpp"

namespace Minty
{
    class Clip;
    using ClipHandle = Handle<Clip>;

    enum class AudioSourceHandle : Index {};
    
    enum class AudioHandle : UInt32 {};
}