#pragma once

#include "Platform/Type/Primitive.h"
#include "Core/Type/Float3.h"
#include "Render/Camera/CameraPerspective.h"
#include "Core/Type/Color.h"

namespace Minty
{
    struct Camera
    {
        Float3 position;
        Float3 direction;

        CameraPerspective perspective = CameraPerspectiveEnum::Default;

        Float fov = 45.0f;
        Float nearPlane = 0.1f;
        Float farPlane = 100.0f;
        Float aspectRatio = 16.0f / 9.0f;
        Float size = 5.0f;
    };
}