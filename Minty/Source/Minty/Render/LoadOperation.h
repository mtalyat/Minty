#pragma once
#include "Minty/Serialization/Parse.h"
#include "Minty/Serialization/ToString.h"

namespace Minty
{
	/// <summary>
	/// The load operation.
	/// </summary>
	enum class LoadOperation
	{
		/// <summary>
		/// Invalid.
		/// </summary>
		Undefined,

		/// <summary>
		/// Do nothing with the previous data.
		/// </summary>
		DontCare,

		/// <summary>
		/// Loads the previous data.
		/// </summary>
		Load,

		/// <summary>
		/// Clears the previous data.
		/// </summary>
		Clear,
	};

	String to_string(LoadOperation const obj);
	LoadOperation parse_to_load_operation(String const& string);
	Bool parse_try_load_operation(String const& string, LoadOperation& value);
	template<>
	inline LoadOperation parse_to<LoadOperation>(String const& string) { return parse_to_load_operation(string); }
	template<>
	inline Bool parse_try<LoadOperation>(String const& string, LoadOperation& value) { return parse_try_load_operation(string, value); }
}