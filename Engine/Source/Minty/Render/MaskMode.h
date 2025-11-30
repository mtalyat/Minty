#ifndef MINTY_RENDER_MASKMODE_H
#define MINTY_RENDER_MASKMODE_H

namespace Minty
{
	/**
	 * @brief Determines how masking is handled.
	 */
	enum class MaskMode
	{
		/**
		 * @brief No masking is applied.
		 */
		None,

		/**
		 * @brief Write to the mask.
		 */
		Write,

		/**
		 * @brief Test the mask.
		 */
		Test
	};
}

#endif // MINTY_RENDER_MASKMODE_H