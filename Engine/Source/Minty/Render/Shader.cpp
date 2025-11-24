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
	MINTY_ASSERT(info.fragmentShaderModule != nullptr, "ShaderInfo fragmentShaderModule must not be null.");
	MINTY_ASSERT(!info.fragmentShaderModuleEntryPoint.is_empty(), "ShaderInfo fragmentShaderModuleEntryPoint must not be empty.");
	MINTY_ASSERT(info.vertexShaderModule != nullptr, "ShaderInfo vertexShaderModule must not be null.");
	MINTY_ASSERT(!info.vertexShaderModuleEntryPoint.is_empty(), "ShaderInfo vertexShaderModuleEntryPoint must not be empty.");
	MINTY_ASSERT(info.renderPass != nullptr, "ShaderInfo renderPass must not be null.");
	MINTY_ASSERT(info.primitiveTopology != ShaderPrimitiveTopology::Undefined, "ShaderInfo primitiveTopology must not be undefined.");
	MINTY_ASSERT(info.polygonMode != ShaderPolygonMode::Undefined, "ShaderInfo polygonMode must not be undefined.");
	MINTY_ASSERT(info.frontFace != ShaderFrontFace::Undefined, "ShaderInfo frontFace must not be undefined.");
	MINTY_ASSERT(info.cullMode != ShaderCullMode::Undefined, "ShaderInfo cullMode must not be undefined.");
	MINTY_ASSERT(info.lineWidth > 0.0f, "ShaderInfo lineWidth must be greater than 0.0f.");
	MINTY_ASSERT(info.primitiveTopology != ShaderPrimitiveTopology::LineList || info.lineWidth == 1.0f, "ShaderInfo lineWidth must be 1.0f if not using line topology.");

	// copy inputs into map
	for (ShaderInput const& input : info.inputs)
	{
		MINTY_ASSERT(!m_inputs.contains(input.name), "ShaderInfo inputs must not contain duplicate names.");
		m_inputs.add(input.name, input);
	}
}

void Minty::Shader::set_global_input(String const& name, void const* const data, Size const size)
{
	MINTY_ASSERT(m_inputs.contains(name), F("Shader does not contain input with name: {}", name));
	MINTY_ASSERT(data != nullptr, "Data must not be null.");
	MINTY_ASSERT(size > 0, "Data size must be greater than 0.");

	ShaderInput const& input = m_inputs.at(name);

	MINTY_ASSERT(size <= m_inputs.at(name).size, "Data size must not exceed the size of the input size.");

	for (Material* const material : m_materials)
	{
		material->set_input(name, data, size);
	}
}

void Minty::Shader::register_material(Material* const material)
{
	MINTY_ASSERT(material != nullptr, "Material must not be null.");
	MINTY_ASSERT(!m_materials.contains(material), "Material is already registered to this Shader.");
	m_materials.add(material);
}

void Minty::Shader::unregister_material(Material* const material)
{
	MINTY_ASSERT(material != nullptr, "Material must not be null.");
	MINTY_ASSERT(m_materials.contains(material), "Material is not registered to this Shader.");
	m_materials.remove(material);
}

Owner<Shader> Minty::Shader::create(ShaderInfo const& info)
{
#ifdef MINTY_VULKAN
	return Owner<Vulkan_Shader>(info);
#else
    return Owner<Shader>();
#endif // MINTY_VULKAN
}
