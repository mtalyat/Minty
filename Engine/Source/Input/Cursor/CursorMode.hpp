#pragma once

/**
 * @file CursorMode.h
 * @brief Header file for cursor mode enumeration.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Core/Serialize/Parser.hpp"
#include "Core/Type/Enum.hpp"

namespace Minty
{
	/**
	 * @brief The visual state of the cursor.
	 */
	enum class CursorModeEnum : Int
	{
		/**
		 * @brief Normal cursor mode.
		 */
		Normal,

		/**
		 * @brief Hidden cursor mode.
		 */
		Hidden,
		
		/**
		 * @brief Disabled cursor mode.
		 */
		Disabled,

		Count
	};

	MINTY_ENABLE_ENUM_OPERATORS(CursorModeEnum)

	struct CursorMode
	{
		CursorModeEnum mode;

		constexpr CursorMode() : mode(CursorModeEnum::Normal) {}
		constexpr CursorMode(CursorModeEnum const mode) : mode(mode) {}

		constexpr operator CursorModeEnum() const { return mode; }
		constexpr Bool operator==(CursorMode const& other) const { return mode == other.mode; }
		constexpr Bool operator!=(CursorMode const& other) const { return mode != other.mode; }
	};

	template<>
	struct Parser<CursorModeEnum>
	{
		static Bool parse(StringView const str, CursorModeEnum& value);
		static String to_string(CursorModeEnum const& obj);
	};
	
	template<>
	struct Parser<CursorMode>
	{
		inline static Bool parse(StringView const str, CursorMode& value) { return Parser<CursorModeEnum>::parse(str, value.mode); }
		inline static String to_string(CursorMode const& obj) { return Parser<CursorModeEnum>::to_string(obj.mode); }
	};
}
