#include "pch.h"
#include "Sprite.h"

using namespace Minty;

Minty::Sprite::Sprite(SpriteBuilder const& builder)
	: Asset(builder.id)
	, m_texture(builder.texture)
	, m_coordinateMode(builder.coordinateMode)
	, m_offset()
	, m_size()
	, m_pivot()
	, m_pixelsPerUnit()
	, m_scale()
{
	MINTY_ASSERT(m_texture != nullptr, "Sprite must have a Texture.");

	set_offset(builder.offset);
	set_size(builder.size);
	set_pivot(builder.pivot);

	set_pixels_per_unit(builder.pixelsPerUnit);
}

Float2 Minty::Sprite::get_coords(Float2 const raw) const
{
	// translate from normalized to CoordinateMode
	switch (m_coordinateMode)
	{
	case CoordinateMode::Normalized:
		return raw;
	case CoordinateMode::Pixel:
	{
		UInt2 textureSize = m_texture->get_size();
		return Float2(
			raw.x * static_cast<Float>(textureSize.x),
			raw.y * static_cast<Float>(textureSize.y));
	}
	default:
		MINTY_ABORT("Failed to get Sprite value. Unhandled CoordinateMode.");
	}
}

Float2 Minty::Sprite::set_coords(Float2 const raw) const
{
	// translate from CoordinateMode to normalized
	switch (m_coordinateMode)
	{
	case CoordinateMode::Normalized:
		return raw;
	case CoordinateMode::Pixel:
	{
		UInt2 textureSize = m_texture->get_size();
		return Float2(
			raw.x / static_cast<Float>(textureSize.x),
			raw.y / static_cast<Float>(textureSize.y));
	}
		default:
			MINTY_ABORT("Failed to set Sprite value. Unhandled CoordinateMode.");
	}
}

void Minty::Sprite::update_scale()
{
	// get the width of the texture
	Float width = static_cast<Float>(m_texture->get_size().x);

	// update the scale
	m_scale = (m_size.x * width) / m_pixelsPerUnit;
}

Float2 Minty::Sprite::get_offset() const
{
	return get_coords(m_offset);
}

void Minty::Sprite::set_offset(Float2 const& offset)
{
	m_offset = set_coords(offset);
}

Float2 Minty::Sprite::get_size() const
{
	return get_coords(m_size);
}

void Minty::Sprite::set_size(Float2 const& size)
{
	m_size = set_coords(size);
}

Float2 Minty::Sprite::get_pivot() const
{
	return get_coords(m_pivot);
}

void Minty::Sprite::set_pivot(Float2 const& pivot)
{
	m_pivot = set_coords(pivot);
}

void Minty::Sprite::set_pixels_per_unit(Float ppu)
{
	MINTY_ASSERT(ppu > 0.0f, "Pixels per unit must be greater than 0.");

	m_pixelsPerUnit = ppu;

	update_scale();
}

Owner<Sprite> Minty::Sprite::create(SpriteBuilder const& builder)
{
	return Owner<Sprite>(builder);
}
