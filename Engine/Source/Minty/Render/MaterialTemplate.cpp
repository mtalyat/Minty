#include "pch.h"
#include "MaterialTemplate.h"
#include "Minty/Core/Format.h"
#include "Minty/Render/Shader.h"

using namespace Minty;

Minty::MaterialTemplate::MaterialTemplate(MaterialTemplateBuilder const& builder)
	: Asset(builder.id)
	, m_shader(builder.shader)
	, m_cargo(builder.values)
{
	MINTY_ASSERT(m_shader != nullptr, "MaterialTemplate shader must not be null.");

#ifdef MINTY_DEBUG

	// check for all valid inputs
	for (auto const& [name, cargo] : get_inputs())
	{
		MINTY_ASSERT(m_shader->contains_input(name), F("Shader does not contain input with name: {}", name));
	}

#endif // MINTY_DEBUG

	// add any missing inputs from the shader
	for (auto const& [name, input] : m_shader->get_inputs())
	{
		// ignore if name is an object within the cargo
		if (m_cargo.contains(name))
		{
			continue;
		}

		// add variable values to the object
		Object object;
		for (auto const& [variableName, variable] : input.data)
		{
			object.add(variableName, variable);
		}
		m_cargo.add(name, object);
	}
}

Owner<MaterialTemplate> Minty::MaterialTemplate::create(MaterialTemplateBuilder const& builder)
{
    return Owner<MaterialTemplate>(builder);
}
