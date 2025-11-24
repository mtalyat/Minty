#pragma once

namespace Minty
{
	/// <summary>
	/// The state of an Event.
	/// </summary>
	enum class EventState
	{
		/// <summary>
		/// The event has not yet been handled.
		/// </summary>
		Unhandled = 0,

		/// <summary>
		/// The event has been handled.
		/// </summary>
		Handled = 1,

		/// <summary>
		/// The event has been canceled.
		/// </summary>
		Canceled = 2,
	};
}