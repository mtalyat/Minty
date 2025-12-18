#include "pch.h"
#include "GenericAsset.h"
#include "Minty/Asset/GenericAssetInfo.h"
#include "Minty/Data/Vector.h"

using namespace Minty;

Minty::GenericAsset::GenericAsset(GenericAssetInfo const &info)
	: Asset(info.id)
	, m_data(info.data)
{
}

String Minty::GenericAsset::get_text() const
{
	Vector<Char> text;
	text.resize(m_data.get_size() + 1, '\0');
	memcpy(text.get_data(), m_data.get_data(), m_data.get_size());
	return String(text.get_data());
}

Shared<GenericAsset> Minty::GenericAsset::create(GenericAssetInfo const& info)
{
    return Shared<GenericAsset>::create(info);
}

Shared<GenericAsset> Minty::GenericAsset::create()
{
	GenericAssetInfo info{};
	return create(info);
}
