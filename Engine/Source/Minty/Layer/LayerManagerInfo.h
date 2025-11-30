#ifndef MINTY_LAYER_LAYERMANAGERINFO_H
#define MINTY_LAYER_LAYERMANAGERINFO_H

/**
 * @file LayerManagerInfo.h
 * @brief Header file for the LayerManagerInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Constant.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/String.h"
#include "Minty/Data/Tuple.h"
#include "Minty/Data/Vector.h"

namespace Minty
{
    /**
     * @brief Configuration information for creating a LayerManager.
     */
	struct LayerManagerInfo
	{
        /**
         * @brief The layer collision matrix data.
         * Each tuple contains the name of the layer, the layer itself, and the layer mask of the layers it collides with.
         * Each bit, starting with the least significant bit, corresponds to the layer index of the layer it collides with.
         */
		Vector<Tuple<String, Layer, Layer>> layerCollisions = {
			{ "None", LAYER_NONE, ~LAYER_MASK_ALL },
			{ "Default", LAYER_DEFAULT, LAYER_MASK_ALL }
		};
	};
}

#endif // MINTY_LAYER_LAYERMANAGERINFO_H