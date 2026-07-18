#pragma once

/**
 * @file Event.h
 * @brief Header file for the Event class, which represents an event in the application, allowing for tracking and handling of various events such as input, window events, and custom events.
 * @author Mitchell Talyat
 */

#include "EventType.hpp"
#include "EventState.hpp"
#include "Event/Type/EventCallback.hpp"

namespace Minty
{
    /**
     * @brief Class representing an event in the application, allowing for tracking and handling of various events such as input, window events, and custom events.
     */
    class Event
    {
#pragma region Constructor

    public:
        Event()
            : m_state()
        {
        }

        virtual ~Event() = default;

#pragma endregion

#pragma region Accessor

    public:
        /**
         * @brief Gets the type of the event, allowing for categorization and handling of various events in the application.
         * @return The type of the event.
         */
        virtual EventType get_type() const = 0;

        /**
         * @brief Gets the state of the event, allowing for tracking and handling of various events in the application.
         * @return The state of the event.
         */
        inline EventState get_state() const { return m_state; }

        /**
         * @brief Checks if the event has been processed.
         * @return True if the event has been processed, false otherwise.
         */
        inline Bool is_processed() const { return m_state.is_processed(); }

#pragma endregion

#pragma region Variable

    private:
        EventState m_state;

#pragma endregion
    };
}