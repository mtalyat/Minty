#pragma once
#include "Minty/Asset/Asset.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Render/Format.h"

namespace Minty
{
	class Window;
	class Image;

	struct SurfaceBuilder
	{
		/// <summary>
		/// The ID.
		/// </summary>
		UUID id = INVALID_ID;

		/// <summary>
		/// The desired format for the surface.
		/// </summary>
		Format targetFormat = Format::Default;

		/// <summary>
		/// The window to create the surface for.
		/// </summary>
		Ref<Window> window = nullptr;
	};

	/// <summary>
	/// Represents a surface, which is a platform-specific representation of a window screen that can be rendered to.
	/// </summary>
	class Surface
		: public Asset
	{
#pragma region Constructors

	public:
		Surface(SurfaceBuilder const& builder)
			: Asset(builder.id)
		{
		}

		virtual ~Surface()
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the size of this surface.
		/// </summary>
		/// <returns>The size of this surface in pixels.</returns>
		virtual UInt2 get_size() const = 0;

		/// <summary>
		/// Gets the Format of this surface.
		/// </summary>
		/// <returns>The Format this surface uses.</returns>
		virtual Format get_format() const = 0;

		/// <summary>
		/// Gets the current image index for this frame.
		/// </summary>
		/// <returns>The index of the current image being used.</returns>
		virtual UInt get_current_image_index() const = 0;

		/// <summary>
		/// Gets the current image for this frame.
		/// </summary>
		/// <returns>The image at the current image index.</returns>
		virtual Ref<Image> const& get_current_image() const = 0;

		/// <summary>
		/// Gets the images of this surface.
		/// </summary>
		/// <returns>A list of images used for this surface.</returns>
		virtual Vector<Ref<Image>> const& get_images() const = 0;

		/// <summary>
		/// Gets the AssetType of this Asset.
		/// </summary>
		/// <returns>Surface.</returns>
		constexpr AssetType get_asset_type() const override { return AssetType::Surface; }

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Recreates elements of the surface if needed, such as a resize after a window resize event.
		/// </summary>
		virtual void refresh() = 0;

#pragma endregion


#pragma region Statics

	public:
		Owner<Surface> create(SurfaceBuilder const& builder = {});

#pragma endregion

	};
}