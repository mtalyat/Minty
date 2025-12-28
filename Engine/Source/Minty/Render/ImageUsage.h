#ifndef MINTY_RENDER_IMAGEUSAGE_H
#define MINTY_RENDER_IMAGEUSAGE_H

/**
 * @file ImageUsage.h
 * @brief Header file defining the ImageUsage enum.
 * @author Mitchell Talyat
 */

#include "Minty/Serialization/Parser.h"

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
	
	template<>
	struct Parser<ImageUsage>
	{
		static Bool parse(StringView const str, ImageUsage& value);
		static String to_string(ImageUsage const& obj);
	};
}

#endif // MINTY_RENDER_IMAGEUSAGE_H