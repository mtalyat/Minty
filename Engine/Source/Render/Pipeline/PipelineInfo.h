#pragma once

/**
 * @file PipelineInfo.h
 * @brief Header file defining the PipelineInfo struct.
 * @author Mitchell Talyat
 */

#include "Resource/Pipeline/PipelinePrimitiveTopology.h"
#include "Resource/Pipeline/PipelinePolygonMode.h"
#include "Resource/Pipeline/PipelineCullMode.h"
#include "Resource/Pipeline/PipelineFrontFace.h"
#include "Resource/Pipeline/PipelineDepthStencilMode.h"
#include "Resource/Pipeline/PipelineBinding.h"
#include "Resource/Pipeline/PipelineInput.h"
#include "Resource/Type/Handle.h"
#include "Render/Type/Handle.h"
#include "Core/Data/Span.h"
#include "Core/Type/Conditional.h"

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