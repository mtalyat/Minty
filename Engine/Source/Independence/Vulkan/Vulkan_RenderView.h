#pragma once

#include "Core/Math/Matrix4x4.h"
#include "Core/Type/Float3.h"

namespace Minty
{
    struct Vulkan_RenderViewData
    {
        Matrix4 viewMatrix;
        Matrix4 projectionMatrix;
        Matrix4 viewProjectionMatrix;

        Float3 position;

        // TODO: Frustrum planes for culling
    };
}