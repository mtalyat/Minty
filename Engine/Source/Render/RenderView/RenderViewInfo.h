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
        Float3 position;

        /**
         * @brief The direction the RenderView is facing in world space.
         */
        Float3 direction;
        
		/**
		 * @brief The RenderTarget to render to.
		 */
		RenderTargetHandle renderTarget = INVALID_HANDLE;

		/**
		 * @brief The Viewport to render to. Leave as INVALID_HANDLE to use the default viewport.
		 */
		ViewportHandle viewport = INVALID_HANDLE;
    };
}