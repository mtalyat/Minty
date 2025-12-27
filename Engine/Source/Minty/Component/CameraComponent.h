#ifndef MINTY_COMPONENT_CAMERACOMPONENT_H
#define MINTY_COMPONENT_CAMERACOMPONENT_H

/**
 * @file CameraComponent.h
 * @brief Header file defining the CameraComponent structure.
 * @author Mitchell Talyat
 */

#include "Minty/Component/Component.h"
#include "Minty/Render/Camera.h"

namespace Minty
{
	/**
	 * @brief A component that holds a Camera.
	 */
	struct CameraComponent
		: public Component
	{
		/**
		 * @brief The Camera.
		 */
		Ref<Camera> camera = nullptr;
	};

	template<>
	struct Serializer<CameraComponent>
	{
		static void serialize(Writer& writer, CameraComponent const& value);
		static void deserialize(Reader& reader, CameraComponent& value);
	};
}

#endif // MINTY_COMPONENT_CAMERACOMPONENT_H