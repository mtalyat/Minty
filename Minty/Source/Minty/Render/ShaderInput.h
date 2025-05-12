#pragma once
#include "Minty/Core/Type.h"
#include "Minty/Core/Types.h"
#include "Minty/Render/ShaderStage.h"
#include "Minty/Render/ShaderInputType.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/String.h"
#include "Minty/Data/Variable.h"

namespace Minty
{
	/// <summary>
	/// Information for an input in a Shader.
	/// </summary>
	struct ShaderInput
	{
		/// <summary>
		/// The binding of this input in the Shader.
		/// </summary>
		UInt binding = 0;

		/// <summary>
		/// The stage of the Shader this input is used in.
		/// </summary>
		ShaderStage stage = ShaderStage::Undefined;

		/// <summary>
		/// The type of the input.
		/// </summary>
		ShaderInputType type = ShaderInputType::Undefined;

		/// <summary>
		/// The number of elements in this input. Should be 1 for non-array inputs.
		/// </summary>
		UInt count = 1;

		/// <summary>
		/// When true, this input is optimized to be updated every frame.
		/// </summary>
		Bool frequent = false;

		/// <summary>
		/// The name of this input.
		/// </summary>
		String name = "";

		/// <summary>
		/// A collection of Variables that are within this input.
		/// </summary>
		Vector<Tuple<String, Variable>> data;

		/// <summary>
		/// The size of the input in bytes, for one element.
		///		Ex. For an array of 10 Floats, this would be sizeof(Float).
		/// Only use this for inputs that need a buffer (such as a uniform constant).
		/// </summary>
		Size size = 0;

		/// <summary>
		/// The offset of the input in bytes.
		/// </summary>
		Size offset = 0;
	};
}