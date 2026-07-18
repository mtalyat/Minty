#pragma once

/**
 * @file ImageAspect.h
 * @brief Header file defining the ImageAspect enum.
 * @author Mitchell Talyat
 */

#include "Core/Serialize/Parser.hpp"
#include "Core/Type/Enum.hpp"

namespace Minty
{
	/**
	 * @brief Determines how the image is used in the pipeline.
	 */
	enum class ImageAspectFlagsEnum
	{
		/**
		 * @brief Invalid.
		 */
		Undefined = 0,

		/**
		 * @brief Used for color.
		 */
		Color = 0x01,

		/**
		 * @brief Used for depth.
		 */
		Depth = 0x02,

		Count = 3,

		Default = Color,
	};

	MINTY_ENABLE_ENUM_OPERATORS(ImageAspectFlagsEnum)

	struct ImageAspectFlags
	{
		ImageAspectFlagsEnum value;

		constexpr ImageAspectFlags() : value(ImageAspectFlagsEnum::Undefined) {}
		constexpr ImageAspectFlags(ImageAspectFlagsEnum const value) : value(value) {}
		constexpr operator ImageAspectFlagsEnum() const { return value; }

		constexpr Bool has_flag(ImageAspectFlagsEnum const flag) const { return (static_cast<Size>(value) & static_cast<Size>(flag)) != 0; }
	};

	template<>
	struct Parser<ImageAspectFlagsEnum>
	{
		static Bool parse(StringView const str, ImageAspectFlagsEnum& value);
		static String to_string(ImageAspectFlagsEnum const& obj);
	};

	template<>
	struct Parser<ImageAspectFlags>
	{
		inline static Bool parse(StringView const str, ImageAspectFlags& value) { return Parser<ImageAspectFlagsEnum>::parse(str, value.value); }
		inline static String to_string(ImageAspectFlags const& obj) { return Parser<ImageAspectFlagsEnum>::to_string(obj.value); }
	};
}
