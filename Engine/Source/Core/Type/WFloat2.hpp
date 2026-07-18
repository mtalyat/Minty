#pragma once

/**
 * @file WFloat2.h
 * @brief Definition of the WFloat2 type.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Library/GLM/GLM.hpp"

namespace Minty
{
    using WFloat2 = glm::vec<2, WFloat>;
}