#pragma once

/**
 * @file Float4.h
 * @brief Definition of the Float4 type.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"
#include "Library/GLM/GLM.h"

namespace Minty
{
    using Float4 = glm::vec4;
}

namespace std
{
    template <>
    struct hash<Minty::Float4>
    {
        std::size_t operator()(Minty::Float4 const &v) const noexcept
        {
            std::size_t h1 = std::hash<Minty::Float>{}(v.x);
            std::size_t h2 = std::hash<Minty::Float>{}(v.y);
            std::size_t h3 = std::hash<Minty::Float>{}(v.z);
            std::size_t h4 = std::hash<Minty::Float>{}(v.w);
            return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3);
        }
    };
}