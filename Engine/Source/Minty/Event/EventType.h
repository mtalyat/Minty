#pragma once

namespace Minty
{
	/// <summary>
	/// Describes the type of an Event.
	/// </summary>
	enum class EventType
	{
		/// <summary>
		/// No event.
		/// </summary>
		None = 0,

		/// <summary>
		/// When a Window is closed.
		/// </summary>
		WindowClose,
		
		/// <summary>
		/// When a Window is resized.
		/// </summary>
		WindowResize,

		//WindowFocus,
		//WindowUnfocus,
		//WindowMoved,

		/// <summary>
		/// When a Key is pressed or released.
		/// </summary>
		Key,

		/// <summary>
		/// When a Mouse Button is pressed or released.
		/// </summary>
		MouseButton,

		/// <summary>
		/// The the Mouse is moved.
		/// </summary>
		MouseMove,

		/// <summary>
		/// When the Mouse is scrolled.
		/// </summary>
		MouseScroll,

		/// <summary>
		/// When a Gamepad is connected.
		/// </summary>
		GamepadConnect,

		/// <summary>
		/// When a Gamepad is disconnected.
		/// </summary>
		GamepadDisconnect,

		/// <summary>
		/// When a Gamepad Button is pressed or released.
		/// </summary>
		GamepadButton,

		/// <summary>
		/// When a Gamepad Axis is moved.
		/// </summary>
		GamepadAxis,
	};
}