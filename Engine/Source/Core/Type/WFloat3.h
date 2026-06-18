#pragma once

/**
 * @file WFloat3.h
 * @brief Definition of the WFloat3 type.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"
#include "Library/GLM/GLM.h"

namespace Minty
{
    using WFloat3 = glm::vec<3, WFloat>;
}