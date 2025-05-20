#pragma once
#include "Minty/Data/String.h"
#include "Minty/Serialization/Parse.h"

namespace Minty
{
	/// <summary>
	/// Determines how the image is used.
	/// </summary>
	enum class ImageUsage
	{
		/// <summary>
		/// Invalid.
		/// </summary>
		Undefined = 0,

		/// <summary>
		/// The image is sampled.
		/// </summary>
		Sampled = 1,

		/// <summary>
		/// The image is used for storage.
		/// </summary>
		Storage = 2,

		/// <summary>
		/// The image is used for input attachment.
		/// </summary>
		Color = 4,

		/// <summary>
		/// The image is used for depth/stencil.
		/// </summary>
		DepthStencil = 8
	};

	MINTY_ENUM_FLAGS_OPERATORS(ImageUsage)

	String to_string(ImageUsage const obj);
	ImageUsage parse_to_image_usage(String const& string);
	Bool parse_try_image_usage(String const& string, ImageUsage& value);
	template<>
	inline ImageUsage parse_to<ImageUsage>(String const& string) { return parse_to_image_usage(string); }
	template<>
	inline Bool parse_try<ImageUsage>(String const& string, ImageUsage& value) { return parse_try_image_usage(string, value); }
}