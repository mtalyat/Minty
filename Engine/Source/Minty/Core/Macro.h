#ifndef MINTY_CORE_MACRO_H
#define MINTY_CORE_MACRO_H

/**
 * @file Macro.h
 * @brief Header file defining core macros for the Minty engine.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include <iostream>
#include <format>
#include <filesystem>

#if !defined(MINTY_DEBUG) && !defined(MINTY_RELEASE)
#error "Either MINTY_DEBUG or MINTY_RELEASE must be defined."
#endif // !MINTY_DEBUG && !MINTY_RELEASE

#ifdef _WIN32
#define MINTY_WINDOWS
#elif defined(__linux__)
#define MINTY_LINUX
#else
#error "Unsupported operating system."
#endif

#define MINTY_MAKE_VERSION(major, minor, patch) (((static_cast<uint32_t>(major)) << 22U) | ((static_cast<uint32_t>(minor)) << 12U) | (static_cast<uint32_t>(patch)))

#endif // MINTY_CORE_MACRO_H