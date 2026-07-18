#pragma once

/**
 * @file UInt3.h
 * @brief Definition of the UInt3 type.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Library/GLM/GLM.hpp"

namespace Minty
{
    using UInt3 = glm::uvec3;
}

namespace std
{
    template <>
    struct hash<Minty::UInt3>
    {
        std::size_t operator()(Minty::UInt3 const &v) const noexcept
        {
            std::size_t h1 = std::hash<Minty::UInt>{}(v.x);
            std::size_t h2 = std::hash<Minty::UInt>{}(v.y);
            std::size_t h3 = std::hash<Minty::UInt>{}(v.z);
            return h1 ^ (h2 << 1) ^ (h3 << 2);
        }
    };
}