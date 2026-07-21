#pragma once

/**
 * @file ShaderModuleInfo.hpp
 * @brief Header file defining the ShaderModuleInfo struct.
 * @author Mitchell Talyat
 */

#include "Resource/Constant/Resource.hpp"
#include "Core/Data/View.hpp"
#include "Core/Data/StringView.hpp"
#include "Resource/Shader/ShaderStage.hpp"

namespace Minty
{
    /**
     * @brief The arguments for a ShaderModule.
     */
    struct ShaderInfo
    {
        /**
         * @brief The raw byte data of the shader module. This should be in SPIR-V format for Vulkan.
         */
        View data = {};

        /**
         * @brief The stage of the shader (vertex, fragment, etc.). This is used to determine how to use the shader module in the pipeline.
         */
        ShaderStage stage = ShaderStageEnum::Undefined;

        /**
         * @brief The entry point of the shader. This is the name of the function that serves as the entry point for the shader. It defaults to "main" if not specified.
         */
        StringView entryPoint = DEFAULT_ENTRY_POINT;
    };
}
