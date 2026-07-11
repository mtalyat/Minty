#pragma once

#include "Render/Geometry/GeometryIndexType.h"
#include "Platform/Type/Primitive.h"
#include "Core/Data/View.h"

namespace Minty
{
    struct GeometryInfo
    {
        View vertexData = {};
        Size vertexStride = 0;

        View indexData = {};
        GeometryIndexType indexType = {};
    };
}