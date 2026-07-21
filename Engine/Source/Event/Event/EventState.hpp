#pragma once

/**
 * @file EventState.hpp
 * @brief Header file for the EventState class, which manages the state of events in the application, allowing for tracking and handling of various events such as input, window events, and custom events.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Core/Serialize/Parser.hpp"
#include "Core/Type/Enum.hpp"

namespace Minty
{
    /**
	 * @brief The state of an Event.
	 */
	enum class EventStateEnum
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

        Count,
	};

    MINTY_ENABLE_ENUM_OPERATORS(EventStateEnum)

    /**
     * @brief Struct representing the state of an event, allowing for tracking and handling of various events in the application.
     */
    struct EventState
    {
        EventStateEnum value;

        constexpr EventState() : value(EventStateEnum::Unhandled) {}

        constexpr EventState(EventStateEnum const initialState) : value(initialState) {}
        
        constexpr operator EventStateEnum() const { return value; }

        /**
         * @brief Checks if the event has been processed.
         * @return True if the event has been processed, false otherwise.
         */
        constexpr Bool is_handled() const { return value != EventStateEnum::Unhandled; }

        /**
         * @brief Marks the event as handled, indicating that it has been processed and should not be further propagated or processed by other handlers.
         */
        constexpr void handle() { value = EventStateEnum::Handled; }

        /**
         * @brief Marks the event as canceled, indicating that it has been processed and should not be further propagated or processed by other handlers, and that any default behavior associated with the event should be prevented.
         */
        constexpr void cancel() { value = EventStateEnum::Canceled; }
    };

    template<>
    struct Parser<EventStateEnum>
    {
        static Bool parse(StringView const str, EventStateEnum &value);
        static String to_string(EventStateEnum const &value);
    };

    template<>
    struct Parser<EventState>
    {
        inline static Bool parse(StringView const str, EventState &value) { return Parser<EventStateEnum>::parse(str, value.value); }
        inline static String to_string(EventState const &value) { return Parser<EventStateEnum>::to_string(value.value); }
    };
}