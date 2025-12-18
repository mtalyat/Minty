#ifndef MINTY_RENDER_RENDERATTACHMENT_H
#define MINTY_RENDER_RENDERATTACHMENT_H

/**
 * @file RenderAttachment.h
 * @brief Header file defining the RenderAttachment struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Render/Format.h"
#include "Minty/Render/ImageLayout.h"
#include "Minty/Render/LoadOperation.h"
#include "Minty/Render/StoreOperation.h"

namespace Minty
{
	/**
	 * @brief Holds data for an attachment in a render pass.
	 */
	struct RenderAttachment
	{
#pragma region Types

	public:
		/**
		 * @brief The type.
		 */
		enum class Type
		{
			/**
			 * @brief Invalid.
			 */
			Undefined,

			/**
			 * @brief Color attachment.
			 */
			Color,

			/**
			 * @brief Depth attachment.
			 */
			Depth
		};

#pragma endregion

#pragma region Variables

	public:
		/**
		 * @brief The Type of this attachment.
		 */
		Type type = Type::Undefined;

		/**
		 * @brief The load operation to perform.
		 */
		LoadOperation loadOperation = LoadOperation::DontCare;

		/**
		 * @brief The store operation to perform.
		 */
		StoreOperation storeOperation = StoreOperation::DontCare;

		/**
		 * @brief The initial layout of this attachment.
		 */
		ImageLayout initialLayout = ImageLayout::Undefined;

		/**
		 * @brief The final layout of this attachment.
		 */
		ImageLayout finalLayout = ImageLayout::Undefined;

#pragma endregion
	};
}

#endif // MINTY_RENDER_RENDERATTACHMENT_H