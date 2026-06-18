#ifndef MINTY_RENDER_MATERIALINFO_H
#define MINTY_RENDER_MATERIALINFO_H

/**
 * @file MaterialInfo.h
 * @brief Header file defining the MaterialInfo struct.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"
#include "Core/Data/Cargo.h"
#include "Render/Type/Handle.h"

namespace Minty
{
    /**
	 * @brief Arguments for a Material.
	 */
	struct MaterialInfo
	{
		/**
		 * @brief The Pipeline for this Material.
		 */
		PipelineHandle pipeline = INVALID_HANDLE;

		/**
		 * @brief The values of this Material. These override the default values in the Pipeline.

		 */
		Cargo values = {};

		/**
		 * @brief The stencil value for this Material. This requires this Material's Shader to have stencil testing enabled.
		 */
		UInt stencil = 0;
	};
}

#endif // MINTY_RENDER_MATERIALINFO_H