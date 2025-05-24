#pragma once
#include "Minty/Core/Type.h"
#include "Minty/Core/Types.h"

namespace Minty
{
	/// <summary>
	/// Information for an attribute in a Shader.
	/// </summary>
	struct ShaderAttribute
	{
		/// <summary>
		/// The location of the attribute in the shader.
		/// </summary>
		UInt location = 0;

		/// <summary>
		/// The type of the attribute.
		/// </summary>
		Type type = Type::Undefined;
	};
}