#pragma once

/**
 * @file Macro.hpp
 * @brief Common macro definitions for the platform.
 * @author Mitchell Talyat
 */

#ifndef MINTY_ALIGN
#    if defined(__cpp_aligned_new) && __cpp_aligned_new >= 201606L
#        define MINTY_ALIGN(alignment) alignas(alignment)
#    else
#        define MINTY_ALIGN(alignment)
#    endif
#endif