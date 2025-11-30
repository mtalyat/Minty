#ifndef MINTY_RENDER_CAMERADATA_H
#define MINTY_RENDER_CAMERADATA_H

/**
 * @file CameraData.h
 * @brief Header file defining the CameraData struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Math.h"
#include "Minty/Data/Pointer.h"

namespace Minty
{
	class Camera;
	class Viewport;

	/**
	 * @brief Holds information needed for a Camera for rendering.
	 */
	struct CameraData
	{
		/**
		 * @brief The position of the Camera.
		 */
		Float3 position = Float3();

		/**
		 * @brief The rotation of the Camera.
		 */
		Quaternion rotation = Math::identity<Quaternion>();

		/**
		 * @brief The Camera data.
		 */
		Ref<Camera> camera = nullptr;

		/**
		 * @brief The view to render the Camera to.
		 */
		Ref<Viewport> viewport = nullptr;

		/**
		 * @brief Gets the transformation matrix for the Camera.
		 * @return The Matrix.
		 */
		Matrix4 get_transformation_matrix() const;
	};
}

#endif // MINTY_RENDER_CAMERADATA_H