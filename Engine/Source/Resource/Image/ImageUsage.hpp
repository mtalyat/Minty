#pragma once

/**
 * @file ImageUsage.h
 * @brief Header file defining the ImageUsage enum.
 * @author Mitchell Talyat
 */

#include "Core/Serialize/Parser.hpp"
#include "Core/Type/Enum.hpp"

namespace Minty
{
	/**
	 * @brief Determines how the image is used.
	 */
	enum class ImageUsageFlagsEnum
	{
		/**
		 * @brief Invalid.
		 */
		Undefined = 0x0,

		/**
		 * @brief The image is sampled.
		 */
		Sampled = 0x1,

		/**
		 * @brief The image is used for storage.
		 */
		Storage = 0x2,

		/**
		 * @brief The image is used for input attachment.
		 */
		Color = 0x4,

		/**
		 * @brief The image is used for depth/stencil.
		 */
		DepthStencil = 0x8,

		/**
		 * @brief The image is used as a transfer source.
		 */
		TransferSrc = 0x10,

		/**
		 * @brief The image is used as a transfer destination.
		 */
		TransferDst = 0x20,

		Count = 7,

		Default = Sampled,
	};

	MINTY_ENABLE_ENUM_OPERATORS(ImageUsageFlagsEnum)
	
	struct ImageUsageFlags
	{
		ImageUsageFlagsEnum value;

		constexpr ImageUsageFlags() : value(ImageUsageFlagsEnum::Undefined) {}
		constexpr ImageUsageFlags(ImageUsageFlagsEnum const value) : value(value) {}
		constexpr operator ImageUsageFlagsEnum() const { return value; }

		constexpr Bool has_flag(ImageUsageFlagsEnum const flag) const { return (static_cast<Size>(value) & static_cast<Size>(flag)) != 0; }
		constexpr Bool is_visible() const { return (static_cast<Size>(value) & ~(static_cast<Size>(ImageUsageFlagsEnum::TransferDst) | static_cast<Size>(ImageUsageFlagsEnum::TransferSrc))) != 0; }
	};

	template<>
	struct Parser<ImageUsageFlagsEnum>
	{
		static Bool parse(StringView const str, ImageUsageFlagsEnum& value);
		static String to_string(ImageUsageFlagsEnum const& obj);
	};
	
	template<>
	struct Parser<ImageUsageFlags>
	{
		inline static Bool parse(StringView const str, ImageUsageFlags& value) { return Parser<ImageUsageFlagsEnum>::parse(str, value.value); }
		inline static String to_string(ImageUsageFlags const& obj) { return Parser<ImageUsageFlagsEnum>::to_string(obj.value); }
	};
}
