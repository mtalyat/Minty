#pragma once

/**
 * @file PipelineCullMode.h
 * @brief Header file defining the PipelineCullMode enum.
 * @author Mitchell Talyat
 */

#include "Core/Type/Enum.hpp"
#include "Platform/Type/Primitive.hpp"

namespace Minty
{
	/**
	 * @brief Determines how the Shader culls faces.
	 */
	enum class PipelineCullModeEnum
	{
		Undefined = 0,

		/**
		 * @brief There is no culling.
		 */
		None = 1,

		/**
		 * @brief The front side of a face is culled.
		 */
		Front = 2,

		/**
		 * @brief The back side of a face is culled.
		 */
		Back = 3,
		
		/**
		 * @brief Both sides of a face are culled.
		 */
		Both = 4,

		Count,

		Default = Back,
	};

	MINTY_ENABLE_ENUM_OPERATORS(PipelineCullModeEnum)

	struct PipelineCullMode
	{
		PipelineCullModeEnum value;

		constexpr PipelineCullMode() : value(PipelineCullModeEnum::Default) {}
		constexpr PipelineCullMode(PipelineCullModeEnum v) : value(v) {}
		constexpr operator PipelineCullModeEnum() const { return value; }
	};
	
	template<>
	struct Parser<PipelineCullModeEnum>
	{
		static Bool parse(StringView const str, PipelineCullModeEnum& value);
		static String to_string(PipelineCullModeEnum const& obj);
	};

	template<>
	struct Parser<PipelineCullMode>
	{
		inline static Bool parse(StringView const str, PipelineCullMode& value) { return Parser<PipelineCullModeEnum>::parse(str, value.value); }
		inline static String to_string(PipelineCullMode const& obj) { return Parser<PipelineCullModeEnum>::to_string(obj.value); }
	};
}
