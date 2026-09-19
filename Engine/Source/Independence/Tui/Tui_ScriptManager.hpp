#pragma once

#include "Core/Data/Path.hpp"
#include "Library/Tui/Tui.hpp"

namespace Minty
{
    struct Script;

    class Tui_ScriptManager
    {
#pragma region Method

    public:
        static Bool load_script(Path const& path, Script& script);

#pragma endregion
    };
}