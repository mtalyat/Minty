#include "pch.h"
#include "Math.h"

using namespace Minty;
using namespace Minty::Math;

Float3 Minty::Math::normalize(Float3 const& value)
{
	// edge case for zero vector
	if (value.x == 0.0f && value.y == 0.0f && value.z == 0.0f)
	{
		return Float3(0.0f, 0.0f, 0.0f);
	}

	return glm::normalize(value);
}

Float Minty::Math::magnitude(Float3 const& value)
{
	return glm::length(value);
}

Float3 Minty::Math::forward(Quaternion const& value)
{
	return glm::normalize(value * Float3(0.0f, 0.0f, 1.0f));
}

Float3 Minty::Math::backward(Quaternion const& value)
{
	return glm::normalize(value * Float3(0.0f, 0.0f, -1.0f));
}

Float3 Minty::Math::up(Quaternion const& value)
{
	return glm::normalize(value * Float3(0.0f, 1.0f, 0.0f));
}

Float3 Minty::Math::down(Quaternion const& value)
{
	return glm::normalize(value * Float3(0.0f, -1.0f, 0.0f));
}

Float3 Minty::Math::right(Quaternion const& value)
{
	return glm::normalize(value * Float3(1.0f, 0.0f, 0.0f));
}

Float3 Minty::Math::left(Quaternion const& value)
{
	return glm::normalize(value * Float3(-1.0f, 0.0f, 0.0f));
}

Quaternion Minty::Math::angle_axis(Float const angle, Float3 const& axis)
{
	return glm::angleAxis(angle, axis);
}

Float3 Minty::Math::to_euler(Quaternion const& value)
{
	return glm::eulerAngles(value);
}

Quaternion Minty::Math::from_euler(Float3 const& value)
{
	Quaternion q = angle_axis(value.y, Float3(0.0f, 1.0f, 0.0f));	// Yaw (Y)
	q = angle_axis(value.x, Float3(1.0f, 0.0f, 0.0f)) * q;			// Pitch (X)
	q = angle_axis(value.z, Float3(0.0f, 0.0f, 1.0f)) * q;			// Roll (Z)
	return q;
}

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