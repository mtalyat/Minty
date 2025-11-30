#ifndef MINTY_RENDER_IMAGELAYOUT_H
#define MINTY_RENDER_IMAGELAYOUT_H

/**
 * @file ImageLayout.h
 * @brief Header file defining the ImageLayout enum.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Enum.h"
#include "Minty/Data/String.h"
#include "Minty/Serialization/Parse.h"

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

	String to_string(ImageLayout const obj);
	ImageLayout parse_to_image_layout(String const& string);
	Bool parse_try_image_layout(String const& string, ImageLayout& value);
	template<>
	inline ImageLayout parse_to<ImageLayout>(String const& string) { return parse_to_image_layout(string); }
	template<>
	inline Bool parse_try<ImageLayout>(String const& string, ImageLayout& value) { return parse_try_image_layout(string, value); }
}

#endif // MINTY_RENDER_IMAGELAYOUT_H