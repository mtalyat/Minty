#pragma once

/**
 * @file Int2.hpp
 * @brief Definition of the Int2 type.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Library/GLM/GLM.hpp"

namespace Minty
{
    using Int2 = glm::ivec2;
}

namespace std
{
    template <>
    struct hash<Minty::Int2>
    {
        std::size_t operator()(Minty::Int2 const &v) const noexcept
        {
            std::size_t h1 = std::hash<Minty::Int>{}(v.x);
            std::size_t h2 = std::hash<Minty::Int>{}(v.y);
            return h1 ^ (h2 << 1);
        }
    };
}