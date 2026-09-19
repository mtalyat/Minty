#pragma once

#include "Application/Application/ApplicationData.hpp"
#include "Scene/Manager/SceneManagerInfo.hpp"
#include "Resource/Manager/ResourceManagerInfo.hpp"
#include "Audio/Manager/AudioManagerInfo.hpp"
#include "Render/Manager/RenderManagerInfo.hpp"
#include "Input/Manager/InputManagerInfo.hpp"
#include "Script/Manager/ScriptManagerInfo.hpp"
#include "Core/Time/TimeControllerInfo.hpp"
#include "Window/Window/WindowInfo.hpp"

namespace Minty
{
    struct ApplicationInfo
    {
        ApplicationData data = {};

        WindowInfo windowInfo = {};

        SceneManagerInfo sceneManagerInfo = {};
        
        ResourceManagerInfo resourceManagerInfo = {};
        
        AudioManagerInfo audioManagerInfo = {};
        
        RenderManagerInfo renderManagerInfo = {};

        InputManagerInfo inputManagerInfo = {};

        ScriptManagerInfo scriptManagerInfo = {};

        TimeControllerInfo timeControllerInfo = {};
    };
}