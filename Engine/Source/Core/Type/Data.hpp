#pragma once

/**
 * @file Data.h
 * @brief Header file for data structures and types.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"

namespace Minty
{
    /**
     * @brief A simple struct to hold a pointer to data and its size.
     */
    struct Data
    {
        /**
         * @brief Pointer to the data.
         */
        Pointer data = nullptr;

        /**
         * @brief Size of the data in bytes.
         */
        Size size = 0;
    };
}