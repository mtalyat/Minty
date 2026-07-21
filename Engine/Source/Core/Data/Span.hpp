#pragma once

/**
 * @file Span.hpp
 * @brief A non-owning view over a contiguous sequence of elements.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Core/Data/View.hpp"

namespace Minty
{
    /**
     * @brief A non-owning view over a contiguous sequence of elements.
     * @tparam T The type of the elements in the span.
     */
    template <typename T>
    struct Span
    {
#pragma region Constructor

        Span() : mp_data{nullptr}, m_size{0} {}

        Span(T *data, Size size) : mp_data{data}, m_size{size} {}

#pragma endregion

#pragma region Iterator

    public:
        T *begin()
        {
            return mp_data;
        }

        T const *begin() const
        {
            return mp_data;
        }

        T *end()
        {
            return mp_data + m_size;
        }

        T const *end() const
        {
            return mp_data + m_size;
        }

#pragma endregion

#pragma region Operator

        T &operator[](Size const index)
        {
            MINTY_ASSERT(index < m_size, ErrorCodeEnum::Collection_IndexOutOfBounds);
            return mp_data[index];
        }

        T const &operator[](Size const index) const
        {
            MINTY_ASSERT(index < m_size, ErrorCodeEnum::Collection_IndexOutOfBounds);
            return mp_data[index];
        }

        // Implicit conversion to View
        operator View() const { return View(mp_data, m_size); }

#pragma endregion

#pragma region Accessor

    public:
        inline Size get_size() const { return m_size; }

        inline T *get_data() { return mp_data; }

        inline T const *get_data() const { return mp_data; }

        /**
         * @brief Checks if this Span is empty (contains no elements).
         * @return True if the span is empty, false otherwise.
         */
        inline Bool is_empty() const { return m_size == 0; }

        inline T& at(Size const index)
        {
            MINTY_ASSERT(index < m_size, ErrorCodeEnum::Argument_OutOfRange);
            return mp_data[index];
        }

        inline T const& at(Size const index) const
        {
            MINTY_ASSERT(index < m_size, ErrorCodeEnum::Argument_OutOfRange);
            return mp_data[index];
        }

#pragma endregion

#pragma region Method

        public:
        inline Span<T> sub(Size const index, Size const length = MAX_SIZE) const
        {
            MINTY_ASSERT(is_empty() || index < get_size(), ErrorCodeEnum::Argument_OutOfRange);
            MINTY_ASSERT(length == MAX_SIZE || index + length <= get_size(), ErrorCodeEnum::Argument_InvalidSize);

            return Span<T>(mp_data + index, Math::min(length, get_size() - index));
        }

        inline View view() const
        {
            return View(mp_data, m_size);
        }

        #pragma endregion

#pragma region Variable

    private:
        T *mp_data;
        Size m_size;

#pragma endregion
    };
}