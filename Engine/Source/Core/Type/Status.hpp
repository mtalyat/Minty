#pragma once

#include "Platform/Type/Primitive.hpp"

namespace Minty
{
    /**
     * @brief Represents the "load state" of an item.
     */
    enum class StatusEnum
    {
        /**
         * @brief The status is undefined.
         */
        Undefined,

        /**
         * @brief The item has been created, but not yet loaded or enabled.
         */
        Created,

        /**
         * @brief The item has been created and loaded, but not yet enabled.
         */
        Loaded,

        /**
         * @brief The item has been created, loaded and enabled.
         */
        Enabled,

        Count,

        // Aliases
        Unloaded = Created,
        Disabled = Loaded,
    };

    struct Status
    {
        StatusEnum parent;
        StatusEnum value;

        constexpr Status() : parent(StatusEnum::Created), value(StatusEnum::Undefined) {}
        constexpr Status(StatusEnum initialValue) : parent(StatusEnum::Created), value(initialValue) {}
        constexpr operator StatusEnum() const { return (static_cast<Int>(value) < static_cast<Int>(parent)) ? value : parent; }

        constexpr Bool operator==(StatusEnum other) const { return value == other; }
        constexpr Bool operator!=(StatusEnum other) const { return value != other; }
        constexpr Bool operator<(StatusEnum other) const { return value < other; }
        constexpr Bool operator<=(StatusEnum other) const { return value <= other; }
        constexpr Bool operator>(StatusEnum other) const { return value > other; }
        constexpr Bool operator>=(StatusEnum other) const { return value >= other; }

        Bool promote_to(StatusEnum target);
        Bool demote_to(StatusEnum target);
        Bool promote_parent_to(StatusEnum target);
        Bool demote_parent_to(StatusEnum target);
    };
}