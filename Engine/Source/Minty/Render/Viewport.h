#ifndef MINTY_RENDER_VIEWPORT_H
#define MINTY_RENDER_VIEWPORT_H

/**
 * @file Viewport.h
 * @brief Header file defining the Viewport class and ViewportInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Asset/Asset.h"
#include "Minty/Core/Math.h"
#include "Minty/Data/Pointer.h"

namespace Minty
{
	struct ViewportInfo;

	/**
	 * @brief Represents a view with a mask that can be used to render to a specific area of the screen.
	 */
	class Viewport
		: public Asset
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates a new Viewport.
		 * @param info The arguments.
		 */
		Viewport(ViewportInfo const& info);

		virtual ~Viewport() override = default;

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Sets the view position and mask position.
		 * @param position The new value.
		 */
		virtual void set_position(Int2 const& position) = 0;

		/**
		 * @brief Sets the view size and mask size.
		 * @param size The new value.
		 */
		virtual void set_size(UInt2 const& size) = 0;

		/**
		 * @brief Gets the view position.
		 * @return The value.
		 */
		virtual Int2 get_view_position() const = 0;

		/**
		 * @brief Sets the view position.
		 * @param position The new value.
		 */
		virtual void set_view_position(Int2 const& position) = 0;

		/**
		 * @brief Gets the view size.
		 * @return The value.
		 */
		virtual UInt2 get_view_size() const = 0;

		/**
		 * @brief Sets the view size.
		 * @param size The new value.
		 */
		virtual void set_view_size(UInt2 const& size) = 0;

		/**
		 * @brief Gets the mask position.
		 * @return The value.
		 */
		virtual Int2 get_mask_position() const = 0;

		/**
		 * @brief Sets the mask position.
		 * @param position The new value.
		 */
		virtual void set_mask_position(Int2 const& position) = 0;

		/**
		 * @brief Gets the mask size.
		 * @return The value.
		 */
		virtual UInt2 get_mask_size() const = 0;

		/**
		 * @brief Sets the mask size.
		 * @param size The new value.
		 */
		virtual void set_mask_size(UInt2 const& size) = 0;

		/**
		 * @brief Gets the AssetType of this Asset.
		 * @return Viewport.
		 */
		inline AssetType get_asset_type() const override { return AssetType::Viewport; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Called when this Viewport is binded for rendering.
		 */
		virtual void on_bind() = 0;

		/**
		 * @brief Creates a new Viewport.
		 * @param info The arguments.
		 * @return A Viewport Owner.
		 */
		static Shared<Viewport> create(ViewportInfo const& info);

		/**
		 * @brief Creates a default Viewport.
		 * @return A Viewport Owner.
		 */
		static Shared<Viewport> create();

#pragma endregion
	};
}

#endif // MINTY_RENDER_VIEWPORT_H