#pragma once

/**
 * @file STB_Image.h
 * @brief Header file for the STB image loading library.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"
#include "Library/STB/STB.h"

namespace Minty
{
    /**
     * @brief Loads an image from a memory buffer using the STB library.
     * @param buffer The memory buffer containing the image data to load.
     * @param bufferSize The size of the memory buffer in bytes.
     * @return A pointer to the loaded image data, or nullptr if loading failed.
     */
    Byte* load_image_data_from_memory(Byte const* const buffer, Int const bufferSize, Int& width, Int& height, Int& channels);

    /**
     * @brief Frees the memory allocated for an image loaded with load_image_data_from_memory.
     * @param data The pointer to the image data to free.
     */
    void free_image_data(Byte* const data);
}