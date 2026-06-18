#pragma once

/**
 * @file WFloat4.h
 * @brief Definition of the WFloat4 type.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"
#include "Library/GLM/GLM.h"

namespace Minty
{
    using WFloat4 = glm::vec<4, WFloat>;
}