#pragma once

#include "Core/Math/Matrix4x4.hpp"
#include "Core/Type/Float3.hpp"
#include "Render/Camera/CameraPerspective.hpp"
#include "Platform/Type/Primitive.hpp"

namespace Minty
{
    struct Vulkan_RenderViewData
    {
        CameraPerspectiveEnum perspective = CameraPerspectiveEnum::Undefined;
        Float fov = 45.0f;
        Float nearPlane = 0.1f;
        Float farPlane = 100.0f;
        Float aspectRatio = 16.0f / 9.0f;
        Float size = 5.0f;

        Matrix4 viewMatrix;
        Matrix4 projectionMatrix;
        Matrix4 viewProjectionMatrix;

        Float3 position;

        void update_projection(Float const aspect)
        {
            switch (perspective)
            {
            case CameraPerspectiveEnum::Perspective:
                projectionMatrix = Math::perspective(fov, aspect, nearPlane, farPlane);
                break;
            case CameraPerspectiveEnum::Orthographic:
                projectionMatrix = Math::orthographic(size, aspect, nearPlane, farPlane);
                break;
            default:
                MINTY_NOT_IMPLEMENTED();
                break;
            }

            projectionMatrix[1][1] *= -1.0f;
        }

        // TODO: Frustrum planes for culling
    };
}