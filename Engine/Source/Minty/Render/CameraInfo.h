#ifndef MINTY_RENDER_CAMERAINFO_H
#define MINTY_RENDER_CAMERAINFO_H

/**
 * @file CameraInfo.h
 * @brief Header file defining the CameraInfo struct.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/Color.h"
#include "Minty/Data/Pointer.h"
#include "Minty/Data/UUID.h"
#include "Minty/Render/Perspective.h"

namespace Minty
{
    class RenderTarget;

    /**
	 * @brief The arguments for a Camera.
	 */
	struct CameraInfo
	{
		/**
		 * @brief The Asset ID.
		 */
		UUID id = UUID();

		/**
		 * @brief The perspective.
		 */
		Perspective perspective = Perspective::Perspective;

		/**
		 * @brief The Field of View.
		 */
		Float fov = 45.0f;

		/**
		 * @brief The near plane. Nothing closer than this distance is rendered.
		 */
		Float nearPlane = 0.1f;

		/**
		 * @brief The far plane. Nothing further than this distance is rendered.
		 */
		Float farPlane = 100.0f;

		/**
		 * @brief The clear color.
		 */
		Color color = Color::black();

		/**
		 * @brief The aspect ratio.
		 */
		Float aspectRatio = 16.0f / 9.0f;

		/**
		 * @brief The size/height of the Camera view. Used for orthographic cameras.
		 */
		Float size = 5.0f;

		/**
		 * @brief The layers to render.
		 */
		Layer layer = LAYER_MASK_ALL;

		/**
		 * @brief The RenderTarget to render to.
		 */
		Ref<RenderTarget> renderTarget = nullptr;
	};
}

#endif // MINTY_RENDER_CAMERAINFO_H