#include "pch.h"
#include "Math.h"
#include <random>

using namespace Minty;
using namespace Minty::Math;

static std::random_device s_randomDevice;
static std::mt19937 s_randomEngine(s_randomDevice());
static std::mt19937_64 s_randomEngine64(s_randomDevice());
static std::uniform_real_distribution<Float> s_uniformDistributionFloat;
static std::uniform_int_distribution<Int> s_uniformDistributionInt;
static std::uniform_int_distribution<UInt> s_uniformDistributionUInt;
static std::uniform_real_distribution<WFloat> s_uniformDistributionDouble;
static std::uniform_int_distribution<WInt> s_uniformDistributionLong;
static std::uniform_int_distribution<WUInt> s_uniformDistributionULong;

Quaternion Minty::Math::inverse(Quaternion const &value)
{
    return glm::inverse(value);
}

Float3 Minty::Math::normalize(Float3 const &value)
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

	Matrix3 rotationMatrix = {
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

Float Minty::Math::random_float(Float const min, Float const max)
{
	std::uniform_real_distribution<Float> dist(min, max);
	return dist(s_randomEngine);
}

Float Minty::Math::random_float()
{
	return s_uniformDistributionFloat(s_randomEngine);
}

Int Minty::Math::random_int(Int const min, Int const max)
{
	std::uniform_int_distribution<Int> dist(min, max);
	return dist(s_randomEngine);
}

Int Minty::Math::random_int()
{
	return s_uniformDistributionInt(s_randomEngine);
}

UInt Minty::Math::random_uint(UInt const min, UInt const max)
{
	std::uniform_int_distribution<UInt> dist(min, max);
	return dist(s_randomEngine);
}

UInt Minty::Math::random_uint()
{
	return s_uniformDistributionUInt(s_randomEngine);
}

WFloat Minty::Math::random_double(WFloat const min, WFloat const max)
{
	std::uniform_real_distribution<WFloat> dist(min, max);
	return dist(s_randomEngine64);
}

WFloat Minty::Math::random_double()
{
	return s_uniformDistributionDouble(s_randomEngine64);
}

WInt Minty::Math::random_long(WInt const min, WInt const max)
{
	std::uniform_int_distribution<WInt> dist(min, max);
	return dist(s_randomEngine64);
}

WInt Minty::Math::random_long()
{
	return s_uniformDistributionLong(s_randomEngine64);
}

WUInt Minty::Math::random_ulong(WUInt const min, WUInt const max)
{
	std::uniform_int_distribution<WUInt> dist(min, max);
	return dist(s_randomEngine64);
}

WUInt Minty::Math::random_ulong()
{
	return s_uniformDistributionULong(s_randomEngine64);
}
