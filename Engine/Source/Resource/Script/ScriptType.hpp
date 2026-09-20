#pragma once

#include "Core/Data/StringView.hpp"

namespace Minty
{
    enum class ScriptTypeEnum
    {
        Undefined,
        Source, // C++
        Tui,
    };

    struct ScriptType
    {
        ScriptTypeEnum value;

        ScriptType() : value(ScriptTypeEnum::Undefined) {}
        ScriptType(ScriptTypeEnum value) : value(value) {}
        operator ScriptTypeEnum() const { return value; }

        Bool is_valid() const { return value != ScriptTypeEnum::Undefined; }
        Bool operator==(ScriptType const &other) const { return value == other.value; }
        Bool operator!=(ScriptType const &other) const { return value != other.value; }

        static ScriptType from_extension(StringView const extension);
    };
}