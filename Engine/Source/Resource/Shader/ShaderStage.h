#pragma once

/**
 * @file ShaderStage.h
 * @brief Header file defining the ShaderStage enum.
 * @author Mitchell Talyat
 */

#include "Core/Type/Enum.h"
#include "Core/Serialize/Parser.h"

namespace Minty
{
	/**
	 * @brief Determines the stage of the shader.
	 */
	enum class ShaderStageEnum
	{
		/**
		 * @brief Invalid.
		 */
		Undefined,
		
		/**
		 * @brief The vertex shader stage.
		 */
		Vertex,

		/**
		 * @brief The fragment shader stage.
		 */
		Fragment,

		Count
	};

	MINTY_ENABLE_ENUM_OPERATORS(ShaderStageEnum)
	
	struct ShaderStage
	{
		ShaderStageEnum value;

		constexpr ShaderStage() : value(ShaderStageEnum::Undefined) {}
		constexpr ShaderStage(ShaderStageEnum v) : value(v) {}
		constexpr operator ShaderStageEnum() const { return value; }
	};
	
	template<>
	struct Parser<ShaderStageEnum>
	{
		static Bool parse(StringView const str, ShaderStageEnum& value);
		static String to_string(ShaderStageEnum const& obj);
	};

	template<>
	struct Parser<ShaderStage>
	{
		inline static Bool parse(StringView const str, ShaderStage& value) { return Parser<ShaderStageEnum>::parse(str, value.value); }
		inline static String to_string(ShaderStage const& obj) { return Parser<ShaderStageEnum>::to_string(obj.value); }
	};
}
