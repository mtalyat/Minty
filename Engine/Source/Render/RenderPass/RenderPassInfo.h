#pragma once

/**
 * @file RenderPassInfo.h
 * @brief Header file defining the RenderPassInfo struct.
 * @author Mitchell Talyat
 */

#include "Resource/RenderPass/RenderAttachment.h"
#include "Core/Data/Span.h"

namespace Minty
{
    /**
	 * @brief The arguments for a RenderPass.
	 */
	struct RenderPassInfo
	{
		Span<RenderAttachment> attachments;
	};
}
