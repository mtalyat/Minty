#pragma once

/**
 * @file Unique.h
 * @brief Header file defining the Unique class for unique ownership in the engine.
 * @author Mitchell Talyat
 */

#include "PointerData.hpp"
#include "Shared.hpp"
#include "Platform/Type/Primitive.hpp"
#include "Core/Memory/DefaultAllocator.hpp"

namespace Minty
{
    /**
     * @class Unique
     * @brief A simple implementation of a unique pointer.
     * @tparam T The type of the object being managed.
     * @tparam Allocator The allocator type used for memory management.
     */
    template <typename T, typename Allocator = DefaultAllocator>
    class Unique
    {
        template <typename U, typename A>
        friend class Unique;

#pragma region Constructors

    public:
        /**
         * @brief Creates an empty Unique pointer.
         */
        Unique()
            : mp_ptr(nullptr), m_allocator()
        {
        }

        /**
         * @brief Creates an empty Unique pointer.
         */
        Unique(Null)
            : mp_ptr(nullptr), m_allocator()
        {
        }

        /**
         * @brief Moves ownership from another Unique pointer of a different type.
         * @tparam U The type of the other Unique pointer.
         */
        template <typename U>
        Unique(Unique<U, Allocator> &&other)
            : mp_ptr(static_cast<T *>(other.get())), m_allocator(std::move(other.m_allocator))
        {
            other.clear();
        }

        /**
         * @brief Moves ownership from another Unique pointer.
         * @param other The other Unique pointer to move from.
         */
        Unique(Unique &&other) noexcept
            : mp_ptr(other.mp_ptr), m_allocator(std::move(other.m_allocator))
        {
            other.clear();
        }

        ~Unique()
        {
            if (mp_ptr)
            {
                m_allocator.destruct(mp_ptr);
            }
        }

        Unique(Unique const &) = delete;

#pragma endregion

#pragma region Operators

    public:
        Unique &operator=(Unique &&other) noexcept
        {
            if (this != &other)
            {
                m_allocator.destruct(mp_ptr);
                mp_ptr = other.mp_ptr;
                m_allocator = std::move(other.m_allocator);
                other.mp_ptr = nullptr;
            }
            return *this;
        }

        inline Bool operator==(Unique const &other) const { return mp_ptr == other.mp_ptr; }
        inline Bool operator==(T *const other) const { return mp_ptr == other; }
        inline Bool operator==(Null const) const { return mp_ptr == nullptr; }
        inline Bool operator!=(Unique const &other) const { return mp_ptr != other.mp_ptr; }
        inline Bool operator!=(T *const other) const { return mp_ptr != other; }
        inline Bool operator!=(Null const) const { return mp_ptr != nullptr; }
        inline T *operator->() const
        {
            MINTY_ASSERT(mp_ptr != nullptr, ErrorCodeEnum::Object_InvalidState);
            return mp_ptr;
        }
        inline T &operator*() const
        {
            MINTY_ASSERT(mp_ptr != nullptr, ErrorCodeEnum::Object_InvalidState);
            return *mp_ptr;
        }
        inline operator Bool() const { return mp_ptr != nullptr; }

        Unique &operator=(Unique const &) = delete;

#pragma endregion

#pragma region Accessors

    public:
        /**
         * @brief Gets the raw pointer managed by the Unique pointer.
         * @return The raw pointer.
         */
        inline T *get() const
        {
            return mp_ptr;
        }

#pragma endregion

#pragma region Methods

    public:
        /**
         * @brief Releases ownership of the managed object and deallocates its memory.
         */
        void release()
        {
            if (mp_ptr)
            {
                m_allocator.destruct(mp_ptr);
                clear();
            }
        }

        /**
         * @brief Kills the pointer, setting it to null.
         * @attention This should be used with caution as it can lead to dangling pointers.
         */
        inline void clear()
        {
            mp_ptr = nullptr;
        }

        /**
         * @brief Converts the Unique pointer to a Shared pointer.
         * @return A Shared pointer managing the same object.
         */
        Shared<T, Allocator> make_shared()
        {
            // Move this pointer to a Shared pointer, creating a new reference counter with a strong count of 1 and a weak count of 0
            Shared<T, Allocator> shared;
            if (mp_ptr)
            {
                shared.mp_ptr = mp_ptr;
                shared.mp_counter = m_allocator.construct<Internal::PointerData<Allocator>>(1, 0);
                shared.mp_counter->allocator = std::move(m_allocator);
                clear();
            }
            return shared;
        }

        /**
         * @brief Creates a Unique pointer by constructing an object of type T.
         * @tparam Args The types of the constructor arguments.
         * @param args The constructor arguments.
         * @return A Unique pointer managing the newly constructed object.
         */
        template <typename... Args>
        static Unique<T, Allocator> create(Args... args)
        {
            Unique<T, Allocator> result;
            result.mp_ptr = result.m_allocator.construct<T>(std::move(args)...);
            return result;
        }

#pragma endregion

#pragma region Variables

    private:
        T *mp_ptr;
        Allocator m_allocator;

#pragma endregion
    };
}

namespace std
{
    template <typename T, typename Allocator>
    struct hash<Minty::Unique<T, Allocator>>
    {
        size_t operator()(const Minty::Unique<T, Allocator> &unique) const noexcept
        {
            return hash<T *>{}(unique.get());
        }
    };
}