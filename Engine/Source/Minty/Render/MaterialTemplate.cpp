#include "pch.h"
#include "MaterialTemplate.h"
#include "Minty/Core/Format.h"
#include "Minty/Render/Shader.h"
#include "Minty/Render/MaterialTemplateInfo.h"

using namespace Minty;

Minty::MaterialTemplate::MaterialTemplate(MaterialTemplateInfo const& info)
	: Asset(info.id)
	, m_shader(info.shader)
	, m_cargo(info.values)
{
	MINTY_ASSERT(m_shader != nullptr, ErrorCode::Argument_ExpectedNonNull);

#ifdef MINTY_DEBUG

	// check for all valid inputs
	for (auto const& [name, cargo] : get_inputs())
	{
		MINTY_ASSERT_F(m_shader->contains_input(name), ErrorCode::Argument_KeyNotFound, name);
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

Shared<MaterialTemplate> Minty::MaterialTemplate::create(MaterialTemplateInfo const& info)
{
    return Shared<MaterialTemplate>::create(info);
}

Shared<MaterialTemplate> Minty::MaterialTemplate::create()
{
	MaterialTemplateInfo info{};
	return create(info);
}
