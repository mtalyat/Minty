#pragma once

#include "Minty/Data/String.h"
#include "Minty/Serialization/Parse.h"

namespace Minty
{
	enum class DepthMode
	{
		/// <summary>
		/// Do not use depth buffer.
		/// </summary>
		None,

		/// <summary>
		/// Write to the depth buffer.
		/// </summary>
		Write,

		/// <summary>
		/// Test the depth buffer.
		/// </summary>
		Test
	};

	String to_string(DepthMode const obj);
	DepthMode parse_to_depth_mode(String const& string);
	Bool parse_try_depth_mode(String const& string, DepthMode& value);
	template<>
	inline DepthMode parse_to<DepthMode>(String const& string) { return parse_to_depth_mode(string); }
	template<>
	inline Bool parse_try<DepthMode>(String const& string, DepthMode& value) { return parse_try_depth_mode(string, value); }
}