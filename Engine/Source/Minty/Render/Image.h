#pragma once
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
	/// <summary>
	/// The arguments for an Image.
	/// </summary>
	struct ImageInfo
	{
		/// <summary>
		/// The ID of the Image.
		/// </summary>
		UUID id = INVALID_ID;

		/// <summary>
		/// The format of the Image.
		/// </summary>
		Format format = Format::Default;

		/// <summary>
		/// The type of the Image.
		/// </summary>
		ImageType type = ImageType::D2;

		/// <summary>
		/// The tiling of the Image.
		/// </summary>
		ImageTiling tiling = ImageTiling::Optimal;
		
		/// <summary>
		/// The aspect of the Image.
		/// </summary>
		ImageAspect aspect = ImageAspect::Color;

		/// <summary>
		/// The usage of the Image.
		/// </summary>
		ImageUsage usage = ImageUsage::Sampled;

		/// <summary>
		/// A pointer to the pixel data.
		/// </summary>
		void* pixelData = nullptr;

		/// <summary>
		/// The size of the pixel data in bytes.
		/// </summary>
		Size pixelDataSize = 0;

		/// <summary>
		/// The size of the Image.
		/// </summary>
		UInt2 size = { 0, 0 };

		/// <summary>
		/// If true, the Image data is not able to be modified.
		/// </summary>
		Bool immutable = false;
	};

	/// <summary>
	/// Represents an Image.
	/// </summary>
	class Image
		: public Asset
	{
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

#pragma region Constructor

		/// <summary>
		/// Creates a new Image.
		/// </summary>
		/// <param name="info">The arguments.</param>
	public:
		Image(ImageInfo const& info)
			: Asset(info.id)
			, m_format(info.format)
			, m_type(info.type)
			, m_tiling(info.tiling)
			, m_aspect(info.aspect)
			, m_usage(info.usage)
			, m_size(info.size)
			, m_immutable(info.immutable)
		{
			MINTY_ASSERT(info.format != Format::Undefined, ErrorCode::Argument_ExpectedNonDefault);
			MINTY_ASSERT(info.type != ImageType::Undefined, ErrorCode::Argument_ExpectedNonDefault);
			MINTY_ASSERT(info.tiling != ImageTiling::Undefined, ErrorCode::Argument_ExpectedNonDefault);
			MINTY_ASSERT(info.aspect != ImageAspect::Undefined, ErrorCode::Argument_ExpectedNonDefault);
			MINTY_ASSERT(info.usage != ImageUsage::Undefined, ErrorCode::Argument_ExpectedNonDefault);
			MINTY_ASSERT(info.size.x > 0 && info.size.y > 0, ErrorCode::Argument_ExpectedAboveZero);
		}

		virtual ~Image()
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Sets the pixel data of the Image. Assumes the pointer points to a size of width * height * channels.
		/// </summary>
		/// <param name="data">A pointer to the byte data.</param>
		/// <param name="size">The size of the data in bytes.</param>
		virtual void set_pixels(void const* const data, Size const size) = 0;

		/// <summary>
		/// Pure virtual method that retrieves pixel data and writes it into a caller-provided output buffer.
		/// </summary>
		/// <param name="outData">Pointer to the output buffer where the pixel data will be written. The caller must provide a valid, sufficiently large buffer; the concrete implementation defines the pixel format and layout.</param>
		/// <param name="size">Size value indicating how much pixel data to write. The precise meaning (for example, number of bytes, number of pixels, or width/height) depends on the concrete implementation of Size and the derived class.</param>
		virtual void get_pixels(void* const outData, Size const size) const = 0;

		/// <summary>
		/// Gets the Format.
		/// </summary>
		/// <returns>The Format.</returns>
		inline Format get_format() const { return m_format; }

		/// <summary>
		/// Gets the ImageType.
		/// </summary>
		/// <returns>The ImageType.</returns>
		inline ImageType get_type() const { return m_type; }

		/// <summary>
		/// Gets the ImageTiling.
		/// </summary>
		/// <returns>The ImageTiling.</returns>
		inline ImageTiling get_tiling() const { return m_tiling; }

		/// <summary>
		/// Gets the ImageAspect.
		/// </summary>
		/// <returns>The ImageAspect.</returns>
		inline ImageAspect get_aspect() const { return m_aspect; }

		/// <summary>
		/// Gets the ImageUsage.
		/// </summary>
		/// <returns>The ImageUsage.</returns>
		inline ImageUsage get_usage() const { return m_usage; }

		/// <summary>
		/// Gets the size of the Image.
		/// </summary>
		/// <returns>The size of the Image.</returns>
		inline UInt2 get_size() const { return m_size; }

		/// <summary>
		/// Checks if the Image is immutable.
		/// </summary>
		/// <returns>True, if the image is immutable.</returns>
		inline Bool is_immutable() const { return m_immutable; }

		/// <summary>
		/// Gets the native Image object.
		/// </summary>
		/// <returns>A pointer to the native object.</returns>
		virtual void* get_native() const = 0;

		/// <summary>
		/// Returns AssetType::Image.
		/// </summary>
		/// <returns>AssetType::Image.</returns>
		constexpr AssetType get_asset_type() const { return AssetType::Image; }

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Creates a new Image.
		/// </summary>
		/// <param name="info">An ImageInfo.</param>
		/// <returns>An Image Owner.</returns>
		static Owner<Image> create(ImageInfo const& info = {});

#pragma endregion

	};
}