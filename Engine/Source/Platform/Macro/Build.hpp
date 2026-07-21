#pragma once

/**
 * @file Build.hpp
 * @brief Common build configuration definitions for the platform.
 * @author Mitchell Talyat
 */

#if !defined(MINTY_DEBUG) && !defined(MINTY_RELEASE)
#error "Either MINTY_DEBUG or MINTY_RELEASE must be defined."
#endif // !MINTY_DEBUG && !MINTY_RELEASE