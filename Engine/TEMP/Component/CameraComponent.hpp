#pragma once

/**
 * @file CameraComponent.hpp
 * @brief Header file defining the CameraComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Render/Camera.h"

namespace Minty
{
	/**
	 * @brief A component that holds a Camera.
	 */
	struct CameraComponent	
	{
		/**
		 * @brief The Camera.
		 */
		Ref<Camera> camera = nullptr;
	};

	template<>
	struct Serializer<CameraComponent>
	{
		static Bool serialize(Writer& writer, CameraComponent const& value);
		static Bool deserialize(Reader& reader, CameraComponent& value);
	};
}
