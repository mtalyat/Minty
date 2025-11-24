#ifndef MINTY_STRING_BUILDER_H
#define MINTY_STRING_BUILDER_H

/**
 * @file StringBuilder.h
 * @brief Header file for string builder utilities.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/String.h"
#include "Minty/Memory/Allocator.h"

namespace Minty
{
    /**
     * @brief Class representing a string builder utility.
     */
    class StringBuilder
    {
#pragma region Constructors

    public:
        /**
         * @brief Constructs a StringBuilder with an optional allocator.
         * @param allocator The allocator to use for memory management. Default is Allocator::Default.
         */
        explicit StringBuilder(Allocator const allocator = Allocator::Default);

        /**
         * @brief Constructs a StringBuilder with an initial capacity and an optional allocator.
         * @param initialCapacity The initial capacity of the string builder.
         * @param allocator The allocator to use for memory management. Default is Allocator::Default.
         */
        explicit StringBuilder(Size const initialCapacity, Allocator const allocator = Allocator::Default);

        /**
         * @brief Constructs a StringBuilder with an initial string and an optional allocator.
         * @param initialString The initial string to initialize the string builder with.
         * @param allocator The allocator to use for memory management. Default is Allocator::Default.
         */
        StringBuilder(String const initialString, Allocator const allocator = Allocator::Default);
        
        ~StringBuilder();

#pragma endregion

#pragma region Accessors

    public:
        /**
         * @brief Gets a C-style string representing the current contents of the StringBuilder.
         * @return A pointer to the C-style string data.
         */
        Char const* get_data() const noexcept { return mp_data; }

        Size get_size() const noexcept { return m_size; }

        Size get_length() const noexcept { return m_size; }

        Size get_capacity() const noexcept { return m_capacity; }

        /**
         * @brief Converts the StringBuilder to a String.
         * @param allocator The allocator to use for the String. Default is Allocator::Default
         * @return A String containing the current string data.
         */
        String to_string(Allocator const allocator = Allocator::Default) const;

#pragma endregion

#pragma region Methods

        /**
         * @brief Reserves capacity for the StringBuilder.
         * @param newCapacity The new capacity to reserve.
         */
        void reserve(Size const newCapacity);

        /**
         * @brief Clears the contents of the StringBuilder.
         */
        void clear() noexcept;

        /**
         * @brief Appends a character to the end of the StringBuilder.
         * @param c The character to append.
         */
        void append(Char const c);

        /**
         * @brief Appends a string to the end of the StringBuilder.
         * @param str The string to append.
         */
        void append(String const str);

#pragma endregion

#pragma region Variables

    private:
        Char* mp_data;
        Size m_size;
        Size m_capacity;
        Allocator m_allocator;

#pragma endregion
    };
}

#endif // MINTY_STRING_BUILDER_H