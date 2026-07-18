#pragma once

/**
 * @file GenericResourceInfo.h
 * @brief Header file defining the GenericResourceInfo struct.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Core/Data/ConstantContainer.hpp"

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
