#pragma once

/**
 * @file ImageType.h
 * @brief Header file defining the ImageType enum.
 * @author Mitchell Talyat
 */

#include "Core/Serialize/Parser.h"
#include "Core/Type/Enum.h"

namespace Minty
{
	/**
	 * @brief The amount of dimensions on the image.
	 */
	enum class ImageTypeEnum
	{
		/**
		 * @brief Invalid.
		 */
		Undefined = 0,

		/**
		 * @brief One dimensional.
		 */
		D1 = 1,

		/**
		 * @brief Two dimensional.
		 */
		D2 = 2,

		/**
		 * @brief Three dimensional.
		 */
		D3 = 3,

		Count,

		Default = D2,
	};

	MINTY_ENABLE_ENUM_OPERATORS(ImageTypeEnum)
	
	struct ImageType
	{
		ImageTypeEnum value;

		constexpr ImageType() : value(ImageTypeEnum::Undefined) {}
		constexpr ImageType(ImageTypeEnum const value) : value(value) {}
		constexpr operator ImageTypeEnum() const { return value; }
	};

	template<>
	struct Parser<ImageTypeEnum>
	{
		static Bool parse(StringView const str, ImageTypeEnum& value);
		static String to_string(ImageTypeEnum const& obj);
	};
	
	template<>
	struct Parser<ImageType>
	{
		inline static Bool parse(StringView const str, ImageType& value) { return Parser<ImageTypeEnum>::parse(str, value.value); }
		inline static String to_string(ImageType const& obj) { return Parser<ImageTypeEnum>::to_string(obj.value); }
	};
}
