#ifndef MINTY_DATA_BOX_H
#define MINTY_DATA_BOX_H

/**
 * @file Box.h
 * @brief Header file for the Box class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Memory/DefaultAllocator.h"

namespace Minty
{
    /**
     * @class Box
     * @brief A simple container that holds a single value.
     * @tparam T The type of the value to store.
     */
    template<typename T, typename Allocator = DefaultAllocator>
    class Box
    {
#pragma region Constructors

    public:
        /**
         * @brief Creates a Box, initializing the stored value with the provided arguments.
         * @param args The arguments to forward to the value's constructor.
         */
        template<typename... Args>
        Box(Args&&... args)
            : mp_value(static_cast<T*>(Allocator::allocate(sizeof(T))))
        {
            new (mp_value) T(std::forward<Args>(args)...);
        }

        Box(Box const& other)
            : mp_value(static_cast<T*>(Allocator::allocate(sizeof(T))))
        {
            new (mp_value) T(*other.mp_value);
        }

        Box(Box&& other) noexcept
            : mp_value(other.mp_value)
        {
            other.mp_value = nullptr;
        }

        ~Box()
        {
            mp_value->~T();
            Allocator::deallocate(mp_value, sizeof(T));
        }

#pragma endregion

#pragma region Operators

    public:
        Box& operator=(Box const& other)
        {
            if (this != &other)
            {
                *mp_value = *other.mp_value;
            }
            return *this;
        }

        Box& operator=(Box&& other) noexcept
        {
            if (this != &other)
            {
                mp_value->~T();
                Allocator::deallocate(mp_value, sizeof(T));

                mp_value = other.mp_value;
                other.mp_value = nullptr;
            }
            return *this;
        }

#pragma endregion

#pragma region Accessors

    public:
        /**
         * @brief Get the stored value.
         * @return A reference to the stored value.
         */
        T& get()
        {
            MINTY_ASSERT(mp_value != nullptr, ErrorCode::Object_InvalidState);
            return *mp_value;
        }

        /**
         * @brief Get the stored value.
         * @return A const reference to the stored value.
         */
        T const& get() const
        {
            MINTY_ASSERT(mp_value != nullptr, ErrorCode::Object_InvalidState);
            return *mp_value;
        }

#pragma endregion

#pragma region Variables

    private:
        T* mp_value;

#pragma endregion
    };
}

#endif // MINTY_DATA_BOX_H