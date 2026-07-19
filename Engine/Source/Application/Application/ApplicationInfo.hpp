#pragma once

#include "Scene/Manager/SceneManagerInfo.hpp"
#include "Window/Manager/WindowManagerInfo.hpp"
#include "Resource/Manager/ResourceManagerInfo.hpp"
#include "Audio/Manager/AudioManagerInfo.hpp"
#include "Render/Manager/RenderManagerInfo.hpp"
#include "Input/Manager/InputManagerInfo.hpp"
#include "Core/Time/TimeControllerInfo.hpp"

namespace Minty
{
    struct ApplicationInfo
    {
        SceneManagerInfo sceneManagerInfo = {};

        WindowManagerInfo windowManagerInfo = {};
        
        ResourceManagerInfo resourceManagerInfo = {};
        
        AudioManagerInfo audioManagerInfo = {};
        
        RenderManagerInfo renderManagerInfo = {};

        InputManagerInfo inputManagerInfo = {};

        TimeControllerInfo timeControllerInfo = {};
    };
}