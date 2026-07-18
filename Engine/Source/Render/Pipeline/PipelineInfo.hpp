#pragma once

/**
 * @file PipelineInfo.h
 * @brief Header file defining the PipelineInfo struct.
 * @author Mitchell Talyat
 */

#include "Resource/Pipeline/PipelinePrimitiveTopology.hpp"
#include "Resource/Pipeline/PipelinePolygonMode.hpp"
#include "Resource/Pipeline/PipelineCullMode.hpp"
#include "Resource/Pipeline/PipelineFrontFace.hpp"
#include "Resource/Pipeline/PipelineDepthStencilMode.hpp"
#include "Resource/Pipeline/PipelineBinding.hpp"
#include "Resource/Pipeline/PipelineInput.hpp"
#include "Resource/Type/Handle.hpp"
#include "Render/Type/Handle.hpp"
#include "Core/Data/Span.hpp"
#include "Core/Type/Conditional.hpp"

namespace Minty
{
    struct PipelineInfo
    {
        RenderPassHandle renderPass = INVALID_HANDLE;

        ShaderHandle vertexShader = INVALID_HANDLE;
        ShaderHandle fragmentShader = INVALID_HANDLE;

        ViewportHandle viewport = INVALID_HANDLE;

        PipelinePrimitiveTopology primitiveTopology = PipelinePrimitiveTopologyEnum::Default;
        PipelinePolygonMode polygonMode = PipelinePolygonModeEnum::Default;
        PipelineCullMode cullMode = PipelineCullModeEnum::Default;
        PipelineFrontFace frontFace = PipelineFrontFaceEnum::Default;
        Float lineWidth = 1.0f;
        Bool transparency = false;

        PipelineDepthStencilMode depthMode = PipelineDepthStencilModeEnum::Write;
        Conditional depthTestOperation = ConditionalEnum::LessThan;
        PipelineDepthStencilMode stencilMode = PipelineDepthStencilModeEnum::None;
        Conditional stencilTestOperation = ConditionalEnum::Equal;

        Span<PipelineBinding> attributes = {};
        Span<PipelineInput> inputs = {};
    };
}