#ifndef MINTY_RENDER_IMAGEINFO_H
#define MINTY_RENDER_IMAGEINFO_H

/**
 * @file ImageInfo.h
 * @brief Header file defining the ImageInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/UUID.h"
#include "Minty/Render/Format.h"
#include "Minty/Render/ImageAspect.h"
#include "Minty/Render/ImageTiling.h"
#include "Minty/Render/ImageType.h"
#include "Minty/Render/ImageUsage.h"

namespace Minty
{
    /**
	 * @brief The arguments for an Image.
	 */
	struct ImageInfo
	{
		/**
		 * @brief The ID of the Image.
		 */
		UUID id = UUID();

		/**
		 * @brief The format of the Image.
		 */
		Format format = Format::Default;

		/**
		 * @brief The type of the Image.
		 */
		ImageType type = ImageType::D2;

		/**
		 * @brief The tiling of the Image.
		 */
		ImageTiling tiling = ImageTiling::Optimal;
		
		/**
		 * @brief The aspect of the Image.
		 */
		ImageAspect aspect = ImageAspect::Color;

		/**
		 * @brief The usage of the Image.
		 */
		ImageUsage usage = ImageUsage::Sampled;

		/**
		 * @brief A pointer to the pixel data.
		 */
		Any pixelData = nullptr;

		/**
		 * @brief The size of the pixel data in bytes.
		 */
		Size pixelDataSize = 0;

		/**
		 * @brief The size of the Image.
		 */
		UInt2 size = { 0, 0 };

		/**
		 * @brief If true, the Image data is not able to be modified.
		 */
		Bool immutable = false;
	};
}

#endif // MINTY_RENDER_IMAGEINFO_H