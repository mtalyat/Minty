#ifndef MINTY_EVENT_EVENTSTATE_H
#define MINTY_EVENT_EVENTSTATE_H

namespace Minty
{
	/**
	 * @brief The state of an Event.
	 */
	enum class EventState
	{
		/**
		 * @brief The event has not yet been handled.
		 */
		Unhandled = 0,

		/**
		 * @brief The event has been handled.
		 */
		Handled = 1,

		/**
		 * @brief The event has been canceled.
		 */
		Canceled = 2,
	};
}

#endif // MINTY_EVENT_EVENTSTATE_H