#ifndef MINTY_RENDER_PERSPECTIVE_H
#define MINTY_RENDER_PERSPECTIVE_H

/**
 * @file Perspective.h
 * @brief Header file defining the Perspective enum.
 * @author Mitchell Talyat
 */

#include "Minty/Serialization/Parse.h"
#include "Minty/Serialization/ToString.h"

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

	String to_string(Perspective const obj);
	Perspective parse_to_perspective(String const& string);
	Bool parse_try_perspective(String const& string, Perspective& value);
	template<>
	inline Perspective parse_to<Perspective>(String const& string) { return parse_to_perspective(string); }
	template<>
	inline Bool parse_try<Perspective>(String const& string, Perspective& value) { return parse_try_perspective(string, value); }
}

#endif // MINTY_RENDER_PERSPECTIVE_H