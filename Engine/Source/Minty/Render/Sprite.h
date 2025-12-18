#ifndef MINTY_RENDER_SPRITE_H
#define MINTY_RENDER_SPRITE_H

/**
 * @file Sprite.h
 * @brief Header file defining the Sprite class and SpriteInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Asset/Asset.h"
#include "Minty/Core/Math.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Rect.h"
#include "Minty/Render/SpriteSlice.h"
#include "Minty/Render/Texture.h"

namespace Minty
{
	class MaterialTemplate;
	struct SpriteInfo;

	/**
	 * @brief A Sprite is a 2D image that is part of a Texture.
	 */
	class Sprite
		: public Asset
	{
#pragma region Constructors

	public:
		Sprite(SpriteInfo const& info);

		~Sprite() = default;

#pragma endregion

#pragma region Accessors

	private:
		// converts coords from normalized to CoordinateMode coords
		Float2 get_coords(Float2 const raw) const;
		// converts coords from CoordinateMode coords to normalized
		Float2 set_coords(Float2 const raw) const;
		// updates the scale based on the PPU
		void update_scale();

	public:
		/**
		 * @brief Gets the Texture used by this Sprite.
		 * @return The Texture.
		 */
		inline Shared<Texture> const& get_texture() const { return m_texture; }

		/**
		 * @brief Gets the CoordinateMode of this Sprite.
		 * @return The CoordinateMode.
		 */
		inline CoordinateMode get_coordinate_mode() const { return m_coordinateMode; }

        /**
         * @brief Gets the offset of the Sprite within the Texture.
         * @return The offset as a Float2.
         */
        Float2 get_offset() const;

        /**
         * @brief Sets the offset of the Sprite within the Texture.
         * @param offset The new offset as a Float2.
         */
        void set_offset(Float2 const& offset);

        /**
         * @brief Gets the size of the Sprite within the Texture.
         * @return The size as a Float2.
         */
        Float2 get_size() const;

        /**
         * @brief Sets the size of the Sprite within the Texture.
         * @param size The new size as a Float2.
         */
        void set_size(Float2 const& size);

        /**
         * @brief Gets the pivot point of the Sprite in world space.
         * @return The pivot as a Float2.
         */
        Float2 get_pivot() const;

        /**
         * @brief Sets the pivot point of the Sprite in world space.
         * @param pivot The new pivot as a Float2.
         */
        void set_pivot(Float2 const& pivot);

        /**
         * @brief Gets the number of pixels that fit within one unit of world space for this Sprite.
         * @return The pixels per unit as a Float.
         */
        inline Float get_pixels_per_unit() const { return m_pixelsPerUnit; }

        /**
         * @brief Gets the scale of the Sprite in world space so it matches the pixels per unit.
         * @return The scale as a Float.
         */
		inline Float2 get_render_scale() const { return m_scale; }

		/**
		 * @brief Returns the current render offset.
		 * @return The current render offset as a Float2 value.
		 */
		inline Float2 get_render_offset() const { return m_offset; }

		/**
		 * @brief Returns the current render size.
		 * @return A Float2 representing the current render size.
		 */
		inline Float2 get_render_size() const { return m_size; }

		/**
		 * @brief Gets the rendering rectangle of this Sprite.
		 * @return The offset and size packed into a Rect.
		 */
		inline Rect get_render_rect() const { return Rect(m_offset.x, m_offset.y, m_size.x, m_size.y); }

		/**
		 * @brief Returns the current render pivot point.
		 * @return The render pivot as a Float2 value.
		 */
		inline Float2 get_render_pivot() const { return m_pivot; }

		/**
		 * @brief Gets the AssetType of this Asset.
		 * @return Sprite.
		 */
		inline AssetType get_asset_type() const override { return AssetType::Sprite; }

		/**
		 * @brief Creates a Sprite with the given arguments.
		 * @param info The arguments.
		 * @return A Sprite Owner.
		 */
		static Shared<Sprite> create(SpriteInfo const& info);

		/**
		 * @brief Creates a default Sprite.
		 * @return A Sprite Owner.
		 */	
		static Shared<Sprite> create();

#pragma endregion

#pragma region Variables

	private:
		Shared<Texture> m_texture; // the texture this Sprite uses
		// the slice data of the Sprite
		CoordinateMode m_coordinateMode;
		Float2 m_offset; // the offset of the Sprite within the Texture
		Float2 m_size; // the size of the Sprite within the Texture
		Float2 m_pivot; // the pivot of the Sprite within world space
		Float m_pixelsPerUnit; // the number of pixels that fit within 1 unit of world space
		Float2 m_scale; // scale within world space so it matches the PPU

#pragma endregion
	};
}

#endif // MINTY_RENDER_SPRITE_H