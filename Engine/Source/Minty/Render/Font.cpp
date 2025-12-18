#include "pch.h"
#include "Font.h"
#include "Minty/Core/Format.h"
#include "Minty/Render/FontInfo.h"
#include "Minty/Render/FontVariant.h"

using namespace Minty;

Minty::Font::Font(FontInfo const& info)
	: Asset(info.id)
	, m_name(info.name)
	, m_variants()
{
	// add variants
	for (auto const& variant : info.variants)
	{
		MINTY_ASSERT(variant != nullptr, ErrorCode::Argument_ExpectedNonNull);
		ID key = create_font_id(variant->get_size(), variant->get_flags());
		MINTY_ASSERT_F(!m_variants.contains(key), ErrorCode::Argument_KeyAlreadyExists, variant->get_size(), variant->get_flags());
		m_variants.add(key, variant);
	}
}

Shared<FontVariant> const& Minty::Font::at(UInt const size, FontFlags const flags) const
{
	ID key = create_font_id(size, flags);
	MINTY_ASSERT_F(m_variants.contains(key), ErrorCode::Argument_KeyNotFound, size, flags);
	return m_variants.at(key);
}

Shared<FontVariant> Minty::Font::get(UInt const size, FontFlags const flags) const
{
	ID key = create_font_id(size, flags);
	auto found = m_variants.find(key);
	if (found == m_variants.end())
	{
		return nullptr; // no variant found
	}
	return found->get_second();
}

Vector<Shared<FontVariant>> Minty::Font::get_variants() const
{
	Vector<Shared<FontVariant>> variants(m_variants.get_size());
	for (auto const& pair : m_variants)
	{
		variants.add(pair.get_second());
	}
	return variants;
}

Shared<Font> Minty::Font::create(FontInfo const& info)
{
	return Shared<Font>::create(info);
}

Shared<Font> Minty::Font::create()
{
	FontInfo info{};
	return create(info);
}
