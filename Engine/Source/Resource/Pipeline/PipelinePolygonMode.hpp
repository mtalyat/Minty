#pragma once

/**
 * @file PipelinePolygonMode.hpp
 * @brief Header file defining the PipelinePolygonMode enum.
 * @author Mitchell Talyat
 */

#include "Core/Type/Enum.hpp"
#include "Core/Serialize/Parser.hpp"

namespace Minty
{
	/**
	 * @brief Determines how the polygons are being drawn.
	 */
	enum class PipelinePolygonModeEnum
	{
		/**
		 * @brief Invalid.
		 */
		Undefined = 0,

		/**
		 * @brief Fill the polygon.
		 */
		Fill = 1,

		/**
		 * @brief Draw the outlines of the polygon.
		 */
		Line = 2,

		/**
		 * @brief Draw the points of the polygon.
		 */
		Point = 3,

		Count,

		Default = Fill,
	};

	MINTY_ENABLE_ENUM_OPERATORS(PipelinePolygonModeEnum)

	struct PipelinePolygonMode
	{
		PipelinePolygonModeEnum value;

		constexpr PipelinePolygonMode() : value(PipelinePolygonModeEnum::Default) {}
		constexpr PipelinePolygonMode(PipelinePolygonModeEnum v) : value(v) {}
		constexpr operator PipelinePolygonModeEnum() const { return value; }
	};
	
	template<>
	struct Parser<PipelinePolygonModeEnum>
	{
		static Bool parse(StringView const str, PipelinePolygonModeEnum& value);
		static String to_string(PipelinePolygonModeEnum const& obj);
	};

	template<>
	struct Parser<PipelinePolygonMode>
	{
		inline static Bool parse(StringView const str, PipelinePolygonMode& value) { return Parser<PipelinePolygonModeEnum>::parse(str, value.value); }
		inline static String to_string(PipelinePolygonMode const& obj) { return Parser<PipelinePolygonModeEnum>::to_string(obj.value); }
	};
}
