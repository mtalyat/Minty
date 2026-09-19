#pragma once

#include "Core/Data/Path.hpp"
#include "Core/Serialize/Serializer.hpp"
#include "Resource/Script/ScriptType.hpp"

namespace Minty
{
    struct ScriptResource
    {
        // type of the script
        ScriptTypeEnum type;
        // path to the script file
        Path path;
    };

    template<>
    struct Serializer<ScriptResource>
    {
        static Bool serialize(Writer &writer, ScriptResource const &value);
        static Bool deserialize(Reader &reader, ScriptResource &value);
    };
}