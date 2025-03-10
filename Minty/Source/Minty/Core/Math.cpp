#include "pch.h"
#include "Math.h"

using namespace Minty;
using namespace Minty::Math;

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
	return glm::normalize(value * Float3(0.0f, -1.0f, 0.0f));
}

Float3 Minty::Math::down(Quaternion const& value)
{
	return glm::normalize(value * Float3(0.0f, 1.0f, 0.0f));
}

Float3 Minty::Math::right(Quaternion const& value)
{
	return glm::normalize(value * Float3(1.0f, 0.0f, 0.0f));
}

Float3 Minty::Math::left(Quaternion const& value)
{
	return glm::normalize(value * Float3(-1.0f, 0.0f, 0.0f));
}

Float3 Minty::Math::to_euler(Quaternion const& value)
{
	Float3 euler = glm::eulerAngles(value) * RAD2DEG;
	euler = Float3(euler.x, euler.y, euler.z);

	return euler;
}

Quaternion Minty::Math::from_euler(Float3 const& value)
{
	return Quaternion(value * DEG2RAD);
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