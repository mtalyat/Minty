#ifndef MINTY_EVENT_EVENTTYPE_H
#define MINTY_EVENT_EVENTTYPE_H

namespace Minty
{
	/**
	 * @brief Describes the type of an Event.
	 */
	enum class EventType
	{
		/**
		 * @brief No event.
		 */
		None = 0,

		/**
		 * @brief When a Window is closed.
		 */
		WindowClose,
		
		/**
		 * @brief When a Window is resized.
		 */
		WindowResize,

		//WindowFocus,
		//WindowUnfocus,
		//WindowMoved,

		/**
		 * @brief When a Key is pressed or released.
		 */
		Key,

		/**
		 * @brief When a Mouse Button is pressed or released.
		 */
		MouseButton,

		/**
		 * @brief The the Mouse is moved.
		 */
		MouseMove,

		/**
		 * @brief When the Mouse is scrolled.
		 */
		MouseScroll,

		/**
		 * @brief When a Gamepad is connected.
		 */
		GamepadConnect,

		/**
		 * @brief When a Gamepad is disconnected.
		 */
		GamepadDisconnect,

		/**
		 * @brief When a Gamepad Button is pressed or released.
		 */
		GamepadButton,

		/**
		 * @brief When a Gamepad Axis is moved.
		 */
		GamepadAxis,
	};
}

#endif // MINTY_EVENT_EVENTTYPE_H