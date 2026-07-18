#include "pch.hpp"
#include "Matrix4x4.hpp"
#include "Matrix3x3.hpp"

using namespace Minty;
using namespace Minty::Math;

Matrix4 Minty::Math::to_matrix(Quaternion const& value)
{
	return glm::mat4_cast(value);
}

Matrix4 Minty::Math::translate(Matrix4 const& matrix, Float3 const value)
{
	return glm::translate(matrix, value);
}

Matrix4 Minty::Math::scale(Matrix4 const& matrix, Float3 const value)
{
	return glm::scale(matrix, value);
}

Matrix4 Minty::Math::rotate(Matrix4 const& matrix, Float const angle, Float3 const& axis)
{
	return glm::rotate(matrix, angle, axis);
}

Matrix4 Minty::Math::rotate(Matrix4 const& matrix, Quaternion const& value)
{
	return matrix * to_matrix(value);
}

Float3 Minty::Math::extract_position(Matrix4 const& value)
{
	return value[3];
}

Float3 Minty::Math::extract_scale(Matrix4 const& value)
{
	return Float3(glm::length(value[0]), glm::length(value[1]), glm::length(value[2]));
}

Quaternion Minty::Math::extract_rotation(Matrix4 const& value, Float3 const& scale)
{
	Matrix3 rotationMatrix{};
	if (scale.x == 0.0f)
	{
		rotationMatrix[0] = value[0];
	}
	else
	{
		rotationMatrix[0] = value[0] / scale.x;
	}
	if (scale.y == 0.0f)
	{
		rotationMatrix[1] = value[1];
	}
	else
	{
		rotationMatrix[1] = value[1] / scale.y;
	}
	if (scale.z == 0.0f)
	{
		rotationMatrix[2] = value[2];
	}
	else
	{
		rotationMatrix[2] = value[2] / scale.z;
	}

	return glm::quat_cast(rotationMatrix);
}

Quaternion Minty::Math::extract_rotation(Matrix4 const& value)
{
	return extract_rotation(value, extract_scale(value));
}

Matrix4 Minty::Math::perspective(Float const fov, Float const aspectRatio, Float const nearPlane, Float const farPlane)
{
    return glm::perspectiveLH(fov, aspectRatio, nearPlane, farPlane);
}

Matrix4 Minty::Math::orthographic(Float const size, Float const aspectRatio, Float const nearPlane, Float const farPlane)
{
	float const orthoHeight = size;
	float const orthoWidth = size * aspectRatio;

	float const left = -orthoWidth * 0.5f;
	float const right = orthoWidth * 0.5f;
	float const bottom = -orthoHeight * 0.5f;
	float const top = orthoHeight * 0.5f;

    return glm::orthoLH(left, right, bottom, top, nearPlane, farPlane);
}

Matrix4 Minty::Math::look_at(Float3 const &eye, Float3 const &target, Float3 const &up)
{
    return glm::lookAtLH(eye, target, up);
}
