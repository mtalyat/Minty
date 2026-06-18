#include "pch.h"
#include "FontResource.h"
#include "FontInfo.h"
#include "Core/Debug/DebugF.h"
#include "Resource/Manager/ResourceManager.h"
#include "Resource/FontVariant/FontVariantResource.h"

using namespace Minty;

Minty::FontResource::FontResource(FontInfo const &info)
	: m_name(info.name),
	  m_variants()
{
	// add variants
	ResourceManager& resourceManager = ResourceManager::get_instance();
	for (auto const &variant : info.variants)
	{
		MINTY_ASSERT(variant != INVALID_HANDLE, ErrorCodeEnum::Argument_ExpectedNonNull);

		FontVariantResource const& fontVariant = resourceManager.at(variant);

		ID key = create_font_id(fontVariant.get_size(), fontVariant.get_flags());
		MINTY_ASSERT_B(!m_variants.contains(key), ErrorCodeEnum::Argument_KeyAlreadyExists, fontVariant.get_size(), Parser<FontFlags>::to_string(fontVariant.get_flags()).get_data());
		m_variants.add(key, variant);
	}
}

FontVariantResourceHandle Minty::FontResource::at(UInt const size, FontFlags const flags) const
{
	ID key = create_font_id(size, flags);
	MINTY_ASSERT_B(m_variants.contains(key), ErrorCodeEnum::Argument_KeyNotFound, size, Parser<FontFlags>::to_string(flags).get_data());
	return m_variants.at(key);
}

FontVariantResourceHandle Minty::FontResource::get(UInt const size, FontFlags const flags) const
{
	ID key = create_font_id(size, flags);
	auto found = m_variants.find(key);
	if (found == m_variants.end())
	{
		return INVALID_HANDLE; // not found
	}
	return found->get_second();
}

Vector<FontVariantResourceHandle> Minty::FontResource::get_variants() const
{
	Vector<FontVariantResourceHandle> variants(m_variants.get_size());
	for (auto const &pair : m_variants)
	{
		variants.add(pair.get_second());
	}
	return variants;
}
