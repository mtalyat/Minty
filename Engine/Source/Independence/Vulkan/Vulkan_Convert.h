#pragma once

/**
 * @file Convert.h
 * @brief Header file defining the Converter specializations for Vulkan types.
 * @author Mitchell Talyat
 */

#include "Library/Vulkan/Vulkan.h"
#include "Core/Convert/Converter.h"
#include "Core/Type/Conditional.h"
#include "Render/Buffer/BufferUsage.h"
#include "Resource/Image/ImageAspect.h"
#include "Resource/Image/ImageFormat.h"
#include "Resource/Image/ImageLayout.h"
#include "Resource/Image/ImageTiling.h"
#include "Resource/Image/ImageType.h"
#include "Resource/Image/ImageUsage.h"
#include "Resource/Texture/TextureAddressMode.h"
#include "Resource/Texture/TextureFilter.h"
#include "Resource/Shader/ShaderStage.h"
#include "Resource/Pipeline/PipelineInputType.h"
#include "Resource/Pipeline/PipelinePrimitiveTopology.h"
#include "Resource/Pipeline/PipelinePolygonMode.h"
#include "Resource/Pipeline/PipelineCullMode.h"
#include "Resource/Pipeline/PipelineFrontFace.h"
#include "Resource/Pipeline/PipelineInputRate.h"
#include "Core/Meta/Type.h"
#include "Core/Type/LoadOperation.h"
#include "Core/Type/StoreOperation.h"

namespace Minty
{
    template<>
    struct Converter<BufferUsageFlags, VkBufferUsageFlags>
    {
        static BufferUsageFlags to_minty(VkBufferUsageFlags const& value);
        static VkBufferUsageFlags from_minty(BufferUsageFlags const& value);
    };

    template<>
    struct Converter<ImageAspectFlags, VkImageAspectFlags>
    {
        static ImageAspectFlags to_minty(VkImageAspectFlags const& value);
        static VkImageAspectFlags from_minty(ImageAspectFlags const& value);
    };

    template<>
    struct Converter<ImageFormat, VkFormat>
    {
        static ImageFormat to_minty(VkFormat const& value);
        static VkFormat from_minty(ImageFormat const& value);
    };

    template<>
    struct Converter<ImageLayout, VkImageLayout>
    {
        static ImageLayout to_minty(VkImageLayout const& value);
        static VkImageLayout from_minty(ImageLayout const& value);
    };

    template<>
    struct Converter<ImageType, VkImageType>
    {
        static ImageType to_minty(VkImageType const& value);
        static VkImageType from_minty(ImageType const& value);
    };

    template<>
    struct Converter<ImageTiling, VkImageTiling>
    {
        static ImageTiling to_minty(VkImageTiling const& value);
        static VkImageTiling from_minty(ImageTiling const& value);
    };

    template<>
    struct Converter<ImageUsageFlags, VkImageUsageFlags>
    {
        static ImageUsageFlags to_minty(VkImageUsageFlags const& value);
        static VkImageUsageFlags from_minty(ImageUsageFlags const& value);
    };

    template<>
    struct Converter<PipelineInputType, VkDescriptorType>
    {
        static PipelineInputType to_minty(VkDescriptorType const& value);
        static VkDescriptorType from_minty(PipelineInputType const& value);
    };

    template<>
    struct Converter<ShaderStage, VkShaderStageFlags>
    {
        static ShaderStage to_minty(VkShaderStageFlags const& value);
        static VkShaderStageFlags from_minty(ShaderStage const& value);
    };

    template<>
    struct Converter<TextureAddressMode, VkSamplerAddressMode>
    {
        static TextureAddressMode to_minty(VkSamplerAddressMode const& value);
        static VkSamplerAddressMode from_minty(TextureAddressMode const& value);
    };
    
    template<>
    struct Converter<TextureFilter, VkFilter>
    {
        static TextureFilter to_minty(VkFilter const& value);
        static VkFilter from_minty(TextureFilter const& value);
    };

    template<>
    struct Converter<PipelinePrimitiveTopology, VkPrimitiveTopology>
    {
        static PipelinePrimitiveTopology to_minty(VkPrimitiveTopology const& value);
        static VkPrimitiveTopology from_minty(PipelinePrimitiveTopology const& value);
    };

    template<>
    struct Converter<PipelinePolygonMode, VkPolygonMode>
    {
        static PipelinePolygonMode to_minty(VkPolygonMode const& value);
        static VkPolygonMode from_minty(PipelinePolygonMode const& value);
    };

    template<>
    struct Converter<PipelineCullMode, VkCullModeFlags>
    {
        static PipelineCullMode to_minty(VkCullModeFlags const& value);
        static VkCullModeFlags from_minty(PipelineCullMode const& value);
    };

    template<>
    struct Converter<PipelineFrontFace, VkFrontFace>
    {
        static PipelineFrontFace to_minty(VkFrontFace const& value);
        static VkFrontFace from_minty(PipelineFrontFace const& value);
    };

    template<>
    struct Converter<PipelineInputRate, VkVertexInputRate>
    {
        static PipelineInputRate to_minty(VkVertexInputRate const& value);
        static VkVertexInputRate from_minty(PipelineInputRate const& value);
    };

    template<>
    struct Converter<Conditional, VkCompareOp>
    {
        static Conditional to_minty(VkCompareOp const& value);
        static VkCompareOp from_minty(Conditional const& value);
    };

    template<>
    struct Converter<Type, VkFormat>
    {
        static Type to_minty(VkFormat const& value);
        static VkFormat from_minty(Type const& value);
    };

    template<>
    struct Converter<LoadOperation, VkAttachmentLoadOp>
    {
        static LoadOperation to_minty(VkAttachmentLoadOp const& value);
        static VkAttachmentLoadOp from_minty(LoadOperation const& value);
    };

    template<>
    struct Converter<StoreOperation, VkAttachmentStoreOp>
    {
        static StoreOperation to_minty(VkAttachmentStoreOp const& value);
        static VkAttachmentStoreOp from_minty(StoreOperation const& value);
    };
}