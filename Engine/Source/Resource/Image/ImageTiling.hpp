#pragma once

/**
 * @file ImageTiling.h
 * @brief Header file defining the ImageTiling enum.
 * @author Mitchell Talyat
 */

#include "Core/Serialize/Parser.hpp"
#include "Core/Type/Enum.hpp"

namespace Minty
{
	/**
	 * @brief Determines how the image is tiled.
	 */
	enum class ImageTilingEnum
	{
		/**
		 * @brief Invalid.
		 */
		Undefined = 0,

		/**
		 * @brief Optimal tiling.
		 */
		Optimal,

		/**
		 * @brief Linear tiling.
		 */
		Linear,

		Count,

		Default = Optimal,
	};
	
	MINTY_ENABLE_ENUM_OPERATORS(ImageTilingEnum)

	struct ImageTiling
	{
		ImageTilingEnum value;

		constexpr ImageTiling() : value(ImageTilingEnum::Undefined) {}
		constexpr ImageTiling(ImageTilingEnum const value) : value(value) {}
		constexpr operator ImageTilingEnum() const { return value; }
	};
	
	template<>
	struct Parser<ImageTilingEnum>
	{
		static Bool parse(StringView const str, ImageTilingEnum& value);
		static String to_string(ImageTilingEnum const& obj);
	};

	template<>
	struct Parser<ImageTiling>
	{
		inline static Bool parse(StringView const str, ImageTiling& value) { return Parser<ImageTilingEnum>::parse(str, value.value); }
		inline static String to_string(ImageTiling const& obj) { return Parser<ImageTilingEnum>::to_string(obj.value); }
	};
}
