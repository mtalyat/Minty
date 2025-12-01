#ifndef MINTY_RENDER_SURFACE_H
#define MINTY_RENDER_SURFACE_H

/**
 * @file Surface.h
 * @brief Header file defining the Surface class.
 * @author Mitchell Talyat
 */

#include "Minty/Asset/Asset.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Render/Format.h"

namespace Minty
{
	class Window;
	class Image;
	struct SurfaceInfo;

	/**
	 * @brief Represents a surface, which is a platform-specific representation of a window screen that can be rendered to.
	 */
	class Surface
		: public Asset
	{
#pragma region Constructors

	public:
		Surface(SurfaceInfo const& info);

		virtual ~Surface() override = default;

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the size of this surface.
		 * @return The size of this surface in pixels.
		 */
		virtual UInt2 get_size() const = 0;

		/**
		 * @brief Gets the Format of this surface.
		 * @return The Format this surface uses.
		 */
		virtual Format get_format() const = 0;

		/**
		 * @brief Gets the current image index for this frame.
		 * @return The index of the current image being used.
		 */
		virtual UInt get_current_image_index() const = 0;

		/**
		 * @brief Gets the current image for this frame.
		 * @return The image at the current image index.
		 */
		virtual Ref<Image> const& get_current_image() const = 0;

		/**
		 * @brief Gets the images of this surface.
		 * @return A list of images used for this surface.
		 */
		virtual Vector<Ref<Image>> const& get_images() const = 0;

		/**
		 * @brief Gets the AssetType of this Asset.
		 * @return Surface.
		 */
		inline AssetType get_asset_type() const override { return AssetType::Surface; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Recreates elements of the surface if needed, such as a resize after a window resize event.
		 */
		virtual void refresh() = 0;

		/**
		 * @brief Creates a new Surface.
		 * @param info The arguments.
		 * @return A Surface Owner.
		 */
		Shared<Surface> create(SurfaceInfo const& info);

#pragma endregion
	};
}

#endif // MINTY_RENDER_SURFACE_H