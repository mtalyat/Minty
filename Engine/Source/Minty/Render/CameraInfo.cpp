#include "pch.h"
#include "CameraInfo.h"
#include "Minty/Core/Math.h"

using namespace Minty;

Matrix4 Minty::CameraInfo::get_transformation_matrix() const
{
    Matrix4 view = glm::lookAtLH(position, position + Math::forward(rotation), Math::UP);

    // TODO: don't use lookat
    // maybe invert global?

	// get projection
	Matrix4 proj;
	switch (camera->get_perspective())
	{
	case Perspective::Perspective:
		proj = glm::perspectiveLH(camera->get_fov(), camera->get_aspect_ratio(), camera->get_near_plane(), camera->get_far_plane());
		break;
	case Perspective::Orthographic:
	{
		float orthoHeight = camera->get_size();
		float orthoWidth = camera->get_size() * camera->get_aspect_ratio();

		float left = -orthoWidth * 0.5f;
		float right = orthoWidth * 0.5f;
		float bottom = -orthoHeight * 0.5f;
		float top = orthoHeight * 0.5f;

		proj = glm::orthoLH(left, right, bottom, top, camera->get_near_plane(), camera->get_far_plane());
		break;
	}
	default:
		MINTY_ERROR("Unrecognized Camera perspective.");
		return Math::identity<Matrix4>();
		break;
	}
	
	// flip Y axis
	proj[1][1] *= -1.0f;

	// multiply together
	Matrix4 transformMatrix = proj * view;

	return transformMatrix;
}
