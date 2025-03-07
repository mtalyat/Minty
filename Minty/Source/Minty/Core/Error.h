#pragma once
#include "Minty/Core/Types.h"

namespace Minty
{
	/// <summary>
	/// Resembles an error code.
	/// </summary>
	enum class ErrorCode : Int
	{
		/// <summary>
		/// This is not a valid error code.
		/// </summary>
		Invalid = -1,

		/// <summary>
		/// The operation completed successfully.
		/// </summary>
		Success = 0,

		/// <summary>
		/// The operation failed.
		/// </summary>
		Failure = 1,
	};

	constexpr Bool operator==(ErrorCode const& lhs, ErrorCode const& rhs)
	{
		return static_cast<Int>(lhs) == static_cast<Int>(rhs);
	}

	constexpr Bool operator!=(ErrorCode const& lhs, ErrorCode const& rhs)
	{
		return static_cast<Int>(lhs) != static_cast<Int>(rhs);
	}
}