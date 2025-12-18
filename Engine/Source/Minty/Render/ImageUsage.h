#ifndef MINTY_RENDER_IMAGEUSAGE_H
#define MINTY_RENDER_IMAGEUSAGE_H

/**
 * @file ImageUsage.h
 * @brief Header file defining the ImageUsage enum.
 * @author Mitchell Talyat
 */

#include "Minty/Data/String.h"
#include "Minty/Serialization/Parse.h"

namespace Minty
{
	/**
	 * @brief Determines how the image is used.
	 */
	enum class ImageUsage
	{
		/**
		 * @brief Invalid.
		 */
		Undefined = 0x0,

		/**
		 * @brief The image is sampled.
		 */
		Sampled = 0x1,

		/**
		 * @brief The image is used for storage.
		 */
		Storage = 0x2,

		/**
		 * @brief The image is used for input attachment.
		 */
		Color = 0x4,

		/**
		 * @brief The image is used for depth/stencil.
		 */
		DepthStencil = 0x8,

		/**
		 * @brief The image is used as a transfer source.
		 */
		TransferSrc = 0x10,

		/**
		 * @brief The image is used as a transfer destination.
		 */
		TransferDst = 0x20,

		Max = TransferDst,
	};

	MINTY_ENABLE_ENUM_OPERATORS(ImageUsage);

	String to_string(ImageUsage const obj);
	ImageUsage parse_to_image_usage(String const& string);
	Bool parse_try_image_usage(String const& string, ImageUsage& value);
	template<>
	inline ImageUsage parse_to<ImageUsage>(StringView const string) { return parse_to_image_usage(string); }
	template<>
	inline Bool parse_try<ImageUsage>(StringView const string, ImageUsage& value) { return parse_try_image_usage(string, value); }
}

#endif // MINTY_RENDER_IMAGEUSAGE_H