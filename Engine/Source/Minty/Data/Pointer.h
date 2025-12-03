#ifndef MINTY_DATA_POINTER_H
#define MINTY_DATA_POINTER_H

/**
 * @file Pointer.h
 * @brief Header file defining pointer utilities.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Memory/DefaultAllocator.h"
#include "Minty/Debug/Debug.h"
#include <concepts>

namespace Minty
{
    /**
     * @struct PointerCounter
     * @brief Structure to keep track of strong and weak reference counts.
     */
    struct PointerCounter
    {
        /**
         * @brief The number of strong/shared references.
         */
        UInt strongCount;

        /**
         * @brief The number of weak/reference references.
         */
        UInt weakCount;

        /**
         * @brief Constructor for PointerCounter.
         * @param strong The initial strong reference count.
         * @param weak The initial weak reference count.
         */
        PointerCounter(UInt const strong, UInt const weak)
            : strongCount(strong), weakCount(weak)
        {
        }
    };

    /**
     * @class Ref
     * @brief A simple implementation of a reference-counted pointer.
     * @tparam T The type of the object being managed.
     * @tparam Allocator The allocator type used for memory management.
     */
    template <typename T, typename Allocator = DefaultAllocator>
    class Ref
    {
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

        explicit Ref(T *const ptr, PointerCounter *const counter)
            : mp_ptr(ptr), mp_counter(counter)
        {
            MINTY_ASSERT((ptr == nullptr && counter == nullptr) || (ptr != nullptr && counter != nullptr), ErrorCode::Argument_InvalidValue);
            if (mp_counter)
            {
                ++mp_counter->weakCount;
            }
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
            other.kill();
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
            other.kill();
        }

        ~Ref()
        {
            release();
        }

#pragma endregion

#pragma region Operators

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
                MINTY_ASSERT(other == nullptr, ErrorCode::Argument_ExpectedNull);
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
        inline T *operator->() const { return mp_ptr; }
        inline T &operator*() const { return *mp_ptr; }
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
        inline PointerCounter *get_counter() const { return mp_counter; }

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
                    Allocator::template destruct<PointerCounter>(mp_counter);
                }
                kill();
            }
        }

        /**
         * @brief Kills the pointer, setting it to null without modifying reference counts.
         * @attention This should be used with caution as it can lead to dangling pointers.
         */
        inline void kill()
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

#pragma endregion

#pragma region Variables

    private:
        T *mp_ptr;
        PointerCounter *mp_counter;

#pragma endregion
    };

    /**
     * @class Shared
     * @brief A simple implementation of a shared pointer.
     * @tparam T The type of the object being managed.
     * @tparam Allocator The allocator type used for memory management.
     */
    template <typename T, typename Allocator = DefaultAllocator>
    class Shared
    {
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
         * @brief Creates a Shared pointer managing the given raw pointer.
         * @param ptr The raw pointer to manage.
         */
        explicit Shared(T *const ptr)
            : mp_ptr(ptr), mp_counter(nullptr)
        {
            if (ptr)
            {
                mp_counter = Allocator::template construct<PointerCounter>(1, 0);
            }
        }

        /**
         * @brief Creates a Shared pointer managing the given raw pointer and counter.
         * @param ptr The raw pointer to manage.
         * @param counter The pointer counter to manage reference counts.
         */
        explicit Shared(T *const ptr, PointerCounter *const counter)
            : mp_ptr(ptr), mp_counter(counter)
        {
            MINTY_ASSERT(ptr != nullptr, ErrorCode::Argument_InvalidValue);
            if (counter)
            {
                ++mp_counter->strongCount;
            }
            else
            {
                mp_counter = Allocator::template construct<PointerCounter>(1, 0);
            }
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
            other.kill();
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
            other.kill();
        }

        ~Shared()
        {
            release();
        }

#pragma endregion

#pragma region Operators

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
        inline T *operator->() const { return mp_ptr; }
        inline T &operator*() const { return *mp_ptr; }
        inline operator Bool() const { return mp_ptr != nullptr; }

#pragma endregion

#pragma region Accessors

        /**
         * @brief Gets the raw pointer managed by the Shared pointer.
         * @return The raw pointer.
         */
        inline T *get() const { return mp_ptr; }

        /**
         * @brief Gets the pointer counter managing the reference counts.
         * @return The pointer counter.
         */
        inline PointerCounter *get_counter() const { return mp_counter; }

#pragma endregion

#pragma region Methods

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
                    Allocator::template destruct<T>(mp_ptr);
                    if (mp_counter->weakCount == 0)
                    {
                        Allocator::template destruct<PointerCounter>(mp_counter);
                    }
                }
                kill();
            }
        }

        /**
         * @brief Kills the pointer, setting it to null without modifying reference counts.
         * @attention This should be used with caution as it can lead to dangling pointers.
         */
        void kill()
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
        static Shared<T, Allocator> create(Args &&...args)
        {
            return Shared<T, Allocator>(Allocator::template construct<T>(std::forward<Args>(args)...));
        }

#pragma endregion

#pragma region Variables

    private:
        T *mp_ptr;
        PointerCounter *mp_counter;

#pragma endregion
    };

    /**
     * @class Source
     * @brief A class that can create Shared and Ref pointers to itself.
     * @tparam T The type of the object being managed.
     * @tparam Allocator The allocator type used for memory management.
     */
    template <typename T>
    class Source
    {
#pragma region Constructors

    public:
        /**
         * @brief Creates a Source object.
         */
        Source()
            : mp_counter(nullptr)
        {
            DefaultAllocator::construct<PointerCounter>(1, 0);
        }

        ~Source()
        {
            --mp_counter->strongCount;
            if (mp_counter->strongCount == 0 && mp_counter->weakCount == 0)
            {
                DefaultAllocator::destruct(mp_counter);
                mp_counter = nullptr;
            }
        }

        // sources are not copyable or movable
        Source(Source const &) = delete;
        Source(Source &&) = delete;

#pragma endregion

#pragma region Operators

    public:
        Source &operator=(Source const &) = delete;
        Source &operator=(Source &&) = delete;

#pragma endregion

#pragma region Methods

    public:
        /**
         * @brief Creates a Shared pointer from the Source.
         * @return A Shared pointer managing this object.
         */
        Shared<T> create_shared()
        {
            return Shared<T>(static_cast<T *>(this), mp_counter);
        }

        /**
         * @brief Creates a Ref pointer from the Source.
         * @return A Ref pointer managing this object.
         */
        Ref<T> create_ref()
        {
            return Ref<T>(static_cast<T *>(this), mp_counter);
        }

#pragma endregion

#pragma region Variables

    private:
        PointerCounter *mp_counter;

#pragma endregion
    };

    /**
     * @class Unique
     * @brief A simple implementation of a unique pointer.
     * @tparam T The type of the object being managed.
     * @tparam Allocator The allocator type used for memory management.
     */
    template <typename T, typename Allocator = DefaultAllocator>
    class Unique
    {
#pragma region Constructors

    public:
        /**
         * @brief Creates an empty Unique pointer.
         */
        Unique()
            : mp_ptr(nullptr)
        {
        }

        /**
         * @brief Creates an empty Unique pointer.
         */
        Unique(Null)
            : mp_ptr(nullptr)
        {
        }

        /**
         * @brief Creates a Unique pointer managing the given raw pointer.
         * @param ptr The raw pointer to manage.
         */
        explicit Unique(T *const ptr)
            : mp_ptr(ptr)
        {
        }

        /**
         * @brief Moves ownership from another Unique pointer of a different type.
         * @tparam U The type of the other Unique pointer.
         */
        template <typename U>
        Unique(Unique<U, Allocator> &&other)
            : mp_ptr(static_cast<T *>(other.get()))
        {
            other.kill();
        }

        /**
         * @brief Moves ownership from another Unique pointer.
         * @param other The other Unique pointer to move from.
         */
        Unique(Unique &&other) noexcept
            : mp_ptr(other.mp_ptr)
        {
            other.kill();
        }

        ~Unique()
        {
            if (mp_ptr)
            {
                Allocator::template destruct<T>(mp_ptr);
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
                Allocator::template destruct<T>(mp_ptr);
                mp_ptr = other.mp_ptr;
                other.mp_ptr = nullptr;
            }
            return *this;
        }
        Unique &operator=(T *const other)
        {
            if (mp_ptr != other)
            {
                Allocator::template destruct<T>(mp_ptr);
                mp_ptr = other;
            }
            return *this;
        }

        inline Bool operator==(Unique const &other) const { return mp_ptr == other.mp_ptr; }
        inline Bool operator==(T *const other) const { return mp_ptr == other; }
        inline Bool operator==(Null const) const { return mp_ptr == nullptr; }
        inline Bool operator!=(Unique const &other) const { return mp_ptr != other.mp_ptr; }
        inline Bool operator!=(T *const other) const { return mp_ptr != other; }
        inline Bool operator!=(Null const) const { return mp_ptr != nullptr; }
        inline T *operator->() const { return mp_ptr; }
        inline T &operator*() const { return *mp_ptr; }
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
                Allocator::template destruct<T>(mp_ptr);
                kill();
            }
        }

        /**
         * @brief Kills the pointer, setting it to null.
         * @attention This should be used with caution as it can lead to dangling pointers.
         */
        inline void kill()
        {
            mp_ptr = nullptr;
        }

        /**
         * @brief Casts the Unique pointer to a Unique pointer of another type.
         * @tparam U The target type to cast to.
         */
        template <typename U>
        Unique<U, Allocator> cast() const
        {
            return Unique<U, Allocator>(static_cast<U *>(mp_ptr));
        }

        /**
         * @brief Converts the Unique pointer to a Shared pointer.
         * @return A Shared pointer managing the same object.
         */
        Shared<T, Allocator> to_shared()
        {
            Shared<T, Allocator> shared(mp_ptr);
            mp_ptr = nullptr;
            return shared;
        }

        /**
         * @brief Creates a Unique pointer by constructing an object of type T.
         * @tparam Args The types of the constructor arguments.
         * @param args The constructor arguments.
         * @return A Unique pointer managing the newly constructed object.
         */
        template <typename... Args>
        static Unique<T, Allocator> create(Args &&...args)
        {
            return Unique<T, Allocator>(Allocator::template construct<T>(std::forward<Args>(args)...));
        }

#pragma endregion

#pragma region Variables

    private:
        T *mp_ptr;

#pragma endregion
    };
}

// std::hash specializations for Minty pointer types
namespace std
{
    template <typename T, typename Allocator>
    struct hash<Minty::Ref<T, Allocator>>
    {
        size_t operator()(const Minty::Ref<T, Allocator>& ref) const noexcept
        {
            return hash<T*>{}(ref.get());
        }
    };

    template <typename T, typename Allocator>
    struct hash<Minty::Shared<T, Allocator>>
    {
        size_t operator()(const Minty::Shared<T, Allocator>& shared) const noexcept
        {
            return hash<T*>{}(shared.get());
        }
    };

    template <typename T, typename Allocator>
    struct hash<Minty::Unique<T, Allocator>>
    {
        size_t operator()(const Minty::Unique<T, Allocator>& unique) const noexcept
        {
            return hash<T*>{}(unique.get());
        }
    };
}

#endif // MINTY_DATA_POINTER_H