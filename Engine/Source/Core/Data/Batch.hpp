#pragma once

#include "Core/Data/TypeArray.hpp"
#include "Core/Data/Vector.hpp"
#include "Core/Tool/Copy.hpp"

namespace Minty
{
    template <typename... Types>
    class Batch
    {
#pragma region Constructor

    public:
        Batch(Size const initialCapacity = 0)
            : m_types(),
              m_data(),
              m_elementIndex(0),
              m_groupIndex(0)
        {
            // If an initial capacity is provided, reserve the space in the data vector
            if (initialCapacity > 0)
            {
                m_data.reserve(initialCapacity * m_types.get_memory_size());
            }
        }

#pragma endregion

#pragma region Accessors

    public:
        inline Byte *get_data()
        {
            return m_data.get_data();
        }

        inline Byte const *get_data() const
        {
            return m_data.get_data();
        }

        inline Size get_size() const
        {
            return m_data.get_size();
        }

        inline Size get_group_count() const
        {
            // Return fully completed groups only
            return m_groupIndex;
        }

#pragma endregion

#pragma region Methods

    public:
        /**
         * @brief Adds a single element to the batch.
         * @tparam T The type of the element to add. Must be one of the types in the TypeArray.
         * @param value The value to add.
         */
        template <typename T>
        void add(T const &value)
        {
            // Ensure this is the next type to add
            MINTY_ASSERT(typeid(T) == m_types.at(m_elementIndex), ErrorCodeEnum::Argument_InvalidType);

            // If at the start of a new group, resize the vector to accommodate the new group
            if (m_elementIndex == 0)
            {
                // Resize to account for this new group of elements
                Size memorySize = m_types.get_memory_size();
                m_data.resize(m_data.get_size() + memorySize);

                // Re-set the data pointer to the start of the new group,
                // In case the vector was resized and the underlying data pointer changed
                m_dataPtr = m_data.get_data() + m_groupIndex * memorySize;
            }

            // Copy over the value into the data vector
            Tool::copy(&value, m_dataPtr, sizeof(T));

            // Increment the element index, data pointer, and group index if we've completed a full group
            m_elementIndex++;
            m_dataPtr += sizeof(T);
            if (m_elementIndex >= m_types.get_size())
            {
                m_elementIndex = 0;
                m_groupIndex++;
            }
        }

        /**
         * @brief Adds a full group of elements to the batch.
         * @param values The values to add.
         */
        void add_group(Types const &...values)
        {
            // Ensure the number of values matches the number of types
            MINTY_ASSERT(sizeof...(values) == m_types.get_size(), ErrorCodeEnum::Argument_InvalidCount);

            // Add each value to the batch
            (add(values), ...);
        }

#pragma endregion

#pragma region Variables

    private:
        TypeArray<Types...> m_types;
        Vector<Byte> m_data;
        Byte *m_dataPtr;
        Size m_elementIndex;
        Size m_groupIndex;

#pragma endregion
    };
}