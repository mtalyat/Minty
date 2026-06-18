#pragma once

/**
 * @file WInt3.h
 * @brief Definition of the WInt3 type.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"
#include "Library/GLM/GLM.h"

namespace Minty
{
    using WInt3 = glm::vec<3, WInt>;
}