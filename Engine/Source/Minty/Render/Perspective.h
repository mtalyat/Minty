#ifndef MINTY_RENDER_PERSPECTIVE_H
#define MINTY_RENDER_PERSPECTIVE_H

/**
 * @file Perspective.h
 * @brief Header file defining the Perspective enum.
 * @author Mitchell Talyat
 */

#include "Minty/Serialization/Parser.h"

namespace Minty
{
	/**
	 * @brief The perspective type for a Camera.
	 */
	enum class Perspective
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
	};
	
	template<>
	struct Parser<Perspective>
	{
		static Bool parse(StringView const str, Perspective& value);
		static String to_string(Perspective const& obj);
	};
}

#endif // MINTY_RENDER_PERSPECTIVE_H