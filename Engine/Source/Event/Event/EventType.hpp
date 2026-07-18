#pragma once

/**
 * @file EventType.h
 * @brief Header file defining the EventType class, which represents the type of an event in the application, allowing for categorization and handling of various events such as input, window events, and custom events.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Core/Serialize/Parser.hpp"
#include "Core/Type/Enum.hpp"

namespace Minty
{
    /**
	 * @brief Describes the type of an Event.
	 */
	enum class EventTypeEnum
	{
		/**
		 * @brief Unknown event.
		 */
		Undefined = 0,

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
		 * @brief When the Mouse is moved.
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

        Count,
	};

	MINTY_ENABLE_ENUM_OPERATORS(EventTypeEnum)

    struct EventType
    {
        EventTypeEnum type;

        constexpr EventType() : type(EventTypeEnum::Undefined) {}

        constexpr EventType(EventTypeEnum const initialType) : type(initialType) {}
        
        constexpr operator EventTypeEnum() const { return type; }

        constexpr Bool operator==(EventTypeEnum const other) const { return type == other; }
        constexpr Bool operator!=(EventTypeEnum const other) const { return type != other; }
    };

    template<>
    struct Parser<EventTypeEnum>
    {
        static Bool parse(StringView const str, EventTypeEnum &value);
        static String to_string(EventTypeEnum const &value);
    };

	template<>
	struct Parser<EventType>
	{
		static Bool parse(StringView const str, EventType &value) { return Parser<EventTypeEnum>::parse(str, value.type); }
		static String to_string(EventType const &value) { return Parser<EventTypeEnum>::to_string(value.type); }
	};
}