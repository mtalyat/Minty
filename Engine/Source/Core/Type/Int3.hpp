#pragma once

/**
 * @file Int3.h
 * @brief Definition of the Int3 type.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Library/GLM/GLM.hpp"

namespace Minty
{
    using Int3 = glm::ivec3;
}

namespace std
{
    template <>
    struct hash<Minty::Int3>
    {
        std::size_t operator()(Minty::Int3 const &v) const noexcept
        {
            std::size_t h1 = std::hash<Minty::Int>{}(v.x);
            std::size_t h2 = std::hash<Minty::Int>{}(v.y);
            std::size_t h3 = std::hash<Minty::Int>{}(v.z);
            return h1 ^ (h2 << 1) ^ (h3 << 2);
        }
    };
}