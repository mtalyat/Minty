#pragma once

/**
 * @file UInt2.h
 * @brief Definition of the UInt2 type.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"
#include "Library/GLM/GLM.h"

namespace Minty
{
    using UInt2 = glm::uvec2;
}

namespace std
{
    template <>
    struct hash<Minty::UInt2>
    {
        std::size_t operator()(Minty::UInt2 const &v) const noexcept
        {
            std::size_t h1 = std::hash<Minty::UInt>{}(v.x);
            std::size_t h2 = std::hash<Minty::UInt>{}(v.y);
            return h1 ^ (h2 << 1);
        }
    };
}