#include "pch.h"
#include "CameraInfo.h"

using namespace Minty;

Matrix4 Minty::CameraInfo::get_transformation_matrix() const
{
    Matrix4 view = glm::lookAt(position, position + Math::forward(rotation), Float3(0.0f, 1.0f, 0.0f));

    // TODO: don't use lookat
    // maybe invert global?

	// get projection
	Matrix4 proj;
	switch (camera.get_perspective())
	{
	case Perspective::Perspective:
		proj = glm::perspective(camera.get_fov(), camera.get_aspect_ratio(), camera.get_near_plane(), camera.get_far_plane());
		break;
	case Perspective::Orthographic:
	{
		float orthoHeight = camera.get_size();
		float orthoWidth = camera.get_size() * camera.get_aspect_ratio();

		float left = -orthoWidth * 0.5f;
		float right = orthoWidth * 0.5f;
		float bottom = -orthoHeight * 0.5f;
		float top = orthoHeight * 0.5f;

		proj = glm::ortho(left, right, bottom, top, camera.get_near_plane(), camera.get_far_plane());
		break;
	}
	default:
		MINTY_ERROR("Unrecognized Camera perspective.");
		return Math::identity<Matrix4>();
		break;
	}

	// multiply together
	Matrix4 transformMatrix = proj * view;

	return transformMatrix;
}
