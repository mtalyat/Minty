#pragma once

#include "Render/Camera/CameraPerspective.hpp"

namespace Minty
{
    struct CameraInfo
    {
        CameraPerspective perspective = CameraPerspectiveEnum::Default;
        Float fov = 45.0f;
        Float nearPlane = 0.1f;
        Float farPlane = 100.0f;
        Float aspectRatio = 16.0f / 9.0f;
        Float size = 5.0f;
    };
}