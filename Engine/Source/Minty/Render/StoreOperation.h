#pragma once
#include "Minty/Serialization/Parse.h"
#include "Minty/Serialization/ToString.h"

namespace Minty
{
	/// <summary>
	/// The store operation.
	/// </summary>
	enum class StoreOperation
	{
		/// <summary>
		/// Invalid.
		/// </summary>
		Undefined,

		/// <summary>
		/// Does nothing with the current data.
		/// </summary>
		DontCare,

		/// <summary>
		/// Stores the current data.
		/// </summary>
		Store,
	};

	String to_string(StoreOperation const obj);
	StoreOperation parse_to_store_operation(String const& string);
	Bool parse_try_store_operation(String const& string, StoreOperation& value);
	template<>
	inline StoreOperation parse_to<StoreOperation>(String const& string) { return parse_to_store_operation(string); }
	template<>
	inline Bool parse_try<StoreOperation>(String const& string, StoreOperation& value) { return parse_try_store_operation(string, value); }
}