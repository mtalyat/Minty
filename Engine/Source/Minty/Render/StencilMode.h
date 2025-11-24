#pragma once

#include "Minty/Serialization/Parse.h"

namespace Minty
{
	enum class StencilMode
	{
		/// <summary>
		/// Do not use stencil buffer.
		/// </summary>
		None,

		/// <summary>
		/// Write to the stencil buffer.
		/// </summary>
		Write,

		/// <summary>
		/// Test the stencil buffer.
		/// </summary>
		Test
	};

	String to_string(StencilMode const obj);
	StencilMode parse_to_stencil_mode(String const& string);
	Bool parse_try_stencil_mode(String const& string, StencilMode& value);
	template<>
	inline StencilMode parse_to<StencilMode>(String const& string) { return parse_to_stencil_mode(string); }
	template<>
	inline Bool parse_try<StencilMode>(String const& string, StencilMode& value) { return parse_try_stencil_mode(string, value); }
}