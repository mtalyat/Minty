#pragma once

/**
 * @file Limit.hpp
 * @brief Common limit definitions for the platform.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"

namespace Minty
{
    /**
     * @brief The maximum value of a Size type.
     */
    constexpr Size MAX_SIZE = static_cast<Size>(-1);
    
    /**
     * @brief The maximum indentation level for serialization.
     */
    constexpr Size SERIALIZATION_MAX_INDENTATION = 255;
}