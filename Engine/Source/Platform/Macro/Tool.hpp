#pragma once

/**
 * @file Tool.hpp
 * @brief Common utility functions for the platform.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"

#define MINTY_MAKE_VERSION(major, minor, patch) (((static_cast<UInt32>(major)) << 22U) | ((static_cast<UInt32>(minor)) << 12U) | (static_cast<UInt32>(patch)))