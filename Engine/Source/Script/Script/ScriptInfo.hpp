#pragma once

#include "Resource/Script/ScriptType.hpp"
#include "Core/Data/Path.hpp"

namespace Minty
{
    struct ScriptInfo
    {
        ScriptType type;
        Path path;
    };
}