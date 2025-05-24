#pragma once
#include "Minty/Data/String.h"
#include "Minty/Serialization/Parse.h"

namespace Minty
{
	/// <summary>
	/// Determines how the image data is laid out in memory.
	/// </summary>
	enum class ImageLayout
	{
		/// <summary>
		/// Invalid.
		/// </summary>
		Undefined = 0,

		/// <summary>
		/// Generic layout.
		/// </summary>
		General = 1,

		/// <summary>
		/// Color attachment.
		/// </summary>
		ColorAttachment = 2,

		/// <summary>
		/// Depth stencil attachment.
		/// </summary>
		DepthStencilAttachment = 3,

		/// <summary>
		/// Depth stencil read only.
		/// </summary>
		DepthStencilReadOnly = 4,

		/// <summary>
		/// Shader read only.
		/// </summary>
		ShaderReadOnly = 5,

		/// <summary>
		/// Transfer source location.
		/// </summary>
		TransferSource = 6,

		/// <summary>
		/// Transfer destination location.
		/// </summary>
		TransferDestination = 7,

		/// <summary>
		/// Pre-initialized.
		/// </summary>
		Preinitialized = 8,

		/// <summary>
		/// Presentation layout (ready to be rendered).
		/// </summary>
		Presentation = 9,
	};

	String to_string(ImageLayout const obj);
	ImageLayout parse_to_image_layout(String const& string);
	Bool parse_try_image_layout(String const& string, ImageLayout& value);
	template<>
	inline ImageLayout parse_to<ImageLayout>(String const& string) { return parse_to_image_layout(string); }
	template<>
	inline Bool parse_try<ImageLayout>(String const& string, ImageLayout& value) { return parse_try_image_layout(string, value); }
}