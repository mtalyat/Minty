#pragma once

#include "Core/Type/Priority.hpp"
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

#pragma region Accessor

    public:
        inline Size get_size() const { return m_data.get_size(); }
        inline Bool is_empty() const { return m_data.is_empty(); }

#pragma endregion

#pragma region Method

    public:
        void add(Priority const priority, T const &value)
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

        void add(Priority const priority, T &&value)
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
        Vector<Priority> m_priorities;
        Vector<T> m_data;

#pragma endregion
    };
}