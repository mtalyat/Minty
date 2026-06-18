#pragma once

/**
 * @file WUInt4.h
 * @brief Definition of the WUInt4 type.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"
#include "Library/GLM/GLM.h"

namespace Minty
{
    using WUInt4 = glm::vec<4, WUInt>;
}