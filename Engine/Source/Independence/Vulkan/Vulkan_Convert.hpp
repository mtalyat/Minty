#pragma once

/**
 * @file Convert.h
 * @brief Header file defining the Converter specializations for Vulkan types.
 * @author Mitchell Talyat
 */

#include "Library/Vulkan/Vulkan.hpp"
#include "Core/Convert/Converter.hpp"
#include "Core/Type/Conditional.hpp"
#include "Render/Buffer/BufferUsage.hpp"
#include "Render/Geometry/GeometryIndexType.hpp"
#include "Resource/Image/ImageAspect.hpp"
#include "Resource/Image/ImageFormat.hpp"
#include "Resource/Image/ImageLayout.hpp"
#include "Resource/Image/ImageTiling.hpp"
#include "Resource/Image/ImageType.hpp"
#include "Resource/Image/ImageUsage.hpp"
#include "Resource/Texture/TextureAddressMode.hpp"
#include "Resource/Texture/TextureFilter.hpp"
#include "Resource/Shader/ShaderStage.hpp"
#include "Resource/Pipeline/PipelineInputType.hpp"
#include "Resource/Pipeline/PipelinePrimitiveTopology.hpp"
#include "Resource/Pipeline/PipelinePolygonMode.hpp"
#include "Resource/Pipeline/PipelineCullMode.hpp"
#include "Resource/Pipeline/PipelineFrontFace.hpp"
#include "Resource/Pipeline/PipelineInputRate.hpp"
#include "Core/Meta/Type.hpp"
#include "Core/Type/LoadOperation.hpp"
#include "Core/Type/StoreOperation.hpp"

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

    template<>
    struct Converter<GeometryIndexType, VkIndexType>
    {
        static GeometryIndexType to_minty(VkIndexType const& value);
        static VkIndexType from_minty(GeometryIndexType const& value);
    };
}