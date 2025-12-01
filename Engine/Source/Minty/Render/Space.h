#ifndef MINTY_RENDER_SPACE_H
#define MINTY_RENDER_SPACE_H

/**
 * @file Space.h
 * @brief Header file defining the Space enum.
 * @author Mitchell Talyat
 */

#include "Minty/Serialization/Parse.h"
#include "Minty/Serialization/ToString.h"

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

	String to_string(Space const obj);
	Space parse_to_space(String const& string);
	Bool parse_try_space(String const& string, Space& value);
	template<>
	inline Space parse_to<Space>(String const& string) { return parse_to_space(string); }
	template<>
	inline Bool parse_try<Space>(String const& string, Space& value) { return parse_try_space(string, value); }
}

#endif // MINTY_RENDER_SPACE_H