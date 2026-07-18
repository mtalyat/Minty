#pragma once

/**
 * @file WInt4.h
 * @brief Definition of the WInt4 type.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Library/GLM/GLM.hpp"

namespace Minty
{
    using WInt4 = glm::vec<4, WInt>;
}