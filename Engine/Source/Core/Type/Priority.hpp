#pragma once

#include "Platform/Type/Primitive.hpp"
#include "Core/Serialize/Parser.hpp"

namespace Minty
{
    enum class PriorityEnum
    {
        /**
         * @brief Low priority level, typically used for less critical tasks or operations that can be deferred.
         */
        Low = 0,

        /**
         * @brief Medium priority level, used for tasks that are of moderate importance and should be processed in a timely manner.
         */
        Medium = 1,

        /**
         * @brief High priority level, used for critical tasks that require immediate attention and should be processed as soon as possible.
         */
        High = 2,

        Count,

        Default = Medium
    };

    struct Priority
    {
        PriorityEnum value;

        constexpr Priority() : value(PriorityEnum::Default) {}
        constexpr Priority(PriorityEnum const &value) : value(value) {}
        constexpr operator PriorityEnum() const { return value; }

        constexpr Bool operator==(Priority const &other) const { return value == other.value; }
        constexpr Bool operator!=(Priority const &other) const { return value != other.value; }
        constexpr Bool operator<(Priority const &other) const { return value < other.value; }
        constexpr Bool operator<=(Priority const &other) const { return value <= other.value; }
        constexpr Bool operator>(Priority const &other) const { return value > other.value; }
        constexpr Bool operator>=(Priority const &other) const { return value >= other.value; }
    };

    template<>
    struct Parser<PriorityEnum>
    {
		static Bool parse(StringView const str, PriorityEnum& value);
		static String to_string(PriorityEnum const& obj);
    };

    template<>
    struct Parser<Priority>
    {
        inline static Bool parse(StringView const str, Priority& value) { return Parser<PriorityEnum>::parse(str, value.value); }
        inline static String to_string(Priority const& obj) { return Parser<PriorityEnum>::to_string(obj.value); }
    };
}