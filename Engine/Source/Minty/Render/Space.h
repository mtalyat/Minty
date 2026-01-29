#ifndef MINTY_RENDER_SPACE_H
#define MINTY_RENDER_SPACE_H

/**
 * @file Space.h
 * @brief Header file defining the Space enum.
 * @author Mitchell Talyat
 */

#include "Minty/Serialization/Parser.h"

namespace Minty
{
	/**
	 * @brief Classifies the Space that an object is in.
	 */
	enum class Space
	{
		/**
		 * @brief Invalid space.
		 */
		Undefined,

		/**
		 * @brief 3D world space.
		 */
		D3,

		/**
		 * @brief 2D world space.
		 */
		D2,

		/**
		 * @brief User Interface space.
		 */
		UI,
	};
	
	template<>
	struct Parser<Space>
	{
		static Bool parse(StringView const str, Space& value);
		static String to_string(Space const& obj);
	};
}

#endif // MINTY_RENDER_SPACE_H