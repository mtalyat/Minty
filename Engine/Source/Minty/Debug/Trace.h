#ifndef MINTY_DEBUG_TRACE_H
#define MINTY_DEBUG_TRACE_H

/**
 * @file Trace.h
 * @brief Header file for tracing utilities.
 * @author Mitchell Talyat
 */

#ifdef MINTY_TRACE

#include "Minty/Library/Tracy.h"

#define MINTY_TRACE_FRAME() FrameMark
#define MINTY_TRACE_SCOPE() ZoneScoped
#define MINTY_TRACE_SCOPE_NAME(name) ZoneScopedN(name)
#define MINTY_TRACE_SCOPE_COLOR(color) ZoneScopedC(color)
#define MINTY_TRACE_SCOPE_NAME_COLOR(name, color) ZoneScopedNC(name, color)

#else // MINTY_TRACE

#define MINTY_TRACE_FRAME()
#define MINTY_TRACE_SCOPE()
#define MINTY_TRACE_SCOPE_NAME(name)
#define MINTY_TRACE_SCOPE_COLOR(color)
#define MINTY_TRACE_SCOPE_NAME_COLOR(name, color)

#endif // !MINTY_TRACE

#endif // MINTY_DEBUG_TRACE_H