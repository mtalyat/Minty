#include "pch.h"
#include "Shader.h"
#include "Minty/Render/ShaderModule.h"
#include "Minty/Render/Material.h"
#ifdef MINTY_VULKAN
#include "Platform/Vulkan/Vulkan_Shader.h"
#endif // MINTY_VULKAN

using namespace Minty;

Minty::Shader::Shader(ShaderInfo const& info)
	: Asset(info.id)
	, m_priority(info.priority)
	, m_renderPass(info.renderPass)
	, m_inputs()
	, m_materials()
	, m_depthMode(info.depthMode)
	, m_stencilMode(info.stencilMode)
{
	MINTY_ASSERT(info.fragmentShaderModule != nullptr, ErrorCode::Argument_ExpectedNonNull);
	MINTY_ASSERT(!info.fragmentShaderModuleEntryPoint.is_empty(), ErrorCode::Argument_ExpectedNonEmpty);
	MINTY_ASSERT(info.vertexShaderModule != nullptr, ErrorCode::Argument_ExpectedNonNull);
	MINTY_ASSERT(!info.vertexShaderModuleEntryPoint.is_empty(), ErrorCode::Argument_ExpectedNonEmpty);
	MINTY_ASSERT(info.renderPass != nullptr, ErrorCode::Argument_ExpectedNonNull);
	MINTY_ASSERT(info.primitiveTopology != ShaderPrimitiveTopology::Undefined, ErrorCode::Argument_ExpectedNonDefault);
	MINTY_ASSERT(info.polygonMode != ShaderPolygonMode::Undefined, ErrorCode::Argument_ExpectedNonDefault);
	MINTY_ASSERT(info.frontFace != ShaderFrontFace::Undefined, ErrorCode::Argument_ExpectedNonDefault);
	MINTY_ASSERT(info.cullMode != ShaderCullMode::Undefined, ErrorCode::Argument_ExpectedNonDefault);
	MINTY_ASSERT(info.lineWidth > 0.0f, ErrorCode::Argument_ExpectedAboveZero);
	MINTY_ASSERT(info.primitiveTopology != ShaderPrimitiveTopology::LineList || info.lineWidth == 1.0f, ErrorCode::Argument_InvalidValue);

	// copy inputs into map
	for (ShaderInput const& input : info.inputs)
	{
		MINTY_ASSERT(!m_inputs.contains(input.name), ErrorCode::Argument_DuplicateValue, input.name);
		m_inputs.add(input.name, input);
	}
}

void Minty::Shader::set_global_input(String const& name, void const* const data, Size const size)
{
	MINTY_ASSERT(m_inputs.contains(name), ErrorCode::Argument_KeyNotFound, name);
	MINTY_ASSERT(data != nullptr, ErrorCode::Argument_ExpectedNonNull);
	MINTY_ASSERT(size > 0, ErrorCode::Argument_ExpectedAboveZero);

	ShaderInput const& input = m_inputs.at(name);

	MINTY_ASSERT(size <= m_inputs.at(name).size, ErrorCode::Argument_InvalidSize, name);

	for (Material* const material : m_materials)
	{
		material->set_input(name, data, size);
	}
}

void Minty::Shader::register_material(Material* const material)
{
	MINTY_ASSERT(material != nullptr, ErrorCode::Argument_ExpectedNonNull);
	MINTY_ASSERT(!m_materials.contains(material), ErrorCode::Argument_KeyAlreadyExists);
	m_materials.add(material);
}

void Minty::Shader::unregister_material(Material* const material)
{
	MINTY_ASSERT(material != nullptr, ErrorCode::Argument_ExpectedNonNull);
	MINTY_ASSERT(m_materials.contains(material), ErrorCode::Argument_KeyNotFound);
	m_materials.remove(material);
}

Shared<Shader> Minty::Shader::create(ShaderInfo const& info)
{
#ifdef MINTY_VULKAN
	return Shared<Vulkan_Shader>(info);
#else
    return Shared<Shader>();
#endif // MINTY_VULKAN
}
