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

		void serialize(Writer& writer) const override;
		Bool deserialize(Reader& reader) override;
	};
}

#endif // MINTY_COMPONENT_CAMERACOMPONENT_H