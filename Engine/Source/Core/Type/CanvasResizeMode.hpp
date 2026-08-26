#pragma once

/**
 * @file CanvasResizeMode.hpp
 * @brief Header file defining the CanvasResizeMode enum.
 * @author Mitchell Talyat
 */

#include "Core/Serialize/Parser.hpp"

namespace Minty
{
	/**
	 * @brief Determines how a Canvas should react to window/framebuffer resize.
	 */
	enum class CanvasResizeModeEnum
	{
		/**
		 * @brief Invalid.
		 */
		Undefined = 0,

		/**
		 * @brief Keeps the current canvas resolution unchanged.
		 */
		FixedSize = 1,

		/**
		 * @brief Updates the canvas resolution to match the active framebuffer size.
		 */
		Dynamic = 2,

		Count,

		Default = FixedSize
	};

	struct CanvasResizeMode
	{
		CanvasResizeModeEnum value;

		constexpr CanvasResizeMode() : value(CanvasResizeModeEnum::Undefined) {}
		constexpr CanvasResizeMode(CanvasResizeModeEnum const value) : value(value) {}
		constexpr operator CanvasResizeModeEnum() const { return value; }

		constexpr Bool operator==(CanvasResizeModeEnum const other) const { return value == other; }
		constexpr Bool operator!=(CanvasResizeModeEnum const other) const { return value != other; }
	};

	template<>
	struct Parser<CanvasResizeModeEnum>
	{
		static Bool parse(StringView const str, CanvasResizeModeEnum &value);
		static String to_string(CanvasResizeModeEnum const &obj);
	};

	template<>
	struct Parser<CanvasResizeMode>
	{
		inline static Bool parse(StringView const str, CanvasResizeMode &value) { return Parser<CanvasResizeModeEnum>::parse(str, value.value); }
		inline static String to_string(CanvasResizeMode const &obj) { return Parser<CanvasResizeModeEnum>::to_string(obj.value); }
	};
}