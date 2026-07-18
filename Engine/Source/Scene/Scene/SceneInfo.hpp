#pragma once

#include "World/Entity/EntityManagerInfo.hpp"
#include "World/System/SystemManagerInfo.hpp"
#include "Core/Type/Priority.hpp"

namespace Minty
{
    struct SceneInfo
    {
        EntityManagerInfo entityManagerInfo = {};

        SystemManagerInfo systemManagerInfo = {};

        // The priority of the Scene when active
        Priority priority = PriorityEnum::Default;
    };
}