#pragma once

/**
 * @file Alignment.h
 * @brief Common alignment definitions for the platform.
 * @author Mitchell Talyat
 */

#include "Platform/Macro/Keyword.hpp"
#include "Primitive.hpp"

namespace Minty::Internal
{
    constexpr Size compute_alignment(Size const count, Size const size)
    {
        Size const totalSize = count * size;

        if (totalSize >= 32)
        {
            return 32;
        }
        else if (totalSize >= 16)
        {
            return 16;
        }
        else if (totalSize >= 8)
        {
            return 8;
        } else
        {
            return alignof(std::max_align_t);
        }
    }
}

#define MINTY_ALIGN_TYPE(type, count) MINTY_ALIGN((Internal::compute_alignment(count, sizeof(type))))