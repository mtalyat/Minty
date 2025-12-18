#include "pch.h"
#include "FontVariant.h"
#include "Minty/Core/Format.h"
#include "Minty/Render/Material.h"
#include "Minty/Render/RenderManager.h"
#include "Minty/Render/Texture.h"
#include "Minty/Render/FontVariantInfo.h"

using namespace Minty;

Minty::FontVariant::FontVariant(FontVariantInfo const& info)
	: Asset(info.id)
	, m_size(info.size)
	, m_flags(info.flags)
	, m_lineHeight(info.lineHeight)
	, m_texture(info.texture)
	, m_material(nullptr)
	, m_characters()
	, m_kernings(info.kernings.get_size() * 2)
{
	// get the material based on the texture
	RenderManager& renderManager = RenderManager::get_singleton();
	m_material = renderManager.get_default_material(m_texture, nullptr, AssetType::FontVariant, Space::UI).to_ref();

	// initiale the characters map
	m_characters.reserve(info.characters.get_size());
	for (FontChar const& character : info.characters)
	{
		m_characters.add(character.id, character);
	}

	// initialize the kernings map
	for (auto const& [left, right, value] : info.kernings)
	{
		Int kerningId = compact_kerning(left, right);
		MINTY_ASSERT_F(!m_kernings.contains(kerningId), ErrorCode::Argument_DuplicateValue, left, right);
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

Shared<FontVariant> Minty::FontVariant::create(FontVariantInfo const& info)
{
	return Shared<FontVariant>::create(info);
}

Shared<FontVariant> Minty::FontVariant::create()
{
	FontVariantInfo info{};
	return create(info);
}
