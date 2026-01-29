#ifndef MINTY_RENDER_IMAGELAYOUT_H
#define MINTY_RENDER_IMAGELAYOUT_H

/**
 * @file ImageLayout.h
 * @brief Header file defining the ImageLayout enum.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Enum.h"
#include "Minty/Serialization/Parser.h"

namespace Minty
{
	/**
	 * @brief Determines how the image data is laid out in memory.
	 */
	enum class ImageLayout
	{
		/**
		 * @brief Invalid.
		 */
		Undefined = 0,

		/**
		 * @brief Generic layout.
		 */
		General = 1,

		/**
		 * @brief Color attachment.
		 */
		ColorAttachment = 2,

		/**
		 * @brief Depth stencil attachment.
		 */
		DepthStencilAttachment = 3,

		/**
		 * @brief Depth stencil read only.
		 */
		DepthStencilReadOnly = 4,

		/**
		 * @brief Shader read only.
		 */
		ShaderReadOnly = 5,

		/**
		 * @brief Transfer source location.
		 */
		TransferSource = 6,

		/**
		 * @brief Transfer destination location.
		 */
		TransferDestination = 7,

		/**
		 * @brief Pre-initialized.
		 */
		Preinitialized = 8,

		/**
		 * @brief Presentation layout (ready to be rendered).
		 */
		Presentation = 9,
	};

	MINTY_ENABLE_ENUM_OPERATORS(ImageLayout);
	
	template<>
	struct Parser<ImageLayout>
	{
		static Bool parse(StringView const str, ImageLayout& value);
		static String to_string(ImageLayout const& obj);
	};
}

#endif // MINTY_RENDER_IMAGELAYOUT_H