#include "pch.h"
#include "Prefab.h"
#include "Minty/Entity/PrefabInfo.h"
#include "Minty/Serialization/Node.h"
#include "Minty/Stream/MemoryStream.h"

using namespace Minty;

Minty::Prefab::Prefab(PrefabInfo const &info)
    : Asset(info.id), m_data(info.source)
{
}

Unique<Reader> Minty::Prefab::open_reader() const
{
    Shared<Stream> const stream = Shared<MemoryStream>::create(m_data);
}

Shared<Prefab> Minty::Prefab::create(PrefabInfo const &info)
{
    return Shared<Prefab>::create(info);
}

Shared<Prefab> Minty::Prefab::create()
{
    PrefabInfo info{};
    return create(info);
}
