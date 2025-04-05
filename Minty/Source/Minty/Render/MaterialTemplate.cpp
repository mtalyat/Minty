#include "pch.h"
#include "MaterialTemplate.h"
#include "Minty/Core/Format.h"
#include "Minty/Render/Shader.h"

using namespace Minty;

Minty::MaterialTemplate::MaterialTemplate(MaterialTemplateBuilder const& builder)
	: Asset(builder.id)
	, m_shader(builder.shader)
	, m_values(builder.values)
{
	MINTY_ASSERT(m_shader != nullptr, "MaterialTemplate shader must not be null.");

#ifdef MINTY_DEBUG

	// check for all valid inputs
	for (auto const& [name, cargo] : get_values())
	{
		MINTY_ASSERT(m_shader->contains_input(name), F("Shader does not contain input with name: {}", name));
	}

	// check to verify that the material template has a default value for ALL shader inputs
	MINTY_ASSERT(m_shader->get_inputs().get_size() == m_values.get_size(), "MaterialTemplate does not have a default value for all shader inputs.");

#endif // MINTY_DEBUG
}

Owner<MaterialTemplate> Minty::MaterialTemplate::create(MaterialTemplateBuilder const& builder)
{
    return Owner<MaterialTemplate>(builder);
}
