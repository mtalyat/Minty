#pragma once

#include "Application/Application/ApplicationData.hpp"
#include "Scene/Manager/SceneManagerInfo.hpp"
#include "Resource/Manager/ResourceManagerInfo.hpp"
#include "Audio/Manager/AudioManagerInfo.hpp"
#include "Render/Manager/RenderManagerInfo.hpp"
#include "Input/Manager/InputManagerInfo.hpp"
#include "Core/Time/TimeControllerInfo.hpp"

namespace Minty
{
    struct ApplicationInfo
    {
        ApplicationData data = {};

        SceneManagerInfo sceneManagerInfo = {};
        
        ResourceManagerInfo resourceManagerInfo = {};
        
        AudioManagerInfo audioManagerInfo = {};
        
        RenderManagerInfo renderManagerInfo = {};

        InputManagerInfo inputManagerInfo = {};

        TimeControllerInfo timeControllerInfo = {};
    };
}