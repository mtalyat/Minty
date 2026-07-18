#pragma once

/**
 * @file WUInt3.h
 * @brief Definition of the WUInt3 type.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Library/GLM/GLM.hpp"

namespace Minty
{
    using WUInt3 = glm::vec<3, WUInt>;
}