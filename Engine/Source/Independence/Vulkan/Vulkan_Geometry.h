#pragma once

#include "Library/Vulkan/Vulkan.h"
#include "Platform/Type/Primitive.h"
#include "Render/Type/Handle.h"

namespace Minty
{
    struct Vulkan_GeometryData
    {
        BufferHandle vertexBuffer = INVALID_HANDLE;
        Size vertexCount = 0;
        Size vertexStride = 0;

        BufferHandle indexBuffer = INVALID_HANDLE;
        Size indexCount = 0;
        VkIndexType indexType = VK_INDEX_TYPE_UINT16;
    };
}