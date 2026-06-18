#pragma once

/**
 * @file Float3.h
 * @brief Definition of the Float3 type.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"
#include "Library/GLM/GLM.h"

namespace Minty
{
    using Float3 = glm::vec3;
}

namespace std
{
    template <>
    struct hash<Minty::Float3>
    {
        std::size_t operator()(Minty::Float3 const &v) const noexcept
        {
            std::size_t h1 = std::hash<Minty::Float>{}(v.x);
            std::size_t h2 = std::hash<Minty::Float>{}(v.y);
            std::size_t h3 = std::hash<Minty::Float>{}(v.z);
            return h1 ^ (h2 << 1) ^ (h3 << 2);
        }
    };
}