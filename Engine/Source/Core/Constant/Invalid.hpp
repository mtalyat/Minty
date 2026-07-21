#pragma once

/**
 * @file Invalid.hpp
 * @brief Common invalid definitions for the platform.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"

namespace Minty
{
    /**
     * @brief A template for defining invalid values of various types, typically used to indicate errors or not found conditions in handle indexing and file operations.
     * @param T The type for which to define the invalid value.
     */
    template<typename T>
    constexpr T INVALID = static_cast<T>(~0);

    /**
     * @brief The invalid index value, typically used to indicate an error in handle indexing.
     */
    constexpr Index INVALID_INDEX = INVALID<Index>;

    /**
     * @brief The invalid generation value, typically used to indicate an error in handle generation.
     */
    constexpr Generation INVALID_GENERATION = 0;

    /**
     * @brief The invalid index value, typically used to indicate a not found condition.
     */
    constexpr Size INVALID_SIZE = INVALID<Size>;

    /**
     * @brief The invalid handle value, typically used to indicate an error in handle operations.
     */
    constexpr Size INVALID_HANDLE = 0;

    /**
     * @brief The invalid file position, typically used to indicate an error in file operations.
     */
    constexpr StreamPosition INVALID_FILE_POSITION = INVALID<StreamPosition>;
    
	#undef INVALID_FILE_SIZE
    /**
     * @brief The invalid file size, typically used to indicate an error in file size retrieval.
     */
	constexpr StreamSize INVALID_FILE_SIZE = INVALID<StreamSize>;
}