#pragma once

/**
 * @file Handle.h
 * @brief Header file defining the Handle type for Audio layer.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"
#include "Core/Type/Handle.h"

namespace Minty
{
    class Clip;
    using ClipHandle = Handle<Clip>;

    enum class AudioSourceHandle : Index {};
    
    enum class AudioHandle : UInt32 {};
}