#pragma once

/**
 * @file TextureInfo.h
 * @brief TextureInfo struct definition.
 * This file defines the TextureInfo struct, which contains metadata about a texture resource in the application.
 */

#include "Resource/Texture/TextureAddressMode.h"
#include "Resource/Texture/TextureFilter.h"
#include "Resource/Image/ImageAspect.h"
#include "Resource/Image/ImageFormat.h"
#include "Resource/Image/ImageType.h"
#include "Resource/Image/ImageTiling.h"
#include "Resource/Image/ImageUsage.h"
#include "Platform/Type/Primitive.h"
#include "Core/Type/UInt2.h"
#include "Core/Data/Span.h"

namespace Minty
{
    class ImageResource;

    /**
     * @struct TextureInfo
     * @brief Struct containing metadata about a texture resource.
     */
    struct TextureInfo
    {
        /**
         * @brief The size of the texture in pixels.
         */
        UInt2 size = { 0, 0 };

        /**
         * @brief The data for the texture.
         */
        Span<Byte> data = {};

        /**
         * @brief The format of the texture.
         */
        ImageFormat format = ImageFormatEnum::Default;

        /**
		 * @brief The type of the texture.
		 */
		ImageType type = ImageTypeEnum::D2;

		/**
		 * @brief The tiling of the texture.
		 */
		ImageTiling tiling = ImageTilingEnum::Optimal;
		
		/**
		 * @brief The aspect of the texture.
		 */
		ImageAspectFlags aspect = ImageAspectFlagsEnum::Color;

		/**
		 * @brief The usage of the texture.
		 */
		ImageUsageFlags usage = ImageUsageFlagsEnum::Sampled;

        /**
         * @brief The filter mode used for the texture.
         */
        TextureFilter filter = TextureFilterEnum::Default;

        /**
         * @brief The address mode used for the texture.
         */
        TextureAddressMode addressMode = TextureAddressModeEnum::Default;

        /**
         * @brief The number of mip levels in the texture. A value of 1 means no mipmaps, and higher values indicate additional mip levels.
         */
        UInt mipLevels = 1;

        /**
         * @brief When true, the texture coordinates will be normalized to the range [0, 1]. When false, the texture coordinates will be in pixel units.
         */
        Bool normalizeCoordinates = true;

        /**
         * @brief If true, the texture data is immutable and will not be changed after creation. This allows the render manager to make certain optimizations when creating the texture resource.
         */
        Bool immutable = false;
    };
}
