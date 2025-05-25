#pragma once
#include "Minty/Asset/Asset.h"
#include "Minty/Core/Math.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/Rect.h"
#include "Minty/Render/CoordinateMode.h"
#include "Minty/Render/Texture.h"

namespace Minty
{
	/// <summary>
	/// The arguments for a Sprite.
	/// </summary>
	struct SpriteBuilder
	{
		/// <summary>
		/// The Asset ID.
		/// </summary>
		UUID id = INVALID_ID;

		/// <summary>
		/// The Texture that this Sprite uses.
		/// </summary>
		Ref<Texture> texture = nullptr;

		/// <summary>
		/// How the coordinates are interpreted.
		/// </summary>
		CoordinateMode coordinateMode = CoordinateMode::Normalized;

		/// <summary>
		/// The offset of this Sprite within the Texture.
		/// </summary>
		Float2 offset = { 0.0f, 0.0f };

		/// <summary>
		/// The size of this Sprite within the Texture.
		/// </summary>
		Float2 size = { 1.0f, 1.0f };

		/// <summary>
		/// The pivot of this Sprite within world space.
		/// </summary>
		Float2 pivot = { 0.5f, 0.5f };

		/// <summary>
		/// The number of pixels that fit within 1 unit of world space.
		/// </summary>
		Float pixelsPerUnit = 16.0f;
	};

	/// <summary>
	/// A Sprite is a 2D image that is part of a Texture.
	/// </summary>
	class Sprite
		: public Asset
	{
#pragma region Variables

	private:
		Ref<Texture> m_texture;
		CoordinateMode m_coordinateMode;
		// store offset, size, pivot as normalized, since that is what the shaders use
		Float2 m_offset;
		Float2 m_size;
		Float2 m_pivot;
		Float m_pixelsPerUnit;
		// scale within world space so it matches the PPU
		Float m_scale;

#pragma endregion

#pragma region Constructors

	public:
		Sprite(SpriteBuilder const& builder);

		~Sprite()
		{
		}

#pragma endregion

#pragma region Get Set

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
		/// Sets the CoordinateMode of this Sprite.
		/// </summary>
		/// <param name="mode">The CoordinateMode.</param>
		void set_coordinate_mode(CoordinateMode mode) { m_coordinateMode = mode; }

		Float2 get_offset() const;

		void set_offset(Float2 const& offset);

		Float2 get_size() const;

		void set_size(Float2 const& size);

		Float2 get_pivot() const;

		void set_pivot(Float2 const& pivot);

		Float get_pixels_per_unit() const { return m_pixelsPerUnit; }

		void set_pixels_per_unit(Float ppu);

		Float get_scale() const { return m_scale; }

		/// <summary>
		/// Gets the rectangle of this Sprite.
		/// </summary>
		/// <returns>The offset and size packed into a Rect.</returns>
		inline Rect get_rect() const
		{
			return Rect(m_offset.x, m_offset.y, m_size.x, m_size.y);
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
		/// <param name="builder">The arguments.</param>
		/// <returns>A Sprite Owner.</returns>
		static Owner<Sprite> create(SpriteBuilder const& builder = {});

#pragma endregion
	};
}