#include "pch.h"
#include "Prefab.h"

using namespace Minty;

Owner<Prefab> Minty::Prefab::create(PrefabBuilder const& builder)
{
    return Owner<Prefab>(builder);
}
