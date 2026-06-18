#pragma once

#include "Platform/Type/Primitive.h"

namespace Minty
{
    enum class EntityHandle : UInt {};

    constexpr EntityHandle INVALID_ENTITY = EntityHandle(0);
}