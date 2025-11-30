#ifndef MINTY_RENDER_MATERIALINFO_H
#define MINTY_RENDER_MATERIALINFO_H

/**
 * @file MaterialInfo.h
 * @brief Header file defining the MaterialInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Data/Cargo.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/UUID.h"

namespace Minty
{
    class MaterialTemplate;

    /**
	 * @brief Arguments for a Material.
	 */
	struct MaterialInfo
	{
		/**
		 * @brief The ID.
		 */
		UUID id = UUID();

		/**
		 * @brief The MaterialTemplate for this Material.
		 */
		Ref<MaterialTemplate> materialTemplate = nullptr;

		/**
		 * @brief The values of this Material. These override the default values in the MaterialTemplate.
		 */
		Cargo values;

		/**
		 * @brief The stencil value for this Material. This requires this Material's Shader to have stencil testing enabled.
		 */
		UInt stencil = 0;
	};
}

#endif // MINTY_RENDER_MATERIALINFO_H