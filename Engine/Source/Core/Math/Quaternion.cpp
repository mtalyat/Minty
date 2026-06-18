#include "pch.h"
#include "Quaternion.h"
#include "Matrix3x3.h"

using namespace Minty;
using namespace Minty::Math;

Quaternion Minty::Math::inverse(Quaternion const& value)
{
    return glm::inverse(value);
}

Float3 Minty::Math::forward(Quaternion const& value)
{
	return glm::normalize(value * FORWARD);
}

Float3 Minty::Math::backward(Quaternion const& value)
{
	return glm::normalize(value * BACKWARD);
}

Float3 Minty::Math::up(Quaternion const& value)
{
	return glm::normalize(value * UP);
}

Float3 Minty::Math::down(Quaternion const& value)
{
	return glm::normalize(value * DOWN);
}

Float3 Minty::Math::right(Quaternion const& value)
{
	return glm::normalize(value * RIGHT);
}

Float3 Minty::Math::left(Quaternion const& value)
{
	return glm::normalize(value * LEFT);
}

Quaternion Minty::Math::angle_axis(Float const angle, Float3 const& axis)
{
	return glm::angleAxis(angle, axis);
}

Quaternion Minty::Math::look_at(Float3 const& eye, Float3 const& target, Float3 const& up)
{
	Float3 forward = glm::normalize(target - eye);
	Float3 right = glm::normalize(glm::cross(up, forward));
	Float3 newUp = glm::cross(forward, right);

	Matrix3x3 rotationMatrix = {
		right.x, right.y, right.z,
		newUp.x, newUp.y, newUp.z,
		forward.x, forward.y, forward.z
	};

	return glm::quat_cast(rotationMatrix);
}

Float3 Minty::Math::to_euler(Quaternion const& value)
{
	Float3 euler = glm::eulerAngles(value);
	return euler;
}

Quaternion Minty::Math::to_cartesian(Float3 const& value)
{
	Quaternion q = angle_axis(value.y, UP);	// Yaw (Y)
	q = angle_axis(value.x, RIGHT) * q;			// Pitch (X)
	q = angle_axis(value.z, FORWARD) * q;			// Roll (Z)
	return q;
}