#include "pch.hpp"
#include "Math.hpp"
#include <random>

using namespace Minty;
using namespace Minty::Math;

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
