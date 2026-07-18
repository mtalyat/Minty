#pragma once

#include "Platform/Type/Primitive.hpp"

namespace Minty
{
    enum class EntityHandle : UInt {};

    constexpr EntityHandle INVALID_ENTITY = EntityHandle(0);
}