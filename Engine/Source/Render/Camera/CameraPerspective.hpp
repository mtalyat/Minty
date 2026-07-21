#pragma once

/**
 * @file Perspective.hpp
 * @brief Header file defining the Perspective enum.
 * @author Mitchell Talyat
 */

#include "Core/Serialize/Parser.hpp"
#include "Core/Type/Enum.hpp"

namespace Minty
{
	/**
	 * @brief The perspective type for a Camera.
	 */
	enum class CameraPerspectiveEnum
	{
		/**
		 * @brief Invalid.
		 */
		Undefined,

		/**
		 * @brief Perspective camera view.
		 */
		Perspective,

		/**
		 * @brief Orthographic camera view.
		 */
		Orthographic,

		Count,

		Default = Perspective
	};

	MINTY_ENABLE_ENUM_OPERATORS(CameraPerspectiveEnum)

	struct CameraPerspective
	{
		CameraPerspectiveEnum type;

		constexpr CameraPerspective() : type(CameraPerspectiveEnum::Undefined) {}
		constexpr CameraPerspective(CameraPerspectiveEnum type) : type(type) {}
		constexpr operator CameraPerspectiveEnum() const { return type; }
	};
	
	template<>
	struct Parser<CameraPerspectiveEnum>
	{
		static Bool parse(StringView const str, CameraPerspectiveEnum& value);
		static String to_string(CameraPerspectiveEnum const& obj);
	};

	template<>
	struct Parser<CameraPerspective>
	{
		inline static Bool parse(StringView const str, CameraPerspective& value) { return Parser<CameraPerspectiveEnum>::parse(str, value.type); }
		inline static String to_string(CameraPerspective const& obj) { return Parser<CameraPerspectiveEnum>::to_string(obj.type); }
	};
}
