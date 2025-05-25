#include "pch.h"
#include "Shader.h"
#include "Minty/Render/ShaderModule.h"
#include "Minty/Render/Material.h"
#ifdef MINTY_VULKAN
#include "Platform/Vulkan/Vulkan_Shader.h"
#endif // MINTY_VULKAN

using namespace Minty;

Minty::Shader::Shader(ShaderBuilder const& builder)
	: Asset(builder.id)
	, m_renderPass(builder.renderPass)
	, m_inputs()
	, m_materials()
{
	MINTY_ASSERT(builder.fragmentShaderModule != nullptr, "ShaderBuilder fragmentShaderModule must not be null.");
	MINTY_ASSERT(!builder.fragmentShaderModuleEntryPoint.is_empty(), "ShaderBuilder fragmentShaderModuleEntryPoint must not be empty.");
	MINTY_ASSERT(builder.vertexShaderModule != nullptr, "ShaderBuilder vertexShaderModule must not be null.");
	MINTY_ASSERT(!builder.vertexShaderModuleEntryPoint.is_empty(), "ShaderBuilder vertexShaderModuleEntryPoint must not be empty.");
	MINTY_ASSERT(builder.renderPass != nullptr, "ShaderBuilder renderPass must not be null.");
	MINTY_ASSERT(builder.primitiveTopology != ShaderPrimitiveTopology::Undefined, "ShaderBuilder primitiveTopology must not be undefined.");
	MINTY_ASSERT(builder.polygonMode != ShaderPolygonMode::Undefined, "ShaderBuilder polygonMode must not be undefined.");
	MINTY_ASSERT(builder.frontFace != ShaderFrontFace::Undefined, "ShaderBuilder frontFace must not be undefined.");
	MINTY_ASSERT(builder.cullMode != ShaderCullMode::Undefined, "ShaderBuilder cullMode must not be undefined.");
	MINTY_ASSERT(builder.lineWidth > 0.0f, "ShaderBuilder lineWidth must be greater than 0.0f.");
	MINTY_ASSERT(builder.primitiveTopology != ShaderPrimitiveTopology::LineList || builder.lineWidth == 1.0f, "ShaderBuilder lineWidth must be 1.0f if not using line topology.");

	// copy inputs into map
	for (ShaderInput const& input : builder.inputs)
	{
		MINTY_ASSERT(!m_inputs.contains(input.name), "ShaderBuilder inputs must not contain duplicate names.");
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

Owner<Shader> Minty::Shader::create(ShaderBuilder const& builder)
{
#ifdef MINTY_VULKAN
	return Owner<Vulkan_Shader>(builder);
#else
    return Owner<Shader>();
#endif // MINTY_VULKAN
}
