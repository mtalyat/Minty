#pragma once

#include "World/Entity/EntityManagerInfo.hpp"
#include "World/System/SystemManagerInfo.hpp"

namespace Minty
{
    struct SceneInfo
    {
        EntityManagerInfo entityManagerInfo = {};

        SystemManagerInfo systemManagerInfo = {};
    };
}