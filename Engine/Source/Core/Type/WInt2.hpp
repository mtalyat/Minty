#pragma once

/**
 * @file WInt2.h
 * @brief Definition of the WInt2 type.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Library/GLM/GLM.hpp"

namespace Minty
{
    using WInt2 = glm::vec<2, WInt>;
}