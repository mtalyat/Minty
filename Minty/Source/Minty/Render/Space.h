#pragma once
#include "Minty/Serialization/Parse.h"
#include "Minty/Serialization/ToString.h"

namespace Minty
{
	/// <summary>
	/// Classifies the Space that an object is in.
	/// </summary>
	enum class Space
	{
		/// <summary>
		/// Invalid space.
		/// </summary>
		Undefined,

		/// <summary>
		/// 3D world space.
		/// </summary>
		D3,

		/// <summary>
		/// 2D world space.
		/// </summary>
		D2,

		/// <summary>
		/// User Interface space.
		/// </summary>
		UI,
	};

	String to_string(Space const obj);
	Space parse_to_space(String const& string);
	Bool parse_try_space(String const& string, Space& value);
	template<>
	inline Space parse_to<Space>(String const& string) { return parse_to_space(string); }
	template<>
	inline Bool parse_try<Space>(String const& string, Space& value) { return parse_try_space(string, value); }
}