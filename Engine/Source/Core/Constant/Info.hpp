#pragma once

/**
 * @file Info.h
 * @brief Information for the engine.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Platform/Macro/Tool.hpp"

namespace Minty
{
    constexpr Char const* MINTY_NAME = "Minty";

    constexpr Char const* MINTY_ENGINE_NAME = "Minty Engine";

    constexpr UInt32 MINTY_VERSION = MINTY_MAKE_VERSION(0, 1, 0);
}