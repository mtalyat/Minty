#pragma once
#include "Minty/Core/Enum.h"

namespace Minty
{
	/// <summary>
	/// Flags for determining how to write debug information.
	/// </summary>
	enum class DebugFlags
	{
		/// <summary>
		/// Do not write any debug information.
		/// </summary>
		None = 0,

		/// <summary>
		/// Write info messages.
		/// </summary>
		Info = 1 << 0,

		/// <summary>
		/// Write message messages.
		/// </summary>
		Message = 1 << 1,

		/// <summary>
		/// Write warning messages.
		/// </summary>
		Warning = 1 << 2,

		/// <summary>
		/// Write error messages.
		/// </summary>
		Error = 1 << 3,

		/// <summary>
		/// Write critical messages.
		/// </summary>
		Critical = 1 << 4,

		/// <summary>
		/// Write stack trace messages on critical errors.
		/// </summary>
		StackTrace = 1 << 5,

		/// <summary>
		/// Break on critical errors.
		/// </summary>
		Break = 1 << 6,

		/// <summary>
		/// Log all messages and perform debug operations.
		/// </summary>
		All = Info | Message | Warning | Error | Critical | StackTrace | Break,

		/// <summary>
		/// Default logging state.
		/// </summary>
		Default = Info | Message | Warning | Error | Critical,
	};

	MINTY_ENABLE_ENUM_OPERATORS(DebugFlags)
}