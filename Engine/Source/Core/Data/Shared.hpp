#pragma once

/**
 * @file Shared.hpp
 * @brief Header file defining the Shared class for shared ownership in the engine.
 * @author Mitchell Talyat
 */

#include "PointerData.hpp"
#include "Ref.hpp"
#include "Platform/Type/Primitive.hpp"
#include "Core/Memory/DefaultAllocator.hpp"

namespace Minty
{
    template <typename T, typename Allocator>
    class Unique;

    /**
     * @class Shared
     * @brief A simple implementation of a shared pointer.
     * @tparam T The type of the object being managed.
     * @tparam Allocator The allocator type used for memory management.
     */
    template <typename T, typename Allocator = DefaultAllocator>
    class Shared
    {
        friend class Ref<T, Allocator>;
        friend class Unique<T, Allocator>;
        template <typename U, typename A>
        friend class Shared;

#pragma region Constructors

    public:
        /**
         * @brief Creates an empty Shared pointer.
         */
        Shared()
            : mp_ptr(nullptr), mp_counter(nullptr)
        {
        }

        /**
         * @brief Creates an empty Shared pointer.
         */
        Shared(Null)
            : mp_ptr(nullptr), mp_counter(nullptr)
        {
        }

        /**
         * @brief Copy constructor.
         * @param other The other Shared pointer to copy from.
         */
        template <typename U>
        Shared(Shared<U, Allocator> const &other)
            : mp_ptr(static_cast<T *>(other.get())), mp_counter(other.get_counter())
        {
            if (mp_counter)
            {
                ++mp_counter->strongCount;
            }
        }

        /**
         * @brief Move constructor.
         * @param other The other Shared pointer to move from.
         */
        template <typename U>
        Shared(Shared<U, Allocator> &&other)
            : mp_ptr(static_cast<T *>(other.get())), mp_counter(other.get_counter())
        {
            other.clear();
        }

        /**
         * @brief Copy constructor.
         * @param other The other Shared pointer to copy from.
         */
        Shared(Shared const &other)
            : mp_ptr(other.mp_ptr), mp_counter(other.mp_counter)
        {
            if (mp_counter)
            {
                ++mp_counter->strongCount;
            }
        }

        /**
         * @brief Move constructor.
         * @param other The other Shared pointer to move from.
         */
        Shared(Shared &&other) noexcept
            : mp_ptr(other.mp_ptr), mp_counter(other.mp_counter)
        {
            other.clear();
        }

        ~Shared()
        {
            release();
        }

    private:
        explicit Shared(T *const ptr, Internal::PointerData<Allocator> *const counter)
            : mp_ptr(ptr), mp_counter(counter)
        {
            MINTY_ASSERT((ptr == nullptr && counter == nullptr) || (ptr != nullptr && counter != nullptr), ErrorCodeEnum::Argument_InvalidValue);
            if (mp_counter)
            {
                ++mp_counter->strongCount;
            }
        }

#pragma endregion

#pragma region Operators

    public:
        Shared &operator=(Shared const &other)
        {
            if (this != &other)
            {
                release();
                mp_ptr = other.mp_ptr;
                mp_counter = other.mp_counter;
                if (mp_counter)
                {
                    ++mp_counter->strongCount;
                }
            }
            return *this;
        }

        Shared &operator=(Shared &&other) noexcept
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

        Shared &operator=(Null)
        {
            release();
            return *this;
        }

        inline Bool operator==(Shared const &other) const { return mp_ptr == other.mp_ptr; }
        inline Bool operator==(T *const other) const { return mp_ptr == other; }
        inline Bool operator==(Null const) const { return mp_ptr == nullptr; }
        inline Bool operator!=(Shared const &other) const { return mp_ptr != other.mp_ptr; }
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
         * @brief Gets the raw pointer managed by the Shared pointer.
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
         * @brief Releases ownership of the managed object and decrements the reference count.
         */
        void release()
        {
            if (mp_counter)
            {
                --mp_counter->strongCount;
                if (mp_counter->strongCount == 0)
                {
                    mp_counter->allocator.destruct(mp_ptr);
                    if (mp_counter->weakCount == 0)
                    {
                        Internal::PointerData<Allocator>::destroy(mp_counter);
                    }
                }
                clear();
            }
        }

        /**
         * @brief Kills the pointer, setting it to null without modifying reference counts.
         * @attention This should be used with caution as it can lead to dangling pointers.
         */
        void clear()
        {
            mp_ptr = nullptr;
            mp_counter = nullptr;
        }

        /**
         * @brief Casts the Shared pointer to a Shared pointer of another type.
         * @tparam U The target type to cast to.
         */
        template <typename U>
        Shared<U, Allocator> cast() const
        {
            return Shared<U, Allocator>(static_cast<U *>(mp_ptr), mp_counter);
        }

        /**
         * @brief Converts the Shared pointer to a Ref pointer.
         * @return A Ref pointer managing the same object.
         */
        Ref<T, Allocator> to_ref() const
        {
            return Ref<T, Allocator>(mp_ptr, mp_counter);
        }

        /**
         * @brief Creates a Shared pointer by constructing an object of type T.
         * @tparam Args The types of the constructor arguments.
         * @param args The constructor arguments.
         * @return A Shared pointer managing the newly constructed object.
         */
        template <typename... Args>
        static Shared<T, Allocator> create(Args... args)
        {
            Shared<T, Allocator> result;
            Internal::PointerData<Allocator> *const counter = Internal::PointerData<Allocator>::create(1, 0);
            result.mp_ptr = counter->allocator.construct<T>(std::move(args)...);
            result.mp_counter = counter;
            return result;
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
    struct hash<Minty::Shared<T, Allocator>>
    {
        size_t operator()(const Minty::Shared<T, Allocator> &shared) const noexcept
        {
            return hash<T *>{}(shared.get());
        }
    };
}