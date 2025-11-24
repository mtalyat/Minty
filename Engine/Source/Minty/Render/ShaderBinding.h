#pragma once
#include "Minty/Core/Type.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Vector.h"
#include "Minty/Render/ShaderAttribute.h"
#include "Minty/Render/ShaderInputRate.h"

namespace Minty
{
	/// <summary>
	/// Information for a binding in a Shader.
	/// </summary>
	struct ShaderBinding
	{
		/// <summary>
		/// The binding index of this binding in the Shader.
		/// </summary>
		UInt binding = 0;

		/// <summary>
		/// The input rate of the binding.
		/// </summary>
		ShaderInputRate inputRate = ShaderInputRate::Undefined;

		/// <summary>
		/// The attributes within this binding.
		/// </summary>
		Vector<ShaderAttribute> attributes;
	};
}