#pragma once

/**
 * @file ImageInfo.h
 * @brief Header file defining the ImageInfo struct.
 * @author Mitchell Talyat
 */

#include "ImageAspect.h"
#include "ImageFormat.h"
#include "ImageLayout.h"
#include "ImageType.h"
#include "ImageTiling.h"
#include "ImageUsage.h"
#include "Core/Data/Path.h"
#include "Core/Type/UInt2.h"
#include "Core/Constant/Invalid.h"
#include "Resource/Type/Handle.h"
#include "Core/Data/ConstantContainer.h"

namespace Minty
{
    /**
     * @brief Arguments for creating an Image.
     */
    struct ImageInfo
    {
        /**
         * @brief The size of the image in pixels.
         */
        UInt2 size = { 0, 0 };

        /**
         * @brief The data for the image, which may include the file path or other relevant information needed to load the image.
         */
        ConstantContainer data = {};

        /**
         * @brief The format of the image.
         */
        ImageFormat format = ImageFormatEnum::Default;

        /**
		 * @brief The type of the Image.
		 */
		ImageType type = ImageTypeEnum::D2;

		/**
		 * @brief The tiling of the Image.
		 */
		ImageTiling tiling = ImageTilingEnum::Optimal;
		
		/**
		 * @brief The aspect of the Image.
		 */
		ImageAspectFlags aspect = ImageAspectFlagsEnum::Color;

		/**
		 * @brief The usage of the Image.
		 */
		ImageUsageFlags usage = ImageUsageFlagsEnum::Sampled;

        /**
         * @brief If true, the image data is immutable and will not be changed after creation. This allows the render manager to make certain optimizations when creating the image resource.
         */
        Bool immutable = false;
    };
}