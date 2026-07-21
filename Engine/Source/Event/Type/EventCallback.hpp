#pragma once

/**
 * @file EventCallback.hpp
 * @brief Header file defining the EventCallback type, which represents a callback function that can be used to handle events in the application, allowing for tracking and handling of various events such as input, window events, and custom events.
 * @author Mitchell Talyat
 */

#include "Core/Type/Function.hpp"

namespace Minty
{
    class Event;

    using EventCallback = Function<void(Event&)>;
}