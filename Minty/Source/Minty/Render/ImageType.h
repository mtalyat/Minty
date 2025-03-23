#pragma once
#include "Minty/Data/String.h"
#include "Minty/Serialization/Parse.h"

namespace Minty
{
	/// <summary>
	/// The amount of dimensions on the image.
	/// </summary>
	enum class ImageType
	{
		Undefined = 0,

		/// <summary>
		/// One dimensional.
		/// </summary>
		D1 = 1,

		/// <summary>
		/// Two dimensional.
		/// </summary>
		D2 = 2,

		/// <summary>
		/// Three dimensional.
		/// </summary>
		D3 = 3,
	};

	String to_string(ImageType const obj);
	ImageType parse_to_image_type(String const& string);
	Bool parse_try_image_type(String const& string, ImageType& value);
	template<>
	inline ImageType parse_to<ImageType>(String const& string) { return parse_to_image_type(string); }
	template<>
	inline Bool parse_try<ImageType>(String const& string, ImageType& value) { return parse_try_image_type(string, value); }
}