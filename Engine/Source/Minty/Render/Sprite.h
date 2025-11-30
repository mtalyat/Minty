#pragma once
#include "Minty/Asset/Asset.h"
#include "Minty/Core/Math.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Rect.h"
#include "Minty/Render/SpriteSlice.h"

namespace Minty
{
	class Texture;
	class MaterialTemplate;

	/// <summary>
	/// The arguments for a Sprite.
	/// </summary>
	struct SpriteInfo
	{
		/// <summary>
		/// The Asset ID.
		/// </summary>
		UUID id = UUID();

		/// <summary>
		/// The Texture that this Sprite uses.
		/// </summary>
		Ref<Texture> texture = nullptr;

		/// <summary>
		/// The slice of the Texture this Sprite uses.
		/// </summary>
		SpriteSlice slice = {};
	};

	/// <summary>
	/// A Sprite is a 2D image that is part of a Texture.
	/// </summary>
	class Sprite
		: public Asset
	{
#pragma region Variables

	private:
		Ref<Texture> m_texture; // the texture this Sprite uses
		// the slice data of the Sprite
		CoordinateMode m_coordinateMode;
		Float2 m_offset; // the offset of the Sprite within the Texture
		Float2 m_size; // the size of the Sprite within the Texture
		Float2 m_pivot; // the pivot of the Sprite within world space
		Float m_pixelsPerUnit; // the number of pixels that fit within 1 unit of world space
		Float2 m_scale; // scale within world space so it matches the PPU

#pragma endregion

#pragma region Constructors

	public:
		Sprite(SpriteInfo const& info);

		~Sprite()
		{
		}

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
		/// <summary>
		/// Gets the Texture used by this Sprite.
		/// </summary>
		/// <returns>The Texture.</returns>
		Ref<Texture> const& get_texture() const { return m_texture; }

		/// <summary>
		/// Gets the CoordinateMode of this Sprite.
		/// </summary>
		/// <returns>The CoordinateMode.</returns>
		CoordinateMode get_coordinate_mode() const { return m_coordinateMode; }

        /// <summary>
        /// Gets the offset of the Sprite within the Texture.
        /// </summary>
        /// <returns>The offset as a Float2.</returns>
        Float2 get_offset() const;

        /// <summary>
        /// Sets the offset of the Sprite within the Texture.
        /// </summary>
        /// <param name="offset">The new offset as a Float2.</param>
        void set_offset(Float2 const& offset);

        /// <summary>
        /// Gets the size of the Sprite within the Texture.
        /// </summary>
        /// <returns>The size as a Float2.</returns>
        Float2 get_size() const;

        /// <summary>
        /// Sets the size of the Sprite within the Texture.
        /// </summary>
        /// <param name="size">The new size as a Float2.</param>
        void set_size(Float2 const& size);

        /// <summary>
        /// Gets the pivot point of the Sprite in world space.
        /// </summary>
        /// <returns>The pivot as a Float2.</returns>
        Float2 get_pivot() const;

        /// <summary>
        /// Sets the pivot point of the Sprite in world space.
        /// </summary>
        /// <param name="pivot">The new pivot as a Float2.</param>
        void set_pivot(Float2 const& pivot);

        /// <summary>
        /// Gets the number of pixels that fit within one unit of world space for this Sprite.
        /// </summary>
        /// <returns>The pixels per unit as a Float.</returns>
        Float get_pixels_per_unit() const { return m_pixelsPerUnit; }

        /// <summary>
        /// Gets the scale of the Sprite in world space so it matches the pixels per unit.
        /// </summary>
        /// <returns>The scale as a Float.</returns>
		Float2 get_render_scale() const { return m_scale; }

		/// <summary>
		/// Returns the current render offset.
		/// </summary>
		/// <returns>The current render offset as a Float2 value.</returns>
		inline Float2 get_render_offset() const
		{
			return m_offset;
		}

		/// <summary>
		/// Returns the current render size.
		/// </summary>
		/// <returns>A Float2 representing the current render size.</returns>
		inline Float2 get_render_size() const
		{
			return m_size;
		}

		/// <summary>
		/// Gets the rendering rectangle of this Sprite.
		/// </summary>
		/// <returns>The offset and size packed into a Rect.</returns>
		inline Rect get_render_rect() const
		{
			return Rect(m_offset.x, m_offset.y, m_size.x, m_size.y);
		}

		/// <summary>
		/// Returns the current render pivot point.
		/// </summary>
		/// <returns>The render pivot as a Float2 value.</returns>
		inline Float2 get_render_pivot() const
		{
			return m_pivot;
		}

		/// <summary>
		/// Gets the AssetType of this Asset.
		/// </summary>
		/// <returns>Sprite.</returns>
		AssetType get_asset_type() const override { return AssetType::Sprite; }

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Creates a Sprite with the given arguments.
		/// </summary>
		/// <param name="info">The arguments.</param>
		/// <returns>A Sprite Owner.</returns>
		static Shared<Sprite> create(SpriteInfo const& info = {});

#pragma endregion
	};
}