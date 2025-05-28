#include "pch.h"
#include "FontVariant.h"
#include "Minty/Core/Format.h"
#include "Minty/Render/Material.h"
#include "Minty/Render/RenderManager.h"
#include "Minty/Render/Texture.h"

using namespace Minty;

Minty::FontVariant::FontVariant(FontVariantBuilder const& builder)
	: Asset(builder.id)
	, m_size(builder.size)
	, m_flags(builder.flags)
	, m_lineHeight(builder.lineHeight)
	, m_texture(builder.texture)
	, m_material(nullptr)
	, m_characters()
	, m_kernings(builder.kernings.get_size() * 2)
{
	// get the material based on the texture
	RenderManager& renderManager = RenderManager::get_singleton();
	m_material = renderManager.get_default_material(m_texture, AssetType::FontVariant, Space::UI);

	// initiale the characters map
	m_characters.reserve(builder.characters.get_size());
	for (FontChar const& character : builder.characters)
	{
		m_characters.add(character.id, character);
	}

	// initialize the kernings map
	for (auto const& [left, right, value] : builder.kernings)
	{
		Int kerningId = compact_kerning(left, right);
		MINTY_ASSERT(!m_kernings.contains(kerningId), F("Duplicate kerning for characters '{}' and '{}'.", left, right));
		m_kernings.add(kerningId, value);
	}
}

FontChar const* Minty::FontVariant::get_char(Char const ch) const
{
	auto found = m_characters.find(ch);
	if (found == m_characters.end())
	{
		return nullptr;
	}
	return &found->get_second();
}

Float Minty::FontVariant::get_kerning(Char const left, Char const right) const
{
	// get the kerning id
	Int kerningId = compact_kerning(left, right);
	auto found = m_kernings.find(kerningId);
	if (found == m_kernings.end())
	{
		return 0.0f; // no kerning found
	}
	// kerning found
	return found->get_second();
}

Owner<FontVariant> Minty::FontVariant::create(FontVariantBuilder const& builder)
{
	return Owner<FontVariant>(builder);
}
