#pragma once
#include "Minty/Data/String.h"
#include "Minty/Serialization/Parse.h"

namespace Minty
{
	/// <summary>
	/// Determines how the image is used in the pipeline.
	/// </summary>
	enum class ImageAspect
	{
		/// <summary>
		/// Invalid.
		/// </summary>
		Undefined = 0,

		/// <summary>
		/// Used for color.
		/// </summary>
		Color = 1,

		/// <summary>
		/// Used for depth.
		/// </summary>
		Depth = 2,
	};

	String to_string(ImageAspect const obj);
	ImageAspect parse_to_image_aspect(String const& string);
	Bool parse_try_image_aspect(String const& string, ImageAspect& value);
	template<>
	inline ImageAspect parse_to<ImageAspect>(String const& string) { return parse_to_image_aspect(string); }
	template<>
	inline Bool parse_try<ImageAspect>(String const& string, ImageAspect& value) { return parse_try_image_aspect(string, value); }
}