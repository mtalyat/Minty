#pragma once

#include "World/Entity/EntityManagerInfo.hpp"
#include "World/System/SystemManagerInfo.hpp"
#include "Core/Data/String.hpp"

namespace Minty
{
    struct SceneInfo
    {
        EntityManagerInfo entityManagerInfo = {};

        SystemManagerInfo systemManagerInfo = {};

        // The priority of the Scene when active
        Int priority = 0;

        String name = {};
    };
}