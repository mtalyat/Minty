#include "pch.h"
#include "ShaderInputType.h"

using namespace Minty;

String Minty::to_string(ShaderInputType const obj)
{
	switch (obj)
	{
	case ShaderInputType::Sample: return "Sample";
	case ShaderInputType::CombinedImageSampler: return "CombinedImageSampler";
	case ShaderInputType::SampledImage: return "SampledImage";
	case ShaderInputType::StorageImage: return "StorageImage";
	case ShaderInputType::UniformTexelBuffer: return "UniformTexelBuffer";
	case ShaderInputType::StorageTexelBuffer: return "StorageTexelBuffer";
	case ShaderInputType::UniformBuffer: return "UniformBuffer";
	case ShaderInputType::StorageBuffer: return "StorageBuffer";
	case ShaderInputType::UniformBufferDynamic: return "UniformBufferDynamic";
	case ShaderInputType::StorageBufferDynamic: return "StorageBufferDynamic";
	case ShaderInputType::PushConstant: return "PushConstant";

	default: return "";
	}
}

ShaderInputType Minty::parse_to_shader_input_type(String const& string)
{
	if (string == "Sample") return ShaderInputType::Sample;
	if (string == "CombinedImageSampler") return ShaderInputType::CombinedImageSampler;
	if (string == "SampledImage") return ShaderInputType::SampledImage;
	if (string == "StorageImage") return ShaderInputType::StorageImage;
	if (string == "UniformTexelBuffer") return ShaderInputType::UniformTexelBuffer;
	if (string == "StorageTexelBuffer") return ShaderInputType::StorageTexelBuffer;
	if (string == "UniformBuffer") return ShaderInputType::UniformBuffer;
	if (string == "StorageBuffer") return ShaderInputType::StorageBuffer;
	if (string == "UniformBufferDynamic") return ShaderInputType::UniformBufferDynamic;
	if (string == "StorageBufferDynamic") return ShaderInputType::StorageBufferDynamic;
	if (string == "PushConstant") return ShaderInputType::PushConstant;

	return ShaderInputType();
}

Bool Minty::parse_try_shader_input_type(String const& string, ShaderInputType& value)
{
	value = parse_to_shader_input_type(string);
	return value != ShaderInputType();
}