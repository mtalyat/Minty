#pragma once

/**
 * @file WInt3.hpp
 * @brief Definition of the WInt3 type.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Library/GLM/GLM.hpp"

namespace Minty
{
    using WInt3 = glm::vec<3, WInt>;
}