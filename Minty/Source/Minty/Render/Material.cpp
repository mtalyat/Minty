#include "pch.h"
#include "Material.h"
#include "Minty/Render/MaterialTemplate.h"
#include "Minty/Render/Shader.h"
#ifdef MINTY_VULKAN
#include "Platform/Vulkan/Vulkan_Material.h"
#endif // MINTY_VULKAN

using namespace Minty;

Minty::Material::Material(MaterialBuilder const& builder)
	: Asset(builder.id)
	, m_materialTemplate(builder.materialTemplate)
	, m_cargo(builder.values)
{
	MINTY_ASSERT(m_materialTemplate != nullptr, "MaterialTemplate must not be null.");

	// add self to shader
	Ref<Shader> shader = m_materialTemplate->get_shader();
	shader->register_material(this);
}

Minty::Material::~Material()
{
	if (m_materialTemplate == nullptr) return;

	// remove self from shader
	Ref<Shader> shader = m_materialTemplate->get_shader();
	shader->unregister_material(this);
}

Bool Minty::Material::has_input(String const& name) const
{
	// check self
	if (m_cargo.contains(name))
	{
		return true;
	}

	// check template
	MINTY_ASSERT(m_materialTemplate != nullptr, "MaterialTemplate must not be null.");
	if (m_materialTemplate->has_input(name))
	{
		return true;
	}

	// not found
	return false;
}

Object const& Minty::Material::get_input(String const& name) const
{
	MINTY_ASSERT(has_input(name), F("Material does not have input with name: {}", name));

	// check self
	auto it = m_cargo.find(name);
	if (it != m_cargo.end())
	{
		return it->get_second();
	}

	// must be in template
	return m_materialTemplate->get_input(name);
}

Bool Minty::Material::try_set_input(String const& name, void const* const data, Size const size)
{
	Ref<Shader> shader = m_materialTemplate->get_shader();
	if (!shader->contains_input(name))
	{
		// does not exist
		return false;
	}

	// exists
	set_input(name, data, size);
	return true;
}

Bool Minty::Material::get_input(String const& name, void* const data, Size const size) const
{
	// if this Material has a value for the input, copy it
	return false;
}

Owner<Material> Minty::Material::create(MaterialBuilder const& builder)
{
#ifdef MINTY_VULKAN
	return Owner<Vulkan_Material>(builder);
#else
	return Owner<Material>();
#endif // MINTY_VULKAN
}
