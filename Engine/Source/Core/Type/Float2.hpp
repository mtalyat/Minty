#pragma once

/**
 * @file Float2.h
 * @brief Definition of the Float2 type.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Library/GLM/GLM.hpp"

namespace Minty
{
    using Float2 = glm::vec2;
}

namespace std
{
    template <>
    struct hash<Minty::Float2>
    {
        std::size_t operator()(Minty::Float2 const &v) const noexcept
        {
            std::size_t h1 = std::hash<Minty::Float>{}(v.x);
            std::size_t h2 = std::hash<Minty::Float>{}(v.y);
            return h1 ^ (h2 << 1);
        }
    };
}