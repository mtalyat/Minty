#pragma once

/**
 * @file WInt4.h
 * @brief Definition of the WInt4 type.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"
#include "Library/GLM/GLM.h"

namespace Minty
{
    using WInt4 = glm::vec<4, WInt>;
}