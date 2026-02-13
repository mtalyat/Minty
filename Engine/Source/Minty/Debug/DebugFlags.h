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
		 * @brief Write debug messages.
		 */
		Debug = 0x1,

		/**
		 * @brief Write info messages.
		 */
		Info = 0x2,

		/**
		 * @brief Write message messages.
		 */
		Message = 0x4,

		/**
		 * @brief Write warning messages.
		 */
		Warning = 0x8,

		/**
		 * @brief Write error messages.
		 */
		Error = 0x10,

		/**
		 * @brief Write critical messages.
		 */
		Critical = 0x20,

		/**
		 * @brief Write stack trace messages on critical errors.
		 */
		StackTrace = 0x40,

		/**
		 * @brief Break on critical errors.
		 */
		Break = 0x80,

		/**
		 * @brief Log all messages and perform debug operations.
		 */
		All = Debug | Info | Message | Warning | Error | Critical | StackTrace | Break,

		/**
		 * @brief Default logging state.
		 */
#ifdef MINTY_DEBUG
		Default = All,
#else
		Default = Message | Warning | Error | Critical,
#endif // MINTY_DEBUG
	};

	MINTY_ENABLE_ENUM_OPERATORS(DebugFlags)
}

#endif // MINTY_DEBUG_DEBUGFLAGS_H