#pragma once

#include "Platform/Type/Primitive.h"
#include "Core/Data/View.h"

namespace Minty
{
    struct GeometryInfo
    {
        View vertexData = {};
        Size vertexStride = 0;

        View indexData = {};
        Size indexStride = 0;
    };
}