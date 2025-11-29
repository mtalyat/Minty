#ifndef MINTY_DATA_BOXARRAY_H
#define MINTY_DATA_BOXARRAY_H

/**
 * @file BoxArray.h
 * @brief Header file for the BoxArray class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Memory/DefaultAllocator.h"

namespace Minty
{
    /**
     * @class BoxArray
     * @brief A simple container that holds an array of values.
     * @tparam T The type of the values to store.
     */
    template<typename T, typename Allocator = DefaultAllocator>
    class BoxArray
    {
#pragma region Constructors

    public:
        /**
         * @brief Creates a BoxArray with the given size, initializing each element with the provided arguments.
         * @param size The number of elements in the BoxArray.
         * @param args The arguments to forward to each element's constructor.
         */
        template<typename... Args>
        BoxArray(Size const size, Args&&... args)
            : m_size(size)
            , mp_data(static_cast<T*>(Allocator::allocate(size * sizeof(T))))
        {
            for (Size i = 0; i < m_size; ++i)
            {
                new (mp_data + i) T(std::forward<Args>(args)...);
            }
        }

        ~BoxArray()
        {
            for (Size i = 0; i < m_size; ++i)
            {
                mp_data[i].~T();
            }
            Allocator::deallocate(mp_data);
        }

        BoxArray(BoxArray const& other)
            : m_size(other.m_size)
            , mp_data(static_cast<T*>(Allocator::allocate(other.m_size * sizeof(T))))
        {
            for (Size i = 0; i < m_size; ++i)
            {
                new (mp_data + i) T(other.mp_data[i]);
            }
        }

        BoxArray(BoxArray&& other) noexcept
            : m_size(other.m_size)
            , mp_data(other.mp_data)
        {
            other.m_size = 0;
            other.mp_data = nullptr;
        }

#pragma endregion

#pragma region Operators

    public:
        BoxArray& operator=(BoxArray const& other)
        {
            if (this != &other)
            {
                for (Size i = 0; i < m_size; ++i)
                {
                    mp_data[i].~T();
                }
                Allocator::deallocate(mp_data);

                m_size = other.m_size;
                mp_data = static_cast<T*>(Allocator::allocate(other.m_size * sizeof(T)));
                for (Size i = 0; i < m_size; ++i)
                {
                    new (mp_data + i) T(other.mp_data[i]);
                }
            }
            return *this;
        }

        BoxArray& operator=(BoxArray&& other) noexcept
        {
            if (this != &other)
            {
                for (Size i = 0; i < m_size; ++i)
                {
                    mp_data[i].~T();
                }
                Allocator::deallocate(mp_data);

                m_size = other.m_size;
                mp_data = other.mp_data;
                other.m_size = 0;
                other.mp_data = nullptr;
            }
            return *this;
        }

#pragma endregion

#pragma region Accessors

    public:
        /**
         * @brief Get the size of the BoxArray.
         * @return The number of elements in the BoxArray.
         */
        Size get_size() const
        {
            MINTY_ASSERT(mp_data != nullptr, ErrorCode::Object_InvalidState);
            return m_size;
        }

#pragma endregion

#pragma region Operators

    public:
        /**
         * @brief Get the value at the specified index.
         * @param index The index of the value to get.
         * @return A reference to the value at the specified index.
         */
        inline T& operator[](Size const index) { return at(index); }

        /**
         * @brief Get the value at the specified index.
         * @param index The index of the value to get.
         * @return A const reference to the value at the specified index.
         */
        inline T const& operator[](Size const index) const { return at(index); }

#pragma endregion

#pragma region Accessors

    public:
        /**
         * @brief Get the value at the specified index.
         * @param index The index of the value to get.
         * @return A reference to the value at the specified index.
         */
        T& at(Size const index)
        {
            MINTY_ASSERT(mp_data != nullptr, ErrorCode::Object_InvalidState);
            MINTY_ASSERT(index < m_size, ErrorCode::Argument_OutOfBounds, index);
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
            MINTY_ASSERT(index < m_size, ErrorCode::Argument_OutOfBounds, index);
            return mp_data[index];
        }

        /**
         * @brief Get the value at the specified index.
         * @param index The index of the value to get.
         * @return A copy of the value at the specified index.
         */
        T index(Size const index) const
        {
            MINTY_ASSERT(mp_data != nullptr, ErrorCode::Object_InvalidState);
            MINTY_ASSERT(index < m_size, ErrorCode::Argument_OutOfBounds, index);
            return mp_data[index];
        }

#pragma endregion

#pragma region Variables

    private:
        Size m_size;
        T* mp_data;

#pragma endregion
    };
}

#endif // MINTY_DATA_BOXARRAY_H