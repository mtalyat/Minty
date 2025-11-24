#pragma once
#include "Minty/Core/Macro.h"

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
		/// Write abort messages.
		/// </summary>
		Abort = 1 << 4,

		/// <summary>
		/// Write stack trace messages on aborts and errors.
		/// </summary>
		StackTrace = 1 << 5,

		/// <summary>
		/// Break on aborts.
		/// </summary>
		Break = 1 << 6,

		/// <summary>
		/// Log all messages and perform debug operations.
		/// </summary>
		All = Info | Message | Warning | Error | Abort | StackTrace | Break,

		/// <summary>
		/// Default logging state.
		/// </summary>
		Default = Info | Message | Warning | Error | Abort,
	};

	MINTY_ENUM_FLAGS_OPERATORS(DebugFlags)
}