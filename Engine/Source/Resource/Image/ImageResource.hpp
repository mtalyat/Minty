#pragma once

/**
 * @file ImageInfo.h
 * @brief Header file defining the ImageInfo struct.
 * @author Mitchell Talyat
 */

#include "ImageFormat.hpp"
#include "ImageType.hpp"
#include "ImageTiling.hpp"
#include "ImageUsage.hpp"
#include "Core/Type/UInt2.hpp"
#include "Core/Memory/DefaultAllocator.hpp"
#include "Core/Serialize/Serializer.hpp"
#include "Core/Data/ConstantContainer.hpp"
#include "Core/Data/Vector.hpp"

namespace Minty
{
    struct ImageInfo;

    /**
     * @brief A simple Image class that holds pixel data and dimensions.
     */
    struct ImageResource
    {
        Vector<Byte> data = {};
        ImageFormat format = ImageFormatEnum::Default;
        ImageType type = ImageTypeEnum::Default;
        ImageTiling tiling = ImageTilingEnum::Default;
        ImageUsageFlags usage = ImageUsageFlagsEnum::Default;
        UInt2 size = {0, 0};
        Bool immutable = false;
    };

    template<>
    struct Serializer<ImageResource>
    {
        static Bool serialize(Writer &writer, ImageResource const &value);
        static Bool deserialize(Reader &reader, ImageResource &value);
    };
}