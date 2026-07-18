#pragma once

/**
 * @file ImageLayout.h
 * @brief Header file defining the ImageLayout enum.
 * @author Mitchell Talyat
 */

#include "Core/Serialize/Parser.hpp"
#include "Core/Type/Enum.hpp"

namespace Minty
{
	/**
	 * @brief Determines how the image data is laid out in memory.
	 */
	enum class ImageLayoutEnum
	{
		/**
		 * @brief Invalid.
		 */
		Undefined = 0,

		/**
		 * @brief Generic layout.
		 */
		General = 1,

		/**
		 * @brief Color attachment.
		 */
		ColorAttachment = 2,

		/**
		 * @brief Depth stencil attachment.
		 */
		DepthStencilAttachment = 3,

		/**
		 * @brief Depth stencil read only.
		 */
		DepthStencilReadOnly = 4,

		/**
		 * @brief Shader read only.
		 */
		ShaderReadOnly = 5,

		/**
		 * @brief Transfer source location.
		 */
		TransferSource = 6,

		/**
		 * @brief Transfer destination location.
		 */
		TransferDestination = 7,

		/**
		 * @brief Pre-initialized.
		 */
		Preinitialized = 8,

		/**
		 * @brief Presentation layout (ready to be rendered).
		 */
		Presentation = 9,

		Count,

		Default = General,
	};

	MINTY_ENABLE_ENUM_OPERATORS(ImageLayoutEnum)

	struct ImageLayout
	{
		ImageLayoutEnum value;

		constexpr ImageLayout() : value(ImageLayoutEnum::Undefined) {}
		constexpr ImageLayout(ImageLayoutEnum const layout) : value(layout) {}
		constexpr operator ImageLayoutEnum() const { return value; }
	};

	template<>
	struct Parser<ImageLayoutEnum>
	{
		static Bool parse(StringView const str, ImageLayoutEnum& value);
		static String to_string(ImageLayoutEnum const& obj);
	};
	
	template<>
	struct Parser<ImageLayout>
	{
		inline static Bool parse(StringView const str, ImageLayout& value) { return Parser<ImageLayoutEnum>::parse(str, value.value); }
		inline static String to_string(ImageLayout const& obj) { return Parser<ImageLayoutEnum>::to_string(obj.value); }
	};
}
