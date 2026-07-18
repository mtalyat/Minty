#pragma once

/**
 * @file Optional.h
 * @brief Header file defining the Optional class template.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"

namespace Minty
{
    /**
     * @brief A simple Optional class template that can hold a value of type T or be empty.
     * The Optional class provides a way to represent an optional value, which may or may not be present.
     */
    template <typename T>
    class Optional
    {
#pragma region Constructor

    public:
        /**
         * @brief Creates an empty Optional that does not contain a value.
         */
        Optional() : m_hasValue(false) {}

        /**
         * @brief Creates an Optional that contains the given value.
         * @param value The value to be contained in this Optional.
         */
        Optional(T const &value) : m_value(value), m_hasValue(true) {}

        /**
         * @brief Creates an Optional that contains the given value.
         * @param value The value to be contained in this Optional.
         */
        Optional(T &&value) : m_value(std::move(value)), m_hasValue(true) {}

        ~Optional() = default;

#pragma endregion

#pragma region Operators

    public:
        Bool operator==(Optional<T> const &other) const
        {
            if (m_hasValue != other.m_hasValue)
                return false;
            if (!m_hasValue) // both are invalid, so they are equal
                return true;
            return m_value == other.m_value;
        }

        Bool operator!=(Optional<T> const &other) const
        {
            return !(*this == other);
        }

#pragma endregion

#pragma region Accessors

    public:
        /**
         * @brief Checks if this Optional contains a value.
         * @return True if this Optional contains a value, false otherwise.
         */
        inline Bool is_valid() const { return m_hasValue; }

        /**
         * @brief Gets the value contained in this Optional. The behavior is undefined if this Optional does not contain a value.
         * @return The value contained in this Optional.
         */
        inline T &get_value() { return m_value; }

        /**
         * @brief Gets the value contained in this Optional. The behavior is undefined if this Optional does not contain a value.
         * @return The value contained in this Optional.
         */
        inline T const &get_value() const { return m_value; }

#pragma endregion

#pragma region Methods

    public:
        /**
         * @brief Resets this Optional to an invalid state, destroying the contained value if it exists.
         */
        inline void reset() { m_hasValue = false; }

#pragma endregion

#pragma region Variables

    private:
        T m_value;
        Bool m_hasValue;

#pragma endregion
    };
}