#pragma once

/**
 * @file UInt4.h
 * @brief Definition of the UInt4 type.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Library/GLM/GLM.hpp"

namespace Minty
{
    using UInt4 = glm::uvec4;
}

namespace std
{
    template <>
    struct hash<Minty::UInt4>
    {
        std::size_t operator()(Minty::UInt4 const &v) const noexcept
        {
            std::size_t h1 = std::hash<Minty::UInt>{}(v.x);
            std::size_t h2 = std::hash<Minty::UInt>{}(v.y);
            std::size_t h3 = std::hash<Minty::UInt>{}(v.z);
            std::size_t h4 = std::hash<Minty::UInt>{}(v.w);
            return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
        }
    };
}