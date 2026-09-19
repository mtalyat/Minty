#pragma once

#include "Core/Data/StringView.hpp"

namespace Minty
{
    constexpr StringView SCRIPT_FUNC_LOAD = "OnLoad";
    constexpr StringView SCRIPT_FUNC_UNLOAD = "OnUnload";
    constexpr StringView SCRIPT_FUNC_ENABLE = "OnEnable";
    constexpr StringView SCRIPT_FUNC_DISABLE = "OnDisable";
    constexpr StringView SCRIPT_FUNC_FRAME_UPDATE = "OnFrameUpdate";
    constexpr StringView SCRIPT_FUNC_FIXED_UPDATE = "OnFixedUpdate";
    constexpr StringView SCRIPT_FUNC_FINALIZE = "OnFinalize";
    constexpr StringView SCRIPT_FUNC_RENDER = "OnRender";
    constexpr StringView SCRIPT_FUNC_EVENT = "OnEvent";
}