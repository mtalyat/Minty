#pragma once

/**
 * @file PipelineResource.h
 * @brief PipelineResource struct definition.
 * @author Mitchell Talyat
 */

#include "PipelinePrimitiveTopology.hpp"
#include "PipelinePolygonMode.hpp"
#include "PipelineCullMode.hpp"
#include "PipelineFrontFace.hpp"
#include "PipelineDepthStencilMode.hpp"
#include "PipelineBinding.hpp"
#include "PipelineInput.hpp"
#include "Core/Serialize/Serializer.hpp"
#include "Resource/Type/Handle.hpp"
#include "Core/Type/Conditional.hpp"

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