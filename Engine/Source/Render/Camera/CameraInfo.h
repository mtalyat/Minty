#pragma once

/**
 * @file CameraInfo.h
 * @brief Header file defining the CameraInfo struct.
 * @author Mitchell Talyat
 */

#include "CameraPerspective.h"
#include "Platform/Type/Primitive.h"
#include "Core/Type/Color.h"
#include "Core/Constant/Default.h"
#include "Core/Constant/Invalid.h"
#include "Render/Type/Handle.h"
#include "Layer/LayerMask/LayerMask.h"

namespace Minty
{
    class RenderTargetResource;

    /**
	 * @brief The arguments for a Camera.
	 */
	struct CameraInfo
	{
		/**
		 * @brief The perspective.
		 */
		CameraPerspective perspective = CameraPerspectiveEnum::Default;

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
		LayerMask mask = MASK_ALL;

		/**
		 * @brief The RenderTarget to render to.
		 */
		RenderTargetHandle renderTarget = INVALID_HANDLE;

		/**
		 * @brief The Viewport to render to. Leave as INVALID_HANDLE to use the default viewport.
		 */
		ViewportHandle viewport = INVALID_HANDLE;
	};
}
