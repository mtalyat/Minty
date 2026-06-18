#include "pch.h"
#include "FontVariantResource.h"
#include "FontVariantInfo.h"
#include "Resource/Image/ImageFormat.h"
#include "Core/Debug/DebugF.h"

using namespace Minty;

Minty::FontVariantResource::FontVariantResource(FontVariantInfo const &info)
	: m_size(info.size),
	  m_flags(info.flags),
	  m_lineHeight(info.lineHeight),
	  m_texture(info.texture),
	  m_characters(),
	  m_kernings(info.kernings.get_size() * 2)
{
	// initiale the characters map
	m_characters.reserve(info.characters.get_size());
	for (FontChar const &character : info.characters)
	{
		m_characters.add(character.id, character);
	}

	// initialize the kernings map
	for (auto const &[left, right, value] : info.kernings)
	{
		Int kerningId = compact_kerning(left, right);
		MINTY_ASSERT_B(!m_kernings.contains(kerningId), ErrorCodeEnum::Argument_DuplicateValue, left, right);
		m_kernings.add(kerningId, value);
	}
}

FontChar const *Minty::FontVariantResource::get_char(Char const ch) const
{
	auto found = m_characters.find(ch);
	if (found == m_characters.end())
	{
		return nullptr;
	}
	return &found->get_second();
}

Float Minty::FontVariantResource::get_kerning(Char const left, Char const right) const
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
