#pragma once

/**
 * @file PipelinePrimitiveTopology.h
 * @brief Header file defining the PipelinePrimitiveTopology enum.
 * @author Mitchell Talyat
 */

#include "Core/Type/Enum.hpp"
#include "Core/Serialize/Parser.hpp"

namespace Minty
{
	/**
	 * @brief Determines the type of primitive topology to use when rendering the vertex data.
	 */
	enum class PipelinePrimitiveTopologyEnum
	{
		/**
		 * @brief Invalid.
		 */
		Undefined = 0,

		/**
		 * @brief The vertex data is a list of points.
		 */
		PointList = 1,

		/**
		 * @brief The vertex data is a list of lines. Every 2 vertices is a line.
		 */
		LineList = 2,

		/**
		 * @brief The vertex data is a line strip.
		 */
		LineStrip = 3,

		/**
		 * @brief The vertex data is a list of triangles. Every 3 vertices is a triangle.
		 */
		TriangleList = 4,

		/**
		 * @brief The vertex data is a triangle strip.
		 */
		TriangleStrip = 5,

		/**
		 * @brief The vertex data is a triangle fan. The first vertex is the center and every 2 vertices is a triangle.
		 */
		TriangleFan = 6,

		Count,

		Default = TriangleList,
	};

	MINTY_ENABLE_ENUM_OPERATORS(PipelinePrimitiveTopologyEnum)

	struct PipelinePrimitiveTopology
	{
		PipelinePrimitiveTopologyEnum value;

		constexpr PipelinePrimitiveTopology() : value(PipelinePrimitiveTopologyEnum::Default) {}
		constexpr PipelinePrimitiveTopology(PipelinePrimitiveTopologyEnum v) : value(v) {}
		constexpr operator PipelinePrimitiveTopologyEnum() const { return value; }
	};
	
	template<>
	struct Parser<PipelinePrimitiveTopologyEnum>
	{
		static Bool parse(StringView const str, PipelinePrimitiveTopologyEnum& value);
		static String to_string(PipelinePrimitiveTopologyEnum const& obj);
	};

	template<>
	struct Parser<PipelinePrimitiveTopology>
	{
		inline static Bool parse(StringView const str, PipelinePrimitiveTopology& value) { return Parser<PipelinePrimitiveTopologyEnum>::parse(str, value.value); }
		inline static String to_string(PipelinePrimitiveTopology const& obj) { return Parser<PipelinePrimitiveTopologyEnum>::to_string(obj.value); }
	};
}
