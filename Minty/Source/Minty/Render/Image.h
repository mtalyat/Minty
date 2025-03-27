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
	struct ImageBuilder
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
		/// The pixels of the image.
		/// </summary>
		Vector<Byte> pixels;

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

	private:
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
		/// <param name="builder">The arguments.</param>
	public:
		Image(ImageBuilder const& builder)
			: Asset(builder.id)
			, m_format(builder.format)
			, m_type(builder.type)
			, m_tiling(builder.tiling)
			, m_aspect(builder.aspect)
			, m_usage(builder.usage)
			, m_size(builder.size)
			, m_immutable(builder.immutable)
		{
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
		/// <param name="pixels">A pointer to the byte data.</param>
		virtual void set_pixels(Byte const* const data) = 0;

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
		virtual void get_native() const = 0;

		/// <summary>
		/// Returns AssetType::Image.
		/// </summary>
		/// <returns>AssetType::Image.</returns>
		constexpr AssetType get_asset_type() const { return AssetType::Image; }

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Resizes the Image with the new size and format.
		/// </summary>
		/// <param name="newSize">The new size of the Image.</param>
		/// <param name="newFormat">The new Format of the Image.</param>
		virtual void resize(UInt2 const newSize, Format const newFormat) = 0;

		/// <summary>
		/// Resizes the Image with the new size.
		/// </summary>
		/// <param name="newSize">The new size of the Image.</param>
		inline void resize(UInt2 const newSize) { resize(newSize, m_format); }

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Creates a new Image.
		/// </summary>
		/// <param name="builder">An ImageBuilder.</param>
		/// <returns>An Image Owner.</returns>
		Owner<Image> create(ImageBuilder const& builder = {});

#pragma endregion

	};
}