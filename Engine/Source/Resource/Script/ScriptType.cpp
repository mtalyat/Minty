#include "pch.hpp"
#include "ScriptType.hpp"
#include "Core/Constant/File.hpp"

using namespace Minty;

ScriptType ScriptType::from_extension(StringView const extension)
{
    if (extension == EXTENSION_SCRIPT_TUI)
    {
        return ScriptTypeEnum::Tui;
    }
    if (extension == EXTENSION_SCRIPT_SOURCE)
    {
        return ScriptTypeEnum::Source;
    }
    return ScriptTypeEnum::Undefined;
}