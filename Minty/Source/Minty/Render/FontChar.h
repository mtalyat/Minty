#pragma once
#include "Minty/Core/Types.h"

namespace Minty
{
	/// <summary>
	/// Holds data for a single character in a Font.
	/// </summary>
	struct FontChar
	{
		/// <summary>
		/// The character.
		/// </summary>
		Char id;

		/// <summary>
		/// The x position within the texture.
		/// </summary>
		Float x;

		/// <summary>
		/// The y position within the texture.
		/// </summary>
		Float y;

		/// <summary>
		/// The width of the character in the texture.
		/// </summary>
		Float width;

		/// <summary>
		/// The height of the character in the texture.
		/// </summary>
		Float height;

		/// <summary>
		/// The x offset to apply when rendering this character.
		/// </summary>
		Float xOffset;
		
		/// <summary>
		/// The y offset to apply when rendering this character.
		/// </summary>
		Float yOffset;

		/// <summary>
		/// The distance to advance the cursor after rendering this character.
		/// </summary>
		Float xAdvance;
	};
}