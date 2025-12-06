#ifndef MINTY_RENDER_RENDERPASSINFO_H
#define MINTY_RENDER_RENDERPASSINFO_H

/**
 * @file RenderPassInfo.h
 * @brief Header file defining the RenderPassInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/UUID.h"

namespace Minty
{
    struct RenderAttachment;

    /**
	 * @brief The arguments for a RenderPass.
	 */
	struct RenderPassInfo
	{
		/**
		 * @brief The ID.
		 */
		UUID id = {};

		/**
		 * @brief The color attachment, if any.
		 */
		RenderAttachment const* colorAttachment = nullptr;

		/**
		 * @brief The depth attachment, if any.
		 */
		RenderAttachment const* depthAttachment = nullptr;
	};
}

#endif // MINTY_RENDER_RENDERPASSINFO_H