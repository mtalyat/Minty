#pragma once

/**
 * @file CameraComponent.h
 * @brief Header file defining the CameraComponent structure.
 * @author Mitchell Talyat
 */

#include "Render/Camera/Camera.hpp"
#include "Core/Data/Unique.hpp"
#include "Core/Serialize/Serializer.hpp"

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
		Unique<Camera> camera = nullptr;
	};

	template<>
	struct Serializer<CameraComponent>
	{
		static void serialize(Writer& writer, CameraComponent const& value);
		static Bool deserialize(Reader& reader, CameraComponent& value);
	};
}
