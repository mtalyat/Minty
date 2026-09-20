#pragma once

#include "Core/Data/Path.hpp"
#include "Library/Tui/Tui.hpp"

namespace Minty
{
    struct Script;
    struct ScriptLocalContext;
    struct ScriptGlobalContext;

    class Tui_ScriptManager
    {
#pragma region Method

    public:
        static Bool load_script(Path const& path, Script& script);
        static void set_local_context(Script& script, ScriptLocalContext const& context);
        static void set_global_context(ScriptGlobalContext const& context);

#pragma endregion
    };
}