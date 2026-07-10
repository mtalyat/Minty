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