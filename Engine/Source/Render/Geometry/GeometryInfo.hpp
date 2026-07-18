#pragma once

#include "Render/Geometry/GeometryIndexType.hpp"
#include "Platform/Type/Primitive.hpp"
#include "Core/Data/View.hpp"

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