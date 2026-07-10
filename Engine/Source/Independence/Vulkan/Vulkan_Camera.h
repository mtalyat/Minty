#pragma once

#include "Platform/Type/Primitive.h"
#include "Library/Vulkan/Vulkan.h"
#include "Render/Type/Handle.h"
#include "Core/Type/Color.h"
#include "Render/Camera/CameraPerspective.h"
#include "Layer/LayerMask/LayerMask.h"

namespace Minty
{
    struct Vulkan_CameraData
    {
		CameraPerspective perspective = CameraPerspectiveEnum::Default;
		Float fov = 45.0f;
		Float nearPlane = 0.1f;
		Float farPlane = 100.0f;
		Color color = Color::black();
		Float aspectRatio = 16.0f / 9.0f;
		Float size = 5.0f;
		LayerMask mask = MASK_ALL;
        RenderTargetHandle renderTarget = INVALID_HANDLE;
        ViewportHandle viewport = INVALID_HANDLE;
    };
}