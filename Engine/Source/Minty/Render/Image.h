#ifndef MINTY_RENDER_IMAGE_H
#define MINTY_RENDER_IMAGE_H

/**
 * @file Image.h
 * @brief Header file defining the Image class and ImageInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Asset/Asset.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Vector.h"
#include "Minty/Render/Format.h"
#include "Minty/Render/ImageAspect.h"
#include "Minty/Render/ImageTiling.h"
#include "Minty/Render/ImageType.h"
#include "Minty/Render/ImageUsage.h"

namespace Minty
{
	struct ImageInfo;

	/**
	 * @brief Represents an Image.
	 */
	class Image
		: public Asset
	{
#pragma region Constructor

	public:
		/**
		 * @brief Creates a new Image.
		 * @param info The arguments.
		 */
		Image(ImageInfo const& info);

		virtual ~Image() = default;

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Sets the pixel data of the Image. Assumes the pointer points to a size of width * height * channels.
		 * @param data A pointer to the byte data.
		 * @param size The size of the data in bytes.
		 */
		virtual void set_pixels(void const* const data, Size const size) = 0;

		/**
		 * @brief Pure virtual method that retrieves pixel data and writes it into a caller-provided output buffer.
		 * @param outData Pointer to the output buffer where the pixel data will be written. The caller must provide a valid, sufficiently large buffer; the concrete implementation defines the pixel format and layout.
		 * @param size Size value indicating how much pixel data to write. The precise meaning (for example, number of bytes, number of pixels, or width/height) depends on the concrete implementation of Size and the derived class.
		 */
		virtual void get_pixels(Any const outData, Size const size) const = 0;

		/**
		 * @brief Gets the Format.
		 * @return The Format.
		 */
		inline Format get_format() const { return m_format; }

		/**
		 * @brief Gets the ImageType.
		 * @return The ImageType.
		 */
		inline ImageType get_type() const { return m_type; }

		/**
		 * @brief Gets the ImageTiling.
		 * @return The ImageTiling.
		 */
		inline ImageTiling get_tiling() const { return m_tiling; }

		/**
		 * @brief Gets the ImageAspect.
		 * @return The ImageAspect.
		 */
		inline ImageAspect get_aspect() const { return m_aspect; }

		/**
		 * @brief Gets the ImageUsage.
		 * @return The ImageUsage.
		 */
		inline ImageUsage get_usage() const { return m_usage; }

		/**
		 * @brief Gets the size of the Image.
		 * @return The size of the Image.
		 */
		inline UInt2 get_size() const { return m_size; }

		/**
		 * @brief Checks if the Image is immutable.
		 * @return True, if the image is immutable.
		 */
		inline Bool is_immutable() const { return m_immutable; }

		/**
		 * @brief Gets the native Image object.
		 * @return A pointer to the native object.
		 */
		virtual Any get_native() const = 0;

		/**
		 * @brief Returns AssetType::Image.
		 * @return AssetType::Image.
		 */
		inline AssetType get_asset_type() const { return AssetType::Image; }

		/**
		 * @brief Creates a new Image.
		 * @param info An ImageInfo.
		 * @return An Image Owner.
		 */
		static Shared<Image> create(ImageInfo const& info);

#pragma endregion

#pragma region Variables

	protected:
		Format m_format;
		ImageType m_type;
		ImageTiling m_tiling;
		ImageAspect m_aspect;
		ImageUsage m_usage;
		UInt2 m_size;
		Bool m_immutable;

#pragma endregion
	};
}

#endif // MINTY_RENDER_IMAGE_H