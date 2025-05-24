#pragma once
#include "Minty/Core/Math.h"
#include "Minty/Render/Camera.h"
#include "Minty/Render/Viewport.h"

namespace Minty
{
	/// <summary>
	/// Holds information needed for a Camera for rendering.
	/// </summary>
	struct CameraInfo
	{
		/// <summary>
		/// The position of the Camera.
		/// </summary>
		Float3 position = Float3();

		/// <summary>
		/// The rotation of the Camera.
		/// </summary>
		Quaternion rotation = Math::identity<Quaternion>();

		/// <summary>
		/// The Camera data.
		/// </summary>
		Ref<Camera> camera = nullptr;

		/// <summary>
		/// The view to render the Camera to.
		/// </summary>
		Ref<Viewport> viewport = nullptr;

		/// <summary>
		/// Gets the transformation matrix for the Camera.
		/// </summary>
		/// <returns>The Matrix.</returns>
		Matrix4 get_transformation_matrix() const;
	};
}