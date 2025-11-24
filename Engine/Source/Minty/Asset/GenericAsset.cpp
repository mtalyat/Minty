#include "pch.h"
#include "GenericAsset.h"

using namespace Minty;

String Minty::GenericAsset::get_text() const
{
	Vector<Char> text;
	text.resize(m_data.get_size() + 1, '\0');
	memcpy(text.get_data(), m_data.get_data(), m_data.get_size());
	return String(text.get_data());
}

Owner<GenericAsset> Minty::GenericAsset::create(GenericAssetBuilder const& builder)
{
    return Owner<GenericAsset>(builder);
}
