#pragma once
#include "Minty/Serialization/Parse.h"
#include "Minty/Serialization/ToString.h"

namespace Minty
{
	/// <summary>
	/// The perspective type for a Camera.
	/// </summary>
	enum class Perspective
	{
		/// <summary>
		/// Invalid.
		/// </summary>
		Undefined,

		/// <summary>
		/// Perspective camera view.
		/// </summary>
		Perspective,

		/// <summary>
		/// Orthographic camera view.
		/// </summary>
		Orthographic,
	};

	String to_string(Perspective const obj);
	Perspective parse_to_perspective(String const& string);
	Bool parse_try_perspective(String const& string, Perspective& value);
	template<>
	inline Perspective parse_to<Perspective>(String const& string) { return parse_to_perspective(string); }
	template<>
	inline Bool parse_try<Perspective>(String const& string, Perspective& value) { return parse_try_perspective(string, value); }
}