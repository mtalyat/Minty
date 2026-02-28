#ifndef MINTY_DATA_POINTER_H
#define MINTY_DATA_POINTER_H

/**
 * @file Pointer.h
 * @brief Header file defining pointer utilities.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Memory/DefaultAllocator.h"
#include <concepts>

namespace Minty
{
    /**
     * @struct PointerData
     * @brief Structure to keep track of strong and weak reference counts.
     */
    template <typename Allocator>
    struct PointerData
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
         * @brief The allocator used for memory management of the pointer data.
         */
        Allocator allocator;

        /**
         * @brief Constructor for PointerData.
         * @param strong The initial strong reference count.
         * @param weak The initial weak reference count.
         */
        PointerData(UInt const strong, UInt const weak)
            : strongCount(strong), weakCount(weak), allocator()
        {
        }

        static PointerData<Allocator> *create(UInt const strong, UInt const weak)
        {
            Allocator allocator;
            PointerData<Allocator> *data = allocator.construct<PointerData<Allocator>>(strong, weak);
            data->allocator = std::move(allocator);
            return data;
        }

        static void destroy(PointerData<Allocator> *data)
        {
            Allocator allocator = std::move(data->allocator);
            allocator.destruct(data);
        }
    };

    template <typename T, typename Allocator>
    class Shared;
    template<typename T, typename Allocator>
    class Source;

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
        friend class Source<T, Allocator>;
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
        explicit Ref(T *const ptr, PointerData<Allocator> *const counter)
            : mp_ptr(ptr), mp_counter(counter)
        {
            MINTY_ASSERT((ptr == nullptr && counter == nullptr) || (ptr != nullptr && counter != nullptr), ErrorCode::Argument_InvalidValue);
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
        inline T *operator->() const
        {
            MINTY_ASSERT(mp_ptr != nullptr, ErrorCode::Object_InvalidState);
            return mp_ptr;
        }
        inline T &operator*() const
        {
            MINTY_ASSERT(mp_ptr != nullptr, ErrorCode::Object_InvalidState);
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
        inline PointerData<Allocator> *get_counter() const { return mp_counter; }

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
                    PointerData<Allocator>::destroy(mp_counter);
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
        PointerData<Allocator> *mp_counter;

#pragma endregion
    };

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
        friend class Source<T, Allocator>;
        friend class Unique<T, Allocator>;
        template<typename U, typename A>
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
        explicit Shared(T *const ptr, PointerData<Allocator> *const counter)
            : mp_ptr(ptr), mp_counter(counter)
        {
            MINTY_ASSERT((ptr == nullptr && counter == nullptr) || (ptr != nullptr && counter != nullptr), ErrorCode::Argument_InvalidValue);
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
            MINTY_ASSERT(mp_ptr != nullptr, ErrorCode::Object_InvalidState);
            return mp_ptr;
        }
        inline T &operator*() const
        {
            MINTY_ASSERT(mp_ptr != nullptr, ErrorCode::Object_InvalidState);
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
        inline PointerData<Allocator> *get_counter() const { return mp_counter; }

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
                        PointerData<Allocator>::destroy(mp_counter);
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
        static Shared<T, Allocator> create(Args &&...args)
        {
            Shared<T, Allocator> result;
            PointerData<Allocator>* const counter = PointerData<Allocator>::create(1, 0);
            result.mp_ptr = counter->allocator.construct<T>(std::forward<Args>(args)...);
            result.mp_counter = counter;
            return result;
        }

#pragma endregion

#pragma region Variables

    private:
        T *mp_ptr;
        PointerData<Allocator> *mp_counter;

#pragma endregion
    };

    /**
     * @class Source
     * @brief A class that can create Shared and Ref pointers to itself.
     * @tparam T The type of the object being managed.
     * @tparam Allocator The allocator type used for memory management.
     */
    template <typename T, typename Allocator = DefaultAllocator>
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
            mp_counter = PointerData<Allocator>::create(1, 0);
        }

        virtual ~Source()
        {
            --mp_counter->strongCount;
            MINTY_ASSERT(mp_counter->strongCount == 0, ErrorCode::Object_InvalidState); // All Shared pointers should have been released before the Source is destroyed
            if (mp_counter->strongCount == 0 && mp_counter->weakCount == 0)
            {
                PointerData<Allocator>::destroy(mp_counter);
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
        Shared<T, Allocator> create_shared()
        {
            return Shared<T, Allocator>(static_cast<T *>(this), mp_counter);
        }

        /**
         * @brief Creates a Ref pointer from the Source.
         * @return A Ref pointer managing this object.
         */
        Ref<T, Allocator> create_ref()
        {
            return Ref<T, Allocator>(static_cast<T *>(this), mp_counter);
        }

#pragma endregion

#pragma region Variables

    private:
        PointerData<Allocator> *mp_counter;

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
        template<typename U, typename A>
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
            MINTY_ASSERT(mp_ptr != nullptr, ErrorCode::Object_InvalidState);
            return mp_ptr;
        }
        inline T &operator*() const
        {
            MINTY_ASSERT(mp_ptr != nullptr, ErrorCode::Object_InvalidState);
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
            if(mp_ptr)
            {
                shared.mp_ptr = mp_ptr;
                shared.mp_counter = m_allocator.construct<PointerData<Allocator>>(1, 0);
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
        static Unique<T, Allocator> create(Args &&...args)
        {
            Unique<T, Allocator> result;
            result.mp_ptr = result.m_allocator.construct<T>(std::forward<Args>(args)...);
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

// std::hash specializations for Minty pointer types
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

    template <typename T, typename Allocator>
    struct hash<Minty::Shared<T, Allocator>>
    {
        size_t operator()(const Minty::Shared<T, Allocator> &shared) const noexcept
        {
            return hash<T *>{}(shared.get());
        }
    };

    template <typename T, typename Allocator>
    struct hash<Minty::Unique<T, Allocator>>
    {
        size_t operator()(const Minty::Unique<T, Allocator> &unique) const noexcept
        {
            return hash<T *>{}(unique.get());
        }
    };
}

#endif // MINTY_DATA_POINTER_H