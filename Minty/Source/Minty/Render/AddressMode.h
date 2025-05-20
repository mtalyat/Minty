#pragma once
#include "Minty/Data/String.h"
#include "Minty/Serialization/Parse.h"

namespace Minty
{
	/// <summary>
	/// Determines how the image data is accessed in the pipeline.
	/// </summary>
	enum class AddressMode
	{
		/// <summary>
		/// Invalid.
		/// </summary>
		Undefined = 0,

		/// <summary>
		/// The texture coordinates are repeated.
		/// </summary>
		Repeat = 1,

		/// <summary>
		/// The texture coordinates are mirrored and repeated.
		/// </summary>
		MirroredRepeat = 2,

		/// <summary>
		/// The texture coordinates are clamped to the edge.
		/// </summary>
		ClampToEdge = 3,

		/// <summary>
		/// The texture coordinates are clamped to the border.
		/// </summary>
		ClampToBorder = 4,

		/// <summary>
		/// The texture coordinates are mirrored and clamped to the edge.
		/// </summary>
		MirroredClampToEdge = 5,
	};

	String to_string(AddressMode const obj);
	AddressMode parse_to_address_mode(String const& string);
	Bool parse_try_address_mode(String const& string, AddressMode& value);
	template<>
	inline AddressMode parse_to<AddressMode>(String const& string) { return parse_to_address_mode(string); }
	template<>
	inline Bool parse_try<AddressMode>(String const& string, AddressMode& value) { return parse_try_address_mode(string, value); }

}