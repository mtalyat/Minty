#pragma once

#include "Core/Data/Vector.hpp"

namespace Minty
{
    template <typename T>
    class PriorityVector
    {
#pragma region Type

    public:
        using Iterator = typename Vector<T>::Iterator;
        using ConstIterator = typename Vector<T>::ConstIterator;

#pragma endregion

#pragma region Constructor

    public:
        PriorityVector() = default;

#pragma endregion

#pragma region Iterator

    public:
        Iterator begin() { return m_data.begin(); }
        ConstIterator begin() const { return m_data.begin(); }
        Iterator end() { return m_data.end(); }
        ConstIterator end() const { return m_data.end(); }

#pragma endregion

#pragma region Operator

    public:
        T &operator[](Size const index)
        {
            MINTY_ASSERT(index < m_data.get_size(), ErrorCodeEnum::Argument_OutOfRange);
            return m_data[index];
        }

        T const &operator[](Size const index) const
        {
            MINTY_ASSERT(index < m_data.get_size(), ErrorCodeEnum::Argument_OutOfRange);
            return m_data[index];
        }

#pragma endregion

#pragma region Accessor

    public:
        inline Size get_size() const { return m_data.get_size(); }
        inline Bool is_empty() const { return m_data.is_empty(); }

#pragma endregion

#pragma region Method

    public:
        void add(T const &value, int const priority = 0)
        {
            // Find the correct position to insert the new value based on its priority
            Size insertIndex = 0;
            while (insertIndex < m_priorities.get_size() && m_priorities[insertIndex] <= priority)
            {
                ++insertIndex;
            }

            // Insert the new value and its priority at the determined position
            m_priorities.insert(insertIndex, priority);
            m_data.insert(insertIndex, value);
        }

        void add(T &&value, int const priority = 0)
        {
            // Find the correct position to insert the new value based on its priority
            Size insertIndex = 0;
            while (insertIndex < m_priorities.get_size() && m_priorities[insertIndex] <= priority)
            {
                ++insertIndex;
            }

            // Insert the new value and its priority at the determined position
            m_priorities.insert(insertIndex, priority);
            m_data.insert(insertIndex, std::move(value));
        }

        void remove(Size const index)
        {
            MINTY_ASSERT(index < m_data.get_size(), ErrorCodeEnum::Argument_OutOfRange);
            m_priorities.remove(index);
            m_data.remove(index);
        }

        T &at(Size const index)
        {
            MINTY_ASSERT(index < m_data.get_size(), ErrorCodeEnum::Argument_OutOfRange);
            return m_data[index];
        }

        T const &at(Size const index) const
        {
            MINTY_ASSERT(index < m_data.get_size(), ErrorCodeEnum::Argument_OutOfRange);
            return m_data[index];
        }

#pragma endregion

#pragma region Variable
    private:
        Vector<int> m_priorities;
        Vector<T> m_data;

#pragma endregion
    };
}