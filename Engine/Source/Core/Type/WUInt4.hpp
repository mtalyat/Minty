#pragma once

/**
 * @file WUInt4.h
 * @brief Definition of the WUInt4 type.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Library/GLM/GLM.hpp"

namespace Minty
{
    using WUInt4 = glm::vec<4, WUInt>;
}