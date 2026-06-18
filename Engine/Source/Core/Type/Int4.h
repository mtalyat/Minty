#pragma once

/**
 * @file Int4.h
 * @brief Definition of the Int4 type.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"
#include "Library/GLM/GLM.h"

namespace Minty
{
    using Int4 = glm::ivec4;
}

namespace std
{
    template <>
    struct hash<Minty::Int4>
    {
        std::size_t operator()(Minty::Int4 const &v) const noexcept
        {
            std::size_t h1 = std::hash<Minty::Int>{}(v.x);
            std::size_t h2 = std::hash<Minty::Int>{}(v.y);
            std::size_t h3 = std::hash<Minty::Int>{}(v.z);
            std::size_t h4 = std::hash<Minty::Int>{}(v.w);
            return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
        }
    };
}