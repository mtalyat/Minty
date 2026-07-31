#include "pch.hpp"
#include "PipelineResource.hpp"
#include "Core/Debug/Debug.hpp"
#include "Resource/Manager/ResourceManager.hpp"
#include "Core/Serialize/ParsedTypes.hpp"

using namespace Minty;

Bool Minty::Serializer<PipelineResource>::serialize(Writer &writer, PipelineResource const &value)
{
    MINTY_NOT_IMPLEMENTED();
    return Bool();
}

Bool Minty::Serializer<PipelineResource>::deserialize(Reader &reader, PipelineResource &value)
{
    ResourceManager &resourceManager = ResourceManager::get_instance();

    // Data to load
    RenderPassResourceHandle renderPassHandle = value.renderPass;
    ShaderResourceHandle vertexShader = value.vertexShader;
    ShaderResourceHandle fragmentShader = value.fragmentShader;

    PipelinePrimitiveTopology primitiveTopology = value.primitiveTopology;
    PipelinePolygonMode polygonMode = value.polygonMode;
    PipelineCullMode cullMode = value.cullMode;
    PipelineFrontFace frontFace = value.frontFace;
    Float lineWidth = value.lineWidth;
    Bool transparency = value.transparency;

    PipelineDepthStencilMode depthMode = value.depthMode;
    Conditional depthTestOperation = value.depthTestOperation;
    PipelineDepthStencilMode stencilMode = value.stencilMode;
    Conditional stencilTestOperation = value.stencilTestOperation;

    Vector<PipelineBinding> attributes = value.attributes;
    Vector<PipelineInput> inputs = value.inputs;

    // Read render pass
    if (!resourceManager.read<RenderPassResource>(reader, "RenderPass", renderPassHandle))
    {
        MINTY_ERROR(ErrorCodeEnum::Serialization_MissingKey);
        return false;
    }

    // Read the data
    reader.read("PrimitiveTopology", primitiveTopology);
    reader.read("PolygonMode", polygonMode);
    reader.read("CullMode", cullMode);
    reader.read("FrontFace", frontFace);
    reader.read("LineWidth", lineWidth);
    reader.read("Transparency", transparency);
    reader.read("DepthMode", depthMode);
    reader.read("DepthTestOperation", depthTestOperation);
    reader.read("StencilMode", stencilMode);
    reader.read("StencilTestOperation", stencilTestOperation);

    // Read shaders
    if (reader.indent("Stages"))
    {
        if (!resourceManager.read<ShaderResource>(reader, "Vertex", vertexShader))
        {
            MINTY_ERROR(ErrorCodeEnum::Serialization_MissingKey);
            return false;
        }

        if (!resourceManager.read<ShaderResource>(reader, "Fragment", fragmentShader))
        {
            MINTY_ERROR(ErrorCodeEnum::Serialization_MissingKey);
            return false;
        }

        reader.outdent();
    }

    // Read vertex inputs (bindings)
    if (reader.indent("Attributes"))
    {
        String name;                 // key str
        UInt binding = UINT_MAX;     // key
        PipelineInputRate inputRate; // value
        UInt location;
        Type type;
        while (reader.indent_next(name, inputRate))
        {
            PipelineBinding pipelineBinding{};

            // read the binding
            if (!Parser<UInt>::parse(name.get_data(), binding))
            {
                // if the first binding, this += will make it wrap around to 0
                // otherwise, go to the next binding
                binding += 1;
            }
            pipelineBinding.binding = binding;

            // set the input rate
            pipelineBinding.inputRate = inputRate;

            // read attributes
            // read each attribute
            location = UINT_MAX;
            while (reader.read_next(name, type))
            {
                PipelineAttribute pipelineAttribute{};

                // get attribute location
                if (!Parser<UInt>::parse(name.get_data(), location))
                {
                    // set location to last location + 1
                    location += 1;
                }
                pipelineAttribute.location = location;

                // get attribute type
                pipelineAttribute.type = type;

                // add to the binding
                pipelineBinding.attributes.add(std::move(pipelineAttribute));
            }

            // add to the info
            attributes.add(std::move(pipelineBinding));

            reader.outdent();
        }

        reader.outdent();
    }

    // inputs (uniform, push, etc.)
    if (reader.indent("Inputs"))
    {
        // offset for push constants
        Size offset = 0;
        String name;
        Type type;

        while (reader.indent_next(name))
        {
            // get the input and set the name
            PipelineInput input{};
            input.name = std::move(name);

            // get basic data
            reader.read("Type", input.type);
            reader.read("Stage", input.stage);
            reader.read("Set", input.set);
            reader.read("Binding", input.binding);
            reader.read("Count", input.count);
            reader.read("Frequent", input.frequent);

            // set offset if push constant
            if (input.type == PipelineInputTypeEnum::PushConstant)
            {
                MINTY_ASSERT_A(input.stage == ShaderStageEnum::Vertex, ErrorCodeEnum::Resource_Shader_PushConstantLocation, input.name.get_data());
                input.offset = offset;
            }

            // read object data for this input, if it has any
            if (!reader.read("Object", input.object))
            {
                MINTY_ERROR(ErrorCodeEnum::Serialization_MissingKey);
                return false;
            }

            // set size to the size of the Object
            input.size = input.object.get_size();

            // adjust offset if push constant, so next push const is aligned
            if (input.type == PipelineInputTypeEnum::PushConstant)
            {
                offset += input.size;
            }

            inputs.add(std::move(input));

            reader.outdent();
        }

        reader.outdent();
    }

    // Set the data
    value.renderPass = renderPassHandle;
    value.vertexShader = vertexShader;
    value.fragmentShader = fragmentShader;
    // TODO: viewport
    value.primitiveTopology = primitiveTopology;
    value.polygonMode = polygonMode;
    value.cullMode = cullMode;
    value.frontFace = frontFace;
    value.lineWidth = lineWidth;
    value.transparency = transparency;
    value.depthMode = depthMode;
    value.depthTestOperation = depthTestOperation;
    value.stencilMode = stencilMode;
    value.stencilTestOperation = stencilTestOperation;
    value.attributes = std::move(attributes);
    value.inputs = std::move(inputs);
    return true;
}
