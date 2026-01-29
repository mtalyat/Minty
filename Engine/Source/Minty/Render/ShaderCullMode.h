#ifndef MINTY_RENDER_SHADERCULLMODE_H
#define MINTY_RENDER_SHADERCULLMODE_H

/**
 * @file ShaderCullMode.h
 * @brief Header file defining the ShaderCullMode enum.
 * @author Mitchell Talyat
 */

#include "Minty/Serialization/Parser.h"

namespace Minty
{
	/**
	 * @brief Determines how the Shader culls faces.
	 */
	enum class ShaderCullMode
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
	};
	
	template<>
	struct Parser<ShaderCullMode>
	{
		static Bool parse(StringView const str, ShaderCullMode& value);
		static String to_string(ShaderCullMode const& obj);
	};
}

#endif // MINTY_RENDER_SHADERCULLMODE_H