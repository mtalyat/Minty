#ifndef MINTY_DEBUG_DEBUGFLAGS_H
#define MINTY_DEBUG_DEBUGFLAGS_H

/**
 * @file DebugFlags.h
 * @brief Header file defining debug flag enums.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Enum.h"

namespace Minty
{
	/**
	 * @brief Flags for determining how to write debug information.
	 */
	enum class DebugFlags
	{
		/**
		 * @brief Do not write any debug information.
		 */
		None = 0,

		/**
		 * @brief Write info messages.
		 */
		Info = 1 << 0,

		/**
		 * @brief Write message messages.
		 */
		Message = 1 << 1,

		/**
		 * @brief Write warning messages.
		 */
		Warning = 1 << 2,

		/**
		 * @brief Write error messages.
		 */
		Error = 1 << 3,

		/**
		 * @brief Write critical messages.
		 */
		Critical = 1 << 4,

		/**
		 * @brief Write stack trace messages on critical errors.
		 */
		StackTrace = 1 << 5,

		/**
		 * @brief Break on critical errors.
		 */
		Break = 1 << 6,

		/**
		 * @brief Log all messages and perform debug operations.
		 */
		All = Info | Message | Warning | Error | Critical | StackTrace | Break,

		/**
		 * @brief Default logging state.
		 */
		Default = Info | Message | Warning | Error | Critical,
	};

	MINTY_ENABLE_ENUM_OPERATORS(DebugFlags)
}

#endif // MINTY_DEBUG_DEBUGFLAGS_H