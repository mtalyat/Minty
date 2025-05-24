#pragma once
#include "Minty/Data/Vector.h"
#include "Minty/Render/ShaderBinding.h"

namespace Minty
{
	/// <summary>
	/// Information for a vertex input in a Shader.
	/// </summary>
	struct ShaderVertexInput
	{
		/// <summary>
		/// A collection of bindings within this vertex input.
		/// </summary>
		Vector<ShaderBinding> bindings;
	};
}