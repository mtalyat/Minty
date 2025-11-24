#include "pch.h"
#include "Sprite.h"
#include "Minty/Core/Format.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Render/Texture.h"

using namespace Minty;

Minty::Sprite::Sprite(SpriteInfo const& info)
	: Asset(info.id)
	, m_texture(info.texture)
	, m_coordinateMode(info.slice.coordinateMode)
	, m_offset()
	, m_size()
	, m_pivot()
	, m_pixelsPerUnit(info.slice.pixelsPerUnit)
	, m_scale(1.0f, 1.0f)
{
	MINTY_ASSERT(info.texture != nullptr, "Sprite must have a Texture.");
	MINTY_ASSERT(info.slice.pixelsPerUnit > 0.0f, "Sprite pixels per unit must be greater than 0.");

	set_offset(info.slice.offset);
	set_size(info.slice.size);
	set_pivot(info.slice.pivot);
	update_scale();
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
	UInt2 const textureSize = m_texture->get_size();
	Float const width = static_cast<Float>(textureSize.x);
	Float const height = static_cast<Float>(textureSize.y);

	// update the scale
	m_scale.x = (m_size.x * width) / m_pixelsPerUnit;
	m_scale.y = (m_size.y * height) / m_pixelsPerUnit;
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
	// translate from CoordinateMode to normalized
	switch (m_coordinateMode)
	{
	case CoordinateMode::Normalized:
		m_pivot = pivot;
		break;
	case CoordinateMode::Pixel:
	{
		UInt2 textureSize = m_texture->get_size();
		m_pivot = Float2(
			pivot.x / (static_cast<Float>(textureSize.x) * m_size.x),
			pivot.y / (static_cast<Float>(textureSize.y) * m_size.y));
		break;
	}
	default:
		MINTY_ABORT("Failed to set Sprite value. Unhandled CoordinateMode.");
	}
}

Owner<Sprite> Minty::Sprite::create(SpriteInfo const& info)
{
	return Owner<Sprite>(info);
}
