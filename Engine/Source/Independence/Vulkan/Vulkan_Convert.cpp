#include "Vulkan_Convert.h"
#include "Core/Debug/Debug.h"

using namespace Minty;

BufferUsageFlags Minty::Converter<BufferUsageFlags, VkBufferUsageFlags>::to_minty(VkBufferUsageFlags const &value)
{
	MINTY_NOT_IMPLEMENTED();
    return BufferUsageFlags();
}

VkBufferUsageFlags Minty::Converter<BufferUsageFlags, VkBufferUsageFlags>::from_minty(BufferUsageFlags const &value)
{
	VkBufferUsageFlags flags = 0;
	if(value.has_flag(BufferUsageFlagsEnum::TransferSrc))
	{
		flags |= VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
	}
	if(value.has_flag(BufferUsageFlagsEnum::TransferDst))
	{
		flags |= VK_BUFFER_USAGE_TRANSFER_DST_BIT;
	}
	if(value.has_flag(BufferUsageFlagsEnum::Vertex))
	{
		flags |= VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
	}
	if(value.has_flag(BufferUsageFlagsEnum::Index))
	{
		flags |= VK_BUFFER_USAGE_INDEX_BUFFER_BIT;
	}
	if(value.has_flag(BufferUsageFlagsEnum::Uniform))
	{
		flags |= VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
	}
	
	MINTY_ASSERT(flags != 0, ErrorCodeEnum::ConversionFailed);
	return flags;
}

ImageAspectFlags Minty::Converter<ImageAspectFlags, VkImageAspectFlags>::to_minty(VkImageAspectFlags const &value)
{
	MINTY_NOT_IMPLEMENTED();
    return ImageAspectFlags();
}

VkImageAspectFlags Minty::Converter<ImageAspectFlags, VkImageAspectFlags>::from_minty(ImageAspectFlags const &value)
{
	VkImageAspectFlags flags = 0;
	if(value.has_flag(ImageAspectFlagsEnum::Color))
	{
		flags |= VK_IMAGE_ASPECT_COLOR_BIT;
	}
	if (value.has_flag(ImageAspectFlagsEnum::Depth))
	{
		flags |= VK_IMAGE_ASPECT_DEPTH_BIT;
	}

	MINTY_ASSERT(flags != 0, ErrorCodeEnum::ConversionFailed);
	return flags;
}

ImageFormat Minty::Converter<ImageFormat, VkFormat>::to_minty(VkFormat const &value)
{
	// for now, 1:1
	// TODO: make safer
    return static_cast<ImageFormatEnum>(value);
}

VkFormat Minty::Converter<ImageFormat, VkFormat>::from_minty(ImageFormat const &value)
{
    // for now, 1:1
	// TODO: make safer
	return static_cast<VkFormat>(value.value);
}

ImageLayout Minty::Converter<ImageLayout, VkImageLayout>::to_minty(VkImageLayout const &value)
{
	MINTY_NOT_IMPLEMENTED();
    return ImageLayout();
}

VkImageLayout Minty::Converter<ImageLayout, VkImageLayout>::from_minty(ImageLayout const &value)
{
	switch (value.value)
	{
	case ImageLayoutEnum::Undefined:
		return VK_IMAGE_LAYOUT_UNDEFINED;
	case ImageLayoutEnum::General:
		return VK_IMAGE_LAYOUT_GENERAL;
	case ImageLayoutEnum::ColorAttachment:
		return VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
	case ImageLayoutEnum::DepthStencilAttachment:
		return VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
	case ImageLayoutEnum::DepthStencilReadOnly:
		return VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL;
	case ImageLayoutEnum::ShaderReadOnly:
		return VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	case ImageLayoutEnum::TransferSource:
		return VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
	case ImageLayoutEnum::TransferDestination:
		return VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
	case ImageLayoutEnum::Preinitialized:
		return VK_IMAGE_LAYOUT_PREINITIALIZED;
	case ImageLayoutEnum::Presentation:
		return VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;
	default:
		MINTY_ABORT(ErrorCodeEnum::ConversionFailed);
		break;
	}

	return VK_IMAGE_LAYOUT_MAX_ENUM;
}

ImageType Minty::Converter<ImageType, VkImageType>::to_minty(VkImageType const &value)
{
	MINTY_NOT_IMPLEMENTED();
    return ImageType();
}

VkImageType Minty::Converter<ImageType, VkImageType>::from_minty(ImageType const &value)
{
	switch (value.value)
	{
	case Minty::ImageTypeEnum::D1:
		return VK_IMAGE_TYPE_1D;
	case Minty::ImageTypeEnum::D2:
		return VK_IMAGE_TYPE_2D;
	case Minty::ImageTypeEnum::D3:
		return VK_IMAGE_TYPE_3D;
	default:
		MINTY_ABORT(ErrorCodeEnum::ConversionFailed);
		break;
	}

	return VK_IMAGE_TYPE_MAX_ENUM;
}

inline ImageTiling Minty::Converter<ImageTiling, VkImageTiling>::to_minty(VkImageTiling const &value)
{
	MINTY_NOT_IMPLEMENTED();
    return ImageTiling();
}

VkImageTiling Minty::Converter<ImageTiling, VkImageTiling>::from_minty(ImageTiling const &value)
{
    switch (value.value)
	{
	case ImageTilingEnum::Optimal:
		return VK_IMAGE_TILING_OPTIMAL;
	case ImageTilingEnum::Linear:
		return VK_IMAGE_TILING_LINEAR;
	default:
		MINTY_ABORT(ErrorCodeEnum::ConversionFailed);
		break;
	};

	return VK_IMAGE_TILING_MAX_ENUM;
}

ImageUsageFlags Minty::Converter<ImageUsageFlags, VkImageUsageFlags>::to_minty(VkImageUsageFlags const &value)
{
	MINTY_NOT_IMPLEMENTED();
    return ImageUsageFlags();
}

VkImageUsageFlags Minty::Converter<ImageUsageFlags, VkImageUsageFlags>::from_minty(ImageUsageFlags const &value)
{
	VkImageUsageFlags flags = 0;

	if(value.has_flag(ImageUsageFlagsEnum::Sampled))
	{
		flags |= VK_IMAGE_USAGE_SAMPLED_BIT;
	}
	if(value.has_flag(ImageUsageFlagsEnum::Storage))
	{
		flags |= VK_IMAGE_USAGE_STORAGE_BIT;
	}
	if(value.has_flag(ImageUsageFlagsEnum::Color))
	{
		flags |= VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	}
	if(value.has_flag(ImageUsageFlagsEnum::DepthStencil))
	{
		flags |= VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT;
	}
	if(value.has_flag(ImageUsageFlagsEnum::TransferSrc))
	{
		flags |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
	}
	if(value.has_flag(ImageUsageFlagsEnum::TransferDst))
	{
		flags |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;
	}
	MINTY_ASSERT(flags != 0, ErrorCodeEnum::ConversionFailed);
	return flags;
}

PipelineInputType Minty::Converter<PipelineInputType, VkDescriptorType>::to_minty(VkDescriptorType const &value)
{
	MINTY_NOT_IMPLEMENTED();
    return PipelineInputType();
}

VkDescriptorType Minty::Converter<PipelineInputType, VkDescriptorType>::from_minty(PipelineInputType const &value)
{
	switch (value.value)
	{
	case PipelineInputTypeEnum::Sample:
		return VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
	case PipelineInputTypeEnum::CombinedImageSampler:
		return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	case PipelineInputTypeEnum::SampledImage:
		return VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
	case PipelineInputTypeEnum::StorageImage:
		return VK_DESCRIPTOR_TYPE_STORAGE_IMAGE;
	case PipelineInputTypeEnum::UniformTexelBuffer:
		return VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER;
	case PipelineInputTypeEnum::StorageTexelBuffer:
		return VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER;
	case PipelineInputTypeEnum::UniformBuffer:
		return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	case PipelineInputTypeEnum::StorageBuffer:
		return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER;
	case PipelineInputTypeEnum::UniformBufferDynamic:
		return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC;
	case PipelineInputTypeEnum::StorageBufferDynamic:
		return VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC;
	case PipelineInputTypeEnum::PushConstant:
		return VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
	}

	MINTY_ABORT(ErrorCodeEnum::ConversionFailed);
	return VK_DESCRIPTOR_TYPE_MAX_ENUM;
}

ShaderStage Minty::Converter<ShaderStage, VkShaderStageFlags>::to_minty(VkShaderStageFlags const &value)
{
	MINTY_NOT_IMPLEMENTED();
    return ShaderStage();
}

VkShaderStageFlags Minty::Converter<ShaderStage, VkShaderStageFlags>::from_minty(ShaderStage const &value)
{
	switch (value.value)
	{
	case ShaderStageEnum::Vertex:
		return VK_SHADER_STAGE_VERTEX_BIT;
	case ShaderStageEnum::Fragment:
		return VK_SHADER_STAGE_FRAGMENT_BIT;
	}

	MINTY_ABORT(ErrorCodeEnum::ConversionFailed);
	return VK_SHADER_STAGE_FLAG_BITS_MAX_ENUM;
}

TextureAddressMode Minty::Converter<TextureAddressMode, VkSamplerAddressMode>::to_minty(VkSamplerAddressMode const &value)
{
    MINTY_NOT_IMPLEMENTED();
    return TextureAddressMode();
}

VkSamplerAddressMode Minty::Converter<TextureAddressMode, VkSamplerAddressMode>::from_minty(TextureAddressMode const &value)
{
    switch (value.value)
	{
	case TextureAddressModeEnum::Repeat:
		return VK_SAMPLER_ADDRESS_MODE_REPEAT;
	case TextureAddressModeEnum::MirroredRepeat:
		return VK_SAMPLER_ADDRESS_MODE_MIRRORED_REPEAT;
	case TextureAddressModeEnum::ClampToEdge:
		return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_EDGE;
	case TextureAddressModeEnum::ClampToBorder:
		return VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
	case TextureAddressModeEnum::MirroredClampToEdge:
		return VK_SAMPLER_ADDRESS_MODE_MIRROR_CLAMP_TO_EDGE;
	default:
		MINTY_ABORT(ErrorCodeEnum::ConversionFailed);
		break;
	};

	return VK_SAMPLER_ADDRESS_MODE_MAX_ENUM;
}

TextureFilter Minty::Converter<TextureFilter, VkFilter>::to_minty(VkFilter const &value)
{
    MINTY_NOT_IMPLEMENTED();
    return TextureFilter();
}

VkFilter Minty::Converter<TextureFilter, VkFilter>::from_minty(TextureFilter const &value)
{
    switch (value.value)
	{
	case TextureFilterEnum::Nearest:
		return VK_FILTER_NEAREST;
	case TextureFilterEnum::Linear:
		return VK_FILTER_LINEAR;
	default:
		MINTY_ABORT(ErrorCodeEnum::ConversionFailed);
		break;
	}

	return VK_FILTER_MAX_ENUM;
}

PipelinePrimitiveTopology Minty::Converter<PipelinePrimitiveTopology, VkPrimitiveTopology>::to_minty(VkPrimitiveTopology const &value)
{
	MINTY_NOT_IMPLEMENTED();
    return PipelinePrimitiveTopology();
}

VkPrimitiveTopology Minty::Converter<PipelinePrimitiveTopology, VkPrimitiveTopology>::from_minty(PipelinePrimitiveTopology const &value)
{
	switch (value.value)
	{
	case PipelinePrimitiveTopologyEnum::PointList:
		return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
	case PipelinePrimitiveTopologyEnum::LineList:
		return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
	case PipelinePrimitiveTopologyEnum::LineStrip:
		return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
	case PipelinePrimitiveTopologyEnum::TriangleList:
		return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
	case PipelinePrimitiveTopologyEnum::TriangleStrip:
		return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
	case PipelinePrimitiveTopologyEnum::TriangleFan:
		return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN;
	}

	MINTY_ABORT(ErrorCodeEnum::ConversionFailed);
	return VK_PRIMITIVE_TOPOLOGY_MAX_ENUM;
}

PipelinePolygonMode Minty::Converter<PipelinePolygonMode, VkPolygonMode>::to_minty(VkPolygonMode const &value)
{
	MINTY_NOT_IMPLEMENTED();
    return PipelinePolygonMode();
}

VkPolygonMode Minty::Converter<PipelinePolygonMode, VkPolygonMode>::from_minty(PipelinePolygonMode const &value)
{
	switch (value.value)
	{
	case PipelinePolygonModeEnum::Fill:
		return VK_POLYGON_MODE_FILL;
	case PipelinePolygonModeEnum::Line:
		return VK_POLYGON_MODE_LINE;
	case PipelinePolygonModeEnum::Point:
		return VK_POLYGON_MODE_POINT;
	}

	MINTY_ABORT(ErrorCodeEnum::ConversionFailed);
	return VK_POLYGON_MODE_MAX_ENUM;
}

PipelineCullMode Minty::Converter<PipelineCullMode, VkCullModeFlags>::to_minty(VkCullModeFlags const &value)
{
	MINTY_NOT_IMPLEMENTED();
    return PipelineCullMode();
}

VkCullModeFlags Minty::Converter<PipelineCullMode, VkCullModeFlags>::from_minty(PipelineCullMode const &value)
{
	switch (value.value)
	{
	case PipelineCullModeEnum::None:
		return VK_CULL_MODE_NONE;
	case PipelineCullModeEnum::Front:
		return VK_CULL_MODE_FRONT_BIT;
	case PipelineCullModeEnum::Back:
		return VK_CULL_MODE_BACK_BIT;
	case PipelineCullModeEnum::Both:
		return VK_CULL_MODE_FRONT_AND_BACK;
	}

	MINTY_ABORT(ErrorCodeEnum::ConversionFailed);
	return VK_CULL_MODE_FLAG_BITS_MAX_ENUM;
}

PipelineFrontFace Minty::Converter<PipelineFrontFace, VkFrontFace>::to_minty(VkFrontFace const &value)
{
	MINTY_NOT_IMPLEMENTED();
    return PipelineFrontFace();
}

VkFrontFace Minty::Converter<PipelineFrontFace, VkFrontFace>::from_minty(PipelineFrontFace const &value)
{
	switch (value.value)
	{
	case PipelineFrontFaceEnum::CounterClockwise:
		return VK_FRONT_FACE_COUNTER_CLOCKWISE;
	case PipelineFrontFaceEnum::Clockwise:
		return VK_FRONT_FACE_CLOCKWISE;
	}

	MINTY_ABORT(ErrorCodeEnum::ConversionFailed);
	return VK_FRONT_FACE_MAX_ENUM;
}

PipelineInputRate Minty::Converter<PipelineInputRate, VkVertexInputRate>::to_minty(VkVertexInputRate const &value)
{
	MINTY_NOT_IMPLEMENTED();
    return PipelineInputRate();
}

VkVertexInputRate Minty::Converter<PipelineInputRate, VkVertexInputRate>::from_minty(PipelineInputRate const &value)
{
	switch (value.value)
	{
		case PipelineInputRateEnum::Vertex:
			return VK_VERTEX_INPUT_RATE_VERTEX;
		case PipelineInputRateEnum::Instance:
			return VK_VERTEX_INPUT_RATE_INSTANCE;
	}

	MINTY_ABORT(ErrorCodeEnum::ConversionFailed);
	return VK_VERTEX_INPUT_RATE_MAX_ENUM;
}

Conditional Minty::Converter<Conditional, VkCompareOp>::to_minty(VkCompareOp const &value)
{
	MINTY_NOT_IMPLEMENTED();
    return Conditional();
}

VkCompareOp Minty::Converter<Conditional, VkCompareOp>::from_minty(Conditional const &value)
{
	switch (value.type)
	{
	case ConditionalEnum::Equal:
		return VK_COMPARE_OP_EQUAL;
	case ConditionalEnum::NotEqual:
		return VK_COMPARE_OP_NOT_EQUAL;
	case ConditionalEnum::GreaterThan:
		return VK_COMPARE_OP_GREATER;
	case ConditionalEnum::GreaterThanOrEqual:
		return VK_COMPARE_OP_GREATER_OR_EQUAL;
	case ConditionalEnum::LessThan:
		return VK_COMPARE_OP_LESS;
	case ConditionalEnum::LessThanOrEqual:
		return VK_COMPARE_OP_LESS_OR_EQUAL;
	}

	MINTY_ABORT(ErrorCodeEnum::ConversionFailed);
	return VK_COMPARE_OP_MAX_ENUM;
}

Type Minty::Converter<Type, VkFormat>::to_minty(VkFormat const &value)
{
	MINTY_NOT_IMPLEMENTED();
	return Type();
}

VkFormat Minty::Converter<Type, VkFormat>::from_minty(Type const &value)
{
	switch (value.value)
	{
	case TypeEnum::Float:
		return VkFormat::VK_FORMAT_R32_SFLOAT;
	case TypeEnum::Float2:
		return VkFormat::VK_FORMAT_R32G32_SFLOAT;
	case TypeEnum::Float3:
		return VkFormat::VK_FORMAT_R32G32B32_SFLOAT;
	case TypeEnum::Float4:
		return VkFormat::VK_FORMAT_R32G32B32A32_SFLOAT;
	case TypeEnum::Int:
		return VkFormat::VK_FORMAT_R32_SINT;
	case TypeEnum::Int2:
		return VkFormat::VK_FORMAT_R32G32_SINT;
	case TypeEnum::Int3:
		return VkFormat::VK_FORMAT_R32G32B32_SINT;
	case TypeEnum::Int4:
		return VkFormat::VK_FORMAT_R32G32B32A32_SINT;
	case TypeEnum::UInt:
		return VkFormat::VK_FORMAT_R32_UINT;
	case TypeEnum::UInt2:
		return VkFormat::VK_FORMAT_R32G32_UINT;
	case TypeEnum::UInt3:
		return VkFormat::VK_FORMAT_R32G32B32_UINT;
	case TypeEnum::UInt4:
		return VkFormat::VK_FORMAT_R32G32B32A32_UINT;
	}

	MINTY_ABORT(ErrorCodeEnum::ConversionFailed);
	return VK_FORMAT_UNDEFINED;
}

LoadOperation Minty::Converter<LoadOperation, VkAttachmentLoadOp>::to_minty(VkAttachmentLoadOp const &value)
{
	MINTY_NOT_IMPLEMENTED();
    return LoadOperation();
}

VkAttachmentLoadOp Minty::Converter<LoadOperation, VkAttachmentLoadOp>::from_minty(LoadOperation const &value)
{
	switch (value.value)
	{
	case LoadOperationEnum::DontCare:
		return VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	case LoadOperationEnum::Load:
		return VK_ATTACHMENT_LOAD_OP_LOAD;
	case LoadOperationEnum::Clear:
		return VK_ATTACHMENT_LOAD_OP_CLEAR;
	}

		MINTY_ABORT(ErrorCodeEnum::ConversionFailed);
	return VK_ATTACHMENT_LOAD_OP_MAX_ENUM;
}

StoreOperation Minty::Converter<StoreOperation, VkAttachmentStoreOp>::to_minty(VkAttachmentStoreOp const &value)
{
	MINTY_NOT_IMPLEMENTED();
    return StoreOperation();
}

VkAttachmentStoreOp Minty::Converter<StoreOperation, VkAttachmentStoreOp>::from_minty(StoreOperation const &value)
{
	switch (value.value)
	{
	case StoreOperationEnum::DontCare:
		return VK_ATTACHMENT_STORE_OP_DONT_CARE;
	case StoreOperationEnum::Store:
		return VK_ATTACHMENT_STORE_OP_STORE;
	}

	MINTY_ABORT(ErrorCodeEnum::ConversionFailed);
	return VK_ATTACHMENT_STORE_OP_MAX_ENUM;
}

GeometryIndexType Minty::Converter<GeometryIndexType, VkIndexType>::to_minty(VkIndexType const &value)
{
    MINTY_NOT_IMPLEMENTED();
	return GeometryIndexType();
}

VkIndexType Minty::Converter<GeometryIndexType, VkIndexType>::from_minty(GeometryIndexType const &value)
{
	switch (value.value)
	{
	case GeometryIndexTypeEnum::UInt16:
		return VK_INDEX_TYPE_UINT16;
	case GeometryIndexTypeEnum::UInt32:
		return VK_INDEX_TYPE_UINT32;
	}

	MINTY_ABORT(ErrorCodeEnum::ConversionFailed);
	return VK_INDEX_TYPE_MAX_ENUM;
}
