#pragma once

/**
 * @file Ref.h
 * @brief Header file defining the Ref class for reference counting in the engine.
 * @author Mitchell Talyat
 */

#include "PointerData.h"
#include "Platform/Type/Primitive.h"
#include "Core/Memory/DefaultAllocator.h"

namespace Minty
{
    template <typename T, typename Allocator>
    class Shared;

    /**
     * @class Ref
     * @brief A simple implementation of a reference-counted pointer.
     * @tparam T The type of the object being managed.
     * @tparam Allocator The allocator type used for memory management.
     */
    template <typename T, typename Allocator = DefaultAllocator>
    class Ref
    {
        friend class Shared<T, Allocator>;
        template<typename U, typename A>
        friend class Ref;

#pragma region Constructors

    public:
        Ref()
            : mp_ptr(nullptr), mp_counter(nullptr)
        {
        }

        Ref(Null)
            : mp_ptr(nullptr), mp_counter(nullptr)
        {
        }

        /**
         * @brief Copy constructor.
         * @param other The other Ref pointer to copy from.
         */
        template <typename U>
        Ref(Ref<U, Allocator> const &other)
            : mp_ptr(static_cast<T *>(other.get())), mp_counter(other.get_counter())
        {
            if (mp_counter)
            {
                ++mp_counter->weakCount;
            }
        }

        /**
         * @brief Move constructor.
         * @param other The other Ref pointer to move from.
         */
        template <typename U>
        Ref(Ref<U, Allocator> &&other)
            : mp_ptr(static_cast<T *>(other.get())), mp_counter(other.get_counter())
        {
            other.clear();
        }

        /**
         * @brief Copy constructor.
         * @param other The other Ref pointer to copy from.
         */
        Ref(Ref const &other)
            : mp_ptr(other.mp_ptr), mp_counter(other.mp_counter)
        {
            if (mp_counter)
            {
                ++mp_counter->weakCount;
            }
        }

        /**
         * @brief Move constructor.
         * @param other The other Ref pointer to move from.
         */
        Ref(Ref &&other) noexcept
            : mp_ptr(other.mp_ptr), mp_counter(other.mp_counter)
        {
            other.clear();
        }

        ~Ref()
        {
            release();
        }

    private:
        explicit Ref(T *const ptr, Internal::PointerData<Allocator> *const counter)
            : mp_ptr(ptr), mp_counter(counter)
        {
            MINTY_ASSERT((ptr == nullptr && counter == nullptr) || (ptr != nullptr && counter != nullptr), ErrorCodeEnum::Argument_InvalidValue);
            if (mp_counter)
            {
                ++mp_counter->weakCount;
            }
        }

#pragma endregion

#pragma region Operators

    public:
        Ref &operator=(Ref const &other)
        {
            if (this != &other)
            {
                release();
                mp_ptr = other.mp_ptr;
                mp_counter = other.mp_counter;
                if (mp_counter)
                {
                    ++mp_counter->weakCount;
                }
            }
            return *this;
        }

        Ref &operator=(Ref &&other) noexcept
        {
            if (this != &other)
            {
                release();
                mp_ptr = other.mp_ptr;
                mp_counter = other.mp_counter;
                other.mp_ptr = nullptr;
                other.mp_counter = nullptr;
            }
            return *this;
        }

        Ref &operator=(T *const other)
        {
            if (mp_ptr != other)
            {
                release();
                MINTY_ASSERT(other == nullptr, ErrorCodeEnum::Argument_ExpectedNull);
                mp_ptr = other;
                mp_counter = nullptr;
            }
            return *this;
        }

        Ref &operator=(Null)
        {
            release();
            return *this;
        }

        inline Bool operator==(Ref const &other) const { return mp_ptr == other.mp_ptr; }
        inline Bool operator==(T *const other) const { return mp_ptr == other; }
        inline Bool operator==(Null const) const { return mp_ptr == nullptr; }
        inline Bool operator!=(Ref const &other) const { return mp_ptr != other.mp_ptr; }
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

#pragma endregion

#pragma region Accessors

    public:
        /**
         * @brief Gets the raw pointer managed by the Ref pointer.
         * @return The raw pointer.
         */
        inline T *get() const { return mp_ptr; }

        /**
         * @brief Gets the pointer counter managing the reference counts.
         * @return The pointer counter.
         */
        inline Internal::PointerData<Allocator> *get_counter() const { return mp_counter; }

#pragma endregion

#pragma region Methods

    public:
        /**
         * @brief Releases the reference to the managed object.
         */
        void release()
        {
            if (mp_counter)
            {
                --mp_counter->weakCount;
                if (mp_counter->strongCount == 0 && mp_counter->weakCount == 0)
                {
                    Internal::PointerData<Allocator>::destroy(mp_counter);
                }
                clear();
            }
        }

        /**
         * @brief Kills the pointer, setting it to null without modifying reference counts.
         * @attention This should be used with caution as it can lead to dangling pointers.
         */
        inline void clear()
        {
            mp_ptr = nullptr;
            mp_counter = nullptr;
        }

        /**
         * @brief Casts the Ref pointer to a Ref pointer of another type.
         * @tparam U The target type to cast to.
         */
        template <typename U>
        Ref<U, Allocator> cast() const
        {
            return Ref<U, Allocator>(static_cast<U *>(mp_ptr), mp_counter);
        }

        /**
         * @brief Converts the Ref pointer to a Shared pointer.
         * @return A Shared pointer managing the same object.
         */
        Shared<T, Allocator> to_shared() const
        {
            return Shared<T, Allocator>(mp_ptr, mp_counter);
        }

#pragma endregion

#pragma region Variables

    private:
        T *mp_ptr;
        Internal::PointerData<Allocator> *mp_counter;

#pragma endregion
    };
}

namespace std
{
    template <typename T, typename Allocator>
    struct hash<Minty::Ref<T, Allocator>>
    {
        size_t operator()(const Minty::Ref<T, Allocator> &ref) const noexcept
        {
            return hash<T *>{}(ref.get());
        }
    };
}