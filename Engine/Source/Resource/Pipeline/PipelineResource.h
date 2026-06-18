#pragma once

/**
 * @file PipelineResource.h
 * @brief PipelineResource struct definition.
 * @author Mitchell Talyat
 */

#include "PipelinePrimitiveTopology.h"
#include "PipelinePolygonMode.h"
#include "PipelineCullMode.h"
#include "PipelineFrontFace.h"
#include "PipelineDepthStencilMode.h"
#include "PipelineBinding.h"
#include "PipelineInput.h"
#include "Core/Serialize/Serializer.h"
#include "Resource/Type/Handle.h"
#include "Core/Type/Conditional.h"

namespace Minty
{
    struct PipelineResource
    {
        RenderPassResourceHandle renderPass = INVALID_HANDLE;
        ShaderResourceHandle vertexShader = INVALID_HANDLE;
        ShaderResourceHandle fragmentShader = INVALID_HANDLE;

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

        Vector<PipelineBinding> attributes = {}; // vertex input attributes
        Vector<PipelineInput> inputs = {}; // push constants, uniform constants, and specialization constants
    };

    template<>
    struct Serializer<PipelineResource>
    {
        static Bool serialize(Writer &writer, PipelineResource const &value);
        static Bool deserialize(Reader &reader, PipelineResource &value);
    };
}