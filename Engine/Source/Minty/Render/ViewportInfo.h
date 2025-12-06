#ifndef MINTY_RENDER_VIEWPORTINFO_H
#define MINTY_RENDER_VIEWPORTINFO_H

/**
 * @file ViewportInfo.h
 * @brief Header file defining the ViewportInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Core/Math.h"
#include "Minty/Data/UUID.h"

namespace Minty
{
    /**
	 * @brief Arguments for a Viewport.
	 */
	struct ViewportInfo
	{
		/**
		 * @brief The ID.
		 */
		UUID id = {};

		/**
		 * @brief The position of the view.
		 */
		Int2 viewPosition = { 0, 0 };

		/**
		 * @brief The size of the view.
		 */
		UInt2 viewSize = { 0, 0 };

		/**
		 * @brief The position of the mask.
		 */
		Int2 maskPosition = { 0, 0 };

		/**
		 * @brief The size of the mask.
		 */
		UInt2 maskSize = { 0, 0 };

		/**
		 * @brief The minimum depth of the viewport.
		 */
		Float minDepth = 0.0f;

		/**
		 * @brief The maximum depth of the viewport.
		 */
		Float maxDepth = 1.0f;
	};
}

#endif // MINTY_RENDER_VIEWPORTINFO_H