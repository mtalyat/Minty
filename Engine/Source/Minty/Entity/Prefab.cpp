#include "pch.h"
#include "Prefab.h"

using namespace Minty;

Owner<Prefab> Minty::Prefab::create(PrefabInfo const& info)
{
    return Owner<Prefab>(info);
}
