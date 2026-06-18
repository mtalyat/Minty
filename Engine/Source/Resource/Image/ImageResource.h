#pragma once

/**
 * @file ImageInfo.h
 * @brief Header file defining the ImageInfo struct.
 * @author Mitchell Talyat
 */

#include "ImageFormat.h"
#include "ImageType.h"
#include "ImageTiling.h"
#include "ImageUsage.h"
#include "Core/Type/UInt2.h"
#include "Core/Memory/DefaultAllocator.h"
#include "Core/Serialize/Serializer.h"
#include "Core/Data/ConstantContainer.h"
#include "Core/Data/Vector.h"

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