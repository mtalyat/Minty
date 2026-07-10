#pragma once

#include "Platform/Type/Primitive.h"
#include "Core/Type/Float3.h"
#include "Render/Type/Handle.h"

namespace Minty
{
    struct RenderViewInfo
    {
        /**
         * @brief The position of the RenderView in world space.
         */
        Float3 position = Math::ZERO;

        /**
         * @brief The direction the RenderView is facing in world space.
         */
        Float3 direction = Math::FORWARD;
    };
}