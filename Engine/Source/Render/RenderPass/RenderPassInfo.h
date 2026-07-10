#pragma once

/**
 * @file RenderPassInfo.h
 * @brief Header file defining the RenderPassInfo struct.
 * @author Mitchell Talyat
 */

#include "Resource/RenderPass/RenderAttachment.h"
#include "Core/Data/Span.h"
#include "Render/Type/Handle.h"

namespace Minty
{
    /**
	 * @brief The arguments for a RenderPass.
	 */
	struct RenderPassInfo
	{
		Span<RenderAttachment> attachments;
        
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
