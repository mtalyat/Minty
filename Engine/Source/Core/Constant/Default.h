#pragma once

/**
 * @file Default.h
 * @brief Common default definitions for the platform.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"

namespace Minty
{
    /**
     * @brief The default size for collections that require an initial capacity.
     */
    constexpr Size DEFAULT_COLLECTION_SIZE = 16;

    /**
     * @brief The default load factor for hash-based collections.
     */
    constexpr Float DEFAULT_LOAD_FACTOR = 0.75f;

    /**
     * @brief The default empty string.
     */
    constexpr Char const *DEFAULT_TEXT_EMPTY = "";

    /**
     * @brief The default whitespace characters.
     */
    constexpr Char const *DEFAULT_TEXT_WHITESPACE = " \n\r\t\v\b\f";

    /**
     * @brief The default opening characters for groups.
     */
    constexpr Char const *DEFAULT_TEXT_OPEN = "([{<\"";
    
    /**
     * @brief The default closing characters for groups.
     */
    constexpr Char const *DEFAULT_TEXT_CLOSE = ")]}>\"";
}