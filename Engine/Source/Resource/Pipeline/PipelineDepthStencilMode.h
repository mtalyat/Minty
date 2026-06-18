#pragma once

/**
 * @file PipelineDepthStencilMode.h
 * @brief Header file defining the PipelineDepthStencilMode enum.
 * @author Mitchell Talyat
 */

#include "Core/Type/Enum.h"
#include "Core/Serialize/Parser.h"

namespace Minty
{
	/**
	 * @brief Determines how depth/stencil buffering is handled.
	 */
	enum class PipelineDepthStencilModeEnum
	{
		/**
		 * @brief Do not use depth/stencil buffer.
		 */
		None,

		/**
		 * @brief Write to the depth/stencil buffer.
		 */
		Write,

		/**
		 * @brief Test the depth/stencil buffer.
		 */
		Test,

		Count
	};

	MINTY_ENABLE_ENUM_OPERATORS(PipelineDepthStencilModeEnum)

	struct PipelineDepthStencilMode
	{
		PipelineDepthStencilModeEnum mode;

		constexpr PipelineDepthStencilMode() : mode(PipelineDepthStencilModeEnum::None) {}
		constexpr PipelineDepthStencilMode(PipelineDepthStencilModeEnum const mode) : mode(mode) {}
		constexpr operator PipelineDepthStencilModeEnum() const { return mode; }
	};
	
	template<>
	struct Parser<PipelineDepthStencilModeEnum>
	{
		static Bool parse(StringView const str, PipelineDepthStencilModeEnum& value);
		static String to_string(PipelineDepthStencilModeEnum const& obj);
	};

	template<>
	struct Parser<PipelineDepthStencilMode>
	{
		inline static Bool parse(StringView const str, PipelineDepthStencilMode& value) { return Parser<PipelineDepthStencilModeEnum>::parse(str, value.mode); }
		inline static String to_string(PipelineDepthStencilMode const& obj) { return Parser<PipelineDepthStencilModeEnum>::to_string(obj.mode); }
	};
}
