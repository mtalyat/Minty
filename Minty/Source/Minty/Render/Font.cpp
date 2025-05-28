#include "pch.h"
#include "Font.h"
#include "Minty/Core/Format.h"
#include "Minty/Render/FontVariant.h"

using namespace Minty;

void Minty::Font::add(Ref<FontVariant> const& variant)
{
	MINTY_ASSERT(variant != nullptr, "Cannot add null FontVariant to Font.");
	ID key = create_font_id(variant->get_size(), variant->get_flags());
	MINTY_ASSERT(!m_variants.contains(key), F("FontVariant with size {} and flags {} already exists in Font \"{}\".", variant->get_size(), to_string(variant->get_flags()), m_name));
	m_variants.add(key, variant);
}

Ref<FontVariant> const& Minty::Font::at(UInt const size, FontFlags const flags) const
{
	ID key = create_font_id(size, flags);
	MINTY_ASSERT(m_variants.contains(key), F("FontVariant with size {} and flags {} not found in Font \"{}\".", size, to_string(flags), m_name));
	return m_variants.at(key);
}

Ref<FontVariant> Minty::Font::get(UInt const size, FontFlags const flags) const
{
	ID key = create_font_id(size, flags);
	auto found = m_variants.find(key);
	if (found == m_variants.end())
	{
		return nullptr; // no variant found
	}
	return found->get_second();
}

Vector<Ref<FontVariant>> Minty::Font::get_variants() const
{
	Vector<Ref<FontVariant>> variants(m_variants.get_size());
	for (auto const& pair : m_variants)
	{
		variants.add(pair.get_second());
	}
	return variants;
}

Owner<Font> Minty::Font::create(FontBuilder const& builder)
{
	return Owner<Font>(builder);
}
