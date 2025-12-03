#ifndef MINTY_DATA_BOXVECTOR_H
#define MINTY_DATA_BOXVECTOR_H

/**
 * @file BoxVector.h
 * @brief Header file for the BoxVector class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Memory/DefaultAllocator.h"
#include "Minty/Debug/Assert.h"

namespace Minty
{
    /**
     * @class BoxVector
     * @brief A simple container that holds a vector of values.
     * @tparam T The type of the values to store.
     */
    template<typename T, typename Allocator = DefaultAllocator>
    class BoxVector
    {
#pragma region Constructors

    public:
        /**
         * @brief Creates a BoxVector with the given size, initializing each element with the provided arguments.
         * @param size The number of elements in the BoxVector.
         * @param args The arguments to forward to each element's constructor.
         */
        template<typename... Args>
        BoxVector(Size const size, Args&&... args)
            : m_capacity(size)
            , m_size(size)
            , mp_data(static_cast<T*>(Allocator::allocate(size * sizeof(T))))
        {
            for (Size i = 0; i < m_size; ++i)
            {
                new (mp_data + i) T(std::forward<Args>(args)...);
            }
        }

        BoxVector(Size const capacity)
            : m_capacity(capacity)
            , m_size(0)
            , mp_data(static_cast<T*>(Allocator::allocate(capacity * sizeof(T))))
        {}

        BoxVector(BoxVector const& other)
            : m_capacity(other.m_capacity)
            , m_size(other.m_size)
            , mp_data(static_cast<T*>(Allocator::allocate(other.m_capacity * sizeof(T))))
        {
            for (Size i = 0; i < m_size; ++i)
            {
                new (mp_data + i) T(other.mp_data[i]);
            }
        }

        BoxVector(BoxVector&& other) noexcept
            : m_capacity(other.m_capacity)
            , m_size(other.m_size)
            , mp_data(other.mp_data)
        {
            other.m_capacity = 0;
            other.m_size = 0;
            other.mp_data = nullptr;
        }

        ~BoxVector()
        {
            for (Size i = 0; i < m_size; ++i)
            {
                mp_data[i].~T();
            }
            Allocator::deallocate(mp_data);
        }

#pragma endregion

#pragma region Operators

    public:
        /**
         * @brief Get the value at the specified index.
         * @param index The index of the value to get.
         * @return A reference to the value at the specified index.
         */
        constexpr T& operator[](Size const index)
        {
            MINTY_ASSERT(mp_data != nullptr, ErrorCode::Object_InvalidState);
            MINTY_ASSERT_F(index < m_size, ErrorCode::Argument_OutOfBounds, index);
            return mp_data[index];
        }

        /**
         * @brief Get the value at the specified index.
         * @param index The index of the value to get.
         * @return A const reference to the value at the specified index.
         */
        constexpr T const& operator[](Size const index) const
        {
            MINTY_ASSERT(mp_data != nullptr, ErrorCode::Object_InvalidState);
            MINTY_ASSERT_F(index < m_size, ErrorCode::Argument_OutOfBounds, index);
            return mp_data[index];
        }

        BoxVector & operator=(BoxVector const& other)
        {
            if (this != &other)
            {
                for (Size i = 0; i < m_size; ++i)
                {
                    mp_data[i].~T();
                }
                Allocator::deallocate(mp_data);

                m_capacity = other.m_capacity;
                m_size = other.m_size;
                mp_data = static_cast<T*>(Allocator::allocate(other.m_capacity * sizeof(T)));
                for (Size i = 0; i < m_size; ++i)
                {
                    new (mp_data + i) T(other.mp_data[i]);
                }
            }
            return *this;
        }

        BoxVector & operator=(BoxVector&& other) noexcept
        {
            if (this != &other)
            {
                for (Size i = 0; i < m_size; ++i)
                {
                    mp_data[i].~T();
                }
                Allocator::deallocate(mp_data);

                m_capacity = other.m_capacity;
                m_size = other.m_size;
                mp_data = other.mp_data;
                other.m_capacity = 0;
                other.m_size = 0;
                other.mp_data = nullptr;
            }
            return *this;
        }

#pragma endregion

#pragma region Accessors

    public:
        /**
         * @brief Get the capacity of the BoxVector.
         * @return The maximum number of elements in the BoxVector.
         */
        Size get_capacity() const
        {
            MINTY_ASSERT(mp_data != nullptr, ErrorCode::Object_InvalidState);
            return m_capacity;
        }

        /**
         * @brief Get the size of the BoxVector.
         * @return The number of elements in the BoxVector.
         */
        Size get_size() const
        {
            MINTY_ASSERT(mp_data != nullptr, ErrorCode::Object_InvalidState);
            return m_size;
        }

        /**
         * @brief Check if the BoxVector is empty.
         * @return True if the BoxVector is empty, false otherwise.
         */
        Bool is_empty() const { return m_size == 0; }

        /**
         * @brief Check if the BoxVector is full.
         * @return True if the BoxVector is full, false otherwise.
         */
        Bool is_full() const { return m_size == m_capacity; }

        /**
         * @brief Get the value at the specified index.
         * @param index The index of the value to get.
         * @return A reference to the value at the specified index.
         */
        T& at(Size const index)
        {
            MINTY_ASSERT(mp_data != nullptr, ErrorCode::Object_InvalidState);
            MINTY_ASSERT_F(index < m_size, ErrorCode::Argument_OutOfBounds, index);
            return mp_data[index];
        }

        /**
         * @brief Get the value at the specified index.
         * @param index The index of the value to get.
         * @return A const reference to the value at the specified index.
         */
        T const& at(Size const index) const
        {
            MINTY_ASSERT(mp_data != nullptr, ErrorCode::Object_InvalidState);
            MINTY_ASSERT_F(index < m_size, ErrorCode::Argument_OutOfBounds, index);
            return mp_data[index];
        }

#pragma endregion

#pragma region Methods

    public:
        /**
         * @brief Adds a new value to the end of the BoxVector.
         * @param value The value to add.
         */
        template<typename... Args>
        void add(Args&&... args)
        {
            MINTY_ASSERT(!is_full(), ErrorCode::Object_FullContainer);
            new (mp_data + m_size) T(std::forward<Args>(args)...);
            ++m_size;
        }

        template<typename... Args>
        void resize(Size const size, Args&&... args)
        {
            // if same size, do nothing
            if (size == get_size())
            {
                return;
            }

            MINTY_ASSERT_F(size <= m_capacity, ErrorCode::Argument_OutOfBounds, size);

            // call constructors/destructors
            if (size > get_size())
            {
                for (Size i = get_size(); i < size; ++i)
                {
                    new (&mp_data[i]) T(std::forward<Args>(args)...);
                }
            }
            else if (size < get_size())
            {
                for (Size i = size; i < get_size(); ++i)
                {
                    mp_data[i].~T();
                }
            }

            m_size = size;
        }

        void clear()
        {
            for (Size i = 0; i < m_size; ++i)
            {
                mp_data[i].~T();
            }
            m_size = 0;
        }

#pragma endregion

#pragma region Variables

    private:
        Size m_capacity;
        Size m_size;
        T* mp_data;

#pragma endregion
    };
}

#endif // MINTY_DATA_BOXVECTOR_H