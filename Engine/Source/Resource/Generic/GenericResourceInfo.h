#pragma once

/**
 * @file GenericResourceInfo.h
 * @brief Header file defining the GenericResourceInfo struct.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"
#include "Core/Data/ConstantContainer.h"

namespace Minty
{
	/**
	 * @brief Arguments for creating a GenericResource.
	 */
	struct GenericResourceInfo
	{
		/**
		 * @brief The data for the resource.
		 */
		ConstantContainer data = {};
	};
}
