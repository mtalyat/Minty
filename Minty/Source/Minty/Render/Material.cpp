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
	, m_values(builder.values)
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

Owner<Material> Minty::Material::create(MaterialBuilder const& builder)
{
#ifdef MINTY_VULKAN
	return Owner<Vulkan_Material>(builder);
#else
	return Owner<Material>();
#endif // MINTY_VULKAN
}
