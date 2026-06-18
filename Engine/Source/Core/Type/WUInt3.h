#pragma once

/**
 * @file WUInt3.h
 * @brief Definition of the WUInt3 type.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"
#include "Library/GLM/GLM.h"

namespace Minty
{
    using WUInt3 = glm::vec<3, WUInt>;
}