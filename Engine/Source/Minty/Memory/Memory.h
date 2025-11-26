#ifndef MINTY_MEMORY_MEMORY_H
#define MINTY_MEMORY_MEMORY_H

/**
 * @file Memory.h
 * @brief Header file for memory management utilities.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Memory/Allocator.h"

namespace Minty
{
    /**
     * @class Memory
     * @brief Static class providing memory allocation and deallocation utilities.
     */
    class Memory
    {
#pragma region Constructors

    public:
        Memory() = delete;
        ~Memory() = delete;

#pragma endregion

#pragma region Methods

    public:
        /**
         * @brief Allocate memory using the specified allocator.
         * @param allocator The allocator to use.
         * @param size The size of memory to allocate in bytes.
         * @return A pointer to the allocated memory.
         */
        static Any Allocate(Allocator const allocator, Size const size);

        /**
         * @brief Allocate memory using the default allocator.
         * @param size The size of memory to allocate in bytes.
         * @return A pointer to the allocated memory.
         */
        static Any AllocateDefault(Size const size);

        /**
         * @brief Allocate memory using the temporary allocator.
         * @param size The size of memory to allocate in bytes.
         * @return A pointer to the allocated memory.
         */
        static Any AllocateTemporary(Size const size);

        /**
         * @brief Allocate memory using the task allocator.
         * @param size The size of memory to allocate in bytes.
         * @return A pointer to the allocated memory.
         */
        static Any AllocateTask(Size const size);

        /**
         * @brief Allocate memory using the persistent allocator.
         * @param size The size of memory to allocate in bytes.
         * @return A pointer to the allocated memory.
         */
        static Any AllocatePersistent(Size const size);

        /**
         * @brief Deallocate memory using the specified allocator.
         * @param allocator The allocator to use.
         * @param ptr The pointer to the memory to deallocate.
         */
        static void Deallocate(Allocator const allocator, Any const ptr);

        /**
         * @brief Deallocate memory using the default allocator.
         * @param ptr The pointer to the memory to deallocate.
         */
        static void DeallocateDefault(Any const ptr);

        /**
         * @brief Deallocate memory using the temporary allocator.
         * @param ptr The pointer to the memory to deallocate.
         */
        static void DeallocateTemporary(Any const ptr);

        /**
         * @brief Deallocate memory using the task allocator.
         * @param ptr The pointer to the memory to deallocate.
         */
        static void DeallocateTask(Any const ptr);

        /**
         * @brief Deallocate memory using the persistent allocator.
         * @param ptr The pointer to the memory to deallocate.
         */
        static void DeallocatePersistent(Any const ptr);

        /**
         * @brief Construct an object using the default allocator.
         * @tparam T The type of the object to construct.
         * @param args The arguments to pass to the constructor.
         * @return A pointer to the constructed object.
         */
        template <typename T, typename... Args>
        static T *ConstructDefault(Args &&...args)
        {
            Any const ptr = AllocateDefault(sizeof(T));
            return new (ptr) T(std::forward<Args>(args)...);
        }

        /**
         * @brief Construct an object using the temporary allocator.
         * @tparam T The type of the object to construct.
         * @param args The arguments to pass to the constructor.
         * @return A pointer to the constructed object.
         */
        template <typename T, typename... Args>
        static T *ConstructTemporary(Args &&...args)
        {
            Any const ptr = AllocateTemporary(sizeof(T));
            return new (ptr) T(std::forward<Args>(args)...);
        }

        /**
         * @brief Construct an object using the task allocator.
         * @tparam T The type of the object to construct.
         * @param args The arguments to pass to the constructor.
         * @return A pointer to the constructed object.
         */
        template <typename T, typename... Args>
        static T *ConstructTask(Args &&...args)
        {
            Any const ptr = AllocateTask(sizeof(T));
            return new (ptr) T(std::forward<Args>(args)...);
        }

        /**
         * @brief Construct an object using the persistent allocator.
         * @tparam T The type of the object to construct.
         * @param args The arguments to pass to the constructor.
         * @return A pointer to the constructed object.
         */
        template <typename T, typename... Args>
        static T *ConstructPersistent(Args &&...args)
        {
            Any const ptr = AllocatePersistent(sizeof(T));
            return new (ptr) T(std::forward<Args>(args)...);
        }

        /**
         * @brief Construct an object using the specified allocator.
         * @tparam T The type of the object to construct.
         * @param allocator The allocator to use.
         * @param args The arguments to pass to the constructor.
         * @return A pointer to the constructed object.
         */
        template <typename T, typename... Args>
        static T *Construct(Allocator const allocator, Args &&...args)
        {
            Any const ptr = Allocate(allocator, sizeof(T));
            return new (ptr) T(std::forward<Args>(args)...);
        }

        /**
         * @brief Construct an array of objects using the default allocator.
         * @tparam T The type of the objects to construct.
         * @param count The number of objects to construct.
         * @param args The arguments to pass to the constructor.
         * @return A pointer to the constructed array.
         */
        template <typename T, typename... Args>
        static T *ConstructArrayDefault(Size const count, Args &&...args)
        {
            Any const ptr = AllocateDefault(sizeof(T) * count);
            T *arrayPtr = static_cast<T *>(ptr);
            for (Size i = 0; i < count; ++i)
            {
                new (&arrayPtr[i]) T(std::forward<Args>(args)...);
            }
            return arrayPtr;
        }

        /**
         * @brief Construct an array of objects using the temporary allocator.
         * @tparam T The type of the objects to construct.
         * @param count The number of objects to construct.
         * @param args The arguments to pass to the constructor.
         * @return A pointer to the constructed array.
         */
        template <typename T, typename... Args>
        static T *ConstructArrayTemporary(Size const count, Args &&...args)
        {
            Any const ptr = AllocateTemporary(sizeof(T) * count);
            T *arrayPtr = static_cast<T *>(ptr);
            for (Size i = 0; i < count; ++i)
            {
                new (&arrayPtr[i]) T(std::forward<Args>(args)...);
            }
            return arrayPtr;
        }

        /**
         * @brief Construct an array of objects using the task allocator.
         * @tparam T The type of the objects to construct.
         * @param count The number of objects to construct.
         * @param args The arguments to pass to the constructor.
         * @return A pointer to the constructed array.
         */
        template <typename T, typename... Args>
        static T *ConstructArrayTask(Size const count, Args &&...args)
        {
            Any const ptr = AllocateTask(sizeof(T) * count);
            T *arrayPtr = static_cast<T *>(ptr);
            for (Size i = 0; i < count; ++i)
            {
                new (&arrayPtr[i]) T(std::forward<Args>(args)...);
            }
            return arrayPtr;
        }

        /**
         * @brief Construct an array of objects using the persistent allocator.
         * @tparam T The type of the objects to construct.
         * @param count The number of objects to construct.
         * @param args The arguments to pass to the constructor.
         * @return A pointer to the constructed array.
         */
        template <typename T, typename... Args>
        static T *ConstructArrayPersistent(Size const count, Args &&...args)
        {
            Any const ptr = AllocatePersistent(sizeof(T) * count);
            T *arrayPtr = static_cast<T *>(ptr);
            for (Size i = 0; i < count; ++i)
            {
                new (&arrayPtr[i]) T(std::forward<Args>(args)...);
            }
            return arrayPtr;
        }

        /**
         * @brief Construct an array of objects using the specified allocator.
         * @tparam T The type of the objects to construct.
         * @param allocator The allocator to use.
         * @param count The number of objects to construct.
         * @param args The arguments to pass to the constructor.
         * @return A pointer to the constructed array.
         */
        template <typename T, typename... Args>
        static T *ConstructArray(Allocator const allocator, Size const count, Args &&...args)
        {
            Any const ptr = Allocate(allocator, sizeof(T) * count);
            T *arrayPtr = static_cast<T *>(ptr);
            for (Size i = 0; i < count; ++i)
            {
                new (&arrayPtr[i]) T(std::forward<Args>(args)...);
            }
            return arrayPtr;
        }

        
        /**
         * @brief Destruct an object allocated with the default allocator.
         * @tparam T The type of the object to destruct.
         * @param ptr The pointer to the object to destruct.
         */
        template <typename T>
        static void DestructDefault(T *const ptr)
        {
            if (ptr)
            {
                ptr->~T();
                DeallocateDefault(ptr);
            }
        }

        /**
         * @brief Destruct an object allocated with the temporary allocator.
         * @tparam T The type of the object to destruct.
         * @param ptr The pointer to the object to destruct.
         */
        template <typename T>
        static void DestructTemporary(T *const ptr)
        {
            if (ptr)
            {
                ptr->~T();
                DeallocateTemporary(ptr);
            }
        }

        /**
         * @brief Destruct an object allocated with the task allocator.
         * @tparam T The type of the object to destruct.
         * @param ptr The pointer to the object to destruct.
         */
        template <typename T>
        static void DestructTask(T *const ptr)
        {
            if (ptr)
            {
                ptr->~T();
                DeallocateTask(ptr);
            }
        }

        /**
         * @brief Destruct an object allocated with the persistent allocator.
         * @tparam T The type of the object to destruct.
         * @param ptr The pointer to the object to destruct.
         */
        template <typename T>
        static void DestructPersistent(T *const ptr)
        {
            if (ptr)
            {
                ptr->~T();
                DeallocatePersistent(ptr);
            }
        }

        /**
         * @brief Destruct an object allocated with the specified allocator.
         * @tparam T The type of the object to destruct.
         * @param allocator The allocator used for allocation.
         * @param ptr The pointer to the object to destruct.
         */
        template <typename T>
        static void Destruct(Allocator const allocator, T *const ptr)
        {
            if (ptr)
            {
                ptr->~T();
                Deallocate(allocator, ptr);
            }
        }

        /**
         * @brief Destruct an array of objects allocated with the default allocator.
         * @tparam T The type of the objects to destruct.
         * @param ptr The pointer to the array to destruct.
         * @param count The number of objects in the array.
         */
        template <typename T>
        static void DestructArrayDefault(T *const ptr, Size const count)
        {
            if (ptr)
            {
                for (Size i = 0; i < count; ++i)
                {
                    ptr[i].~T();
                }
                DeallocateDefault(ptr);
            }
        }

        /**
         * @brief Destruct an array of objects allocated with the temporary allocator.
         * @tparam T The type of the objects to destruct.
         * @param ptr The pointer to the array to destruct.
         * @param count The number of objects in the array.
         */
        template <typename T>
        static void DestructArrayTemporary(T *const ptr, Size const count)
        {
            if (ptr)
            {
                for (Size i = 0; i < count; ++i)
                {
                    ptr[i].~T();
                }
                DeallocateTemporary(ptr);
            }
        }

        /**
         * @brief Destruct an array of objects allocated with the task allocator.
         * @tparam T The type of the objects to destruct.
         * @param ptr The pointer to the array to destruct.
         * @param count The number of objects in the array.
         */
        template <typename T>
        static void DestructArrayTask(T *const ptr, Size const count)
        {
            if (ptr)
            {
                for (Size i = 0; i < count; ++i)
                {
                    ptr[i].~T();
                }
                DeallocateTask(ptr);
            }
        }

        /**
         * @brief Destruct an array of objects allocated with the persistent allocator.
         * @tparam T The type of the objects to destruct.
         * @param ptr The pointer to the array to destruct.
         * @param count The number of objects in the array.
         */
        template <typename T>
        static void DestructArrayPersistent(T *const ptr, Size const count)
        {
            if (ptr)
            {
                for (Size i = 0; i < count; ++i)
                {
                    ptr[i].~T();
                }
                DeallocatePersistent(ptr);
            }
        }

        /**
         * @brief Destruct an array of objects allocated with the specified allocator.
         * @tparam T The type of the objects to destruct.
         * @param allocator The allocator used for allocation.
         * @param ptr The pointer to the array to destruct.
         * @param count The number of objects in the array.
         */
        template <typename T>
        static void DestructArray(Allocator const allocator, T *const ptr, Size const count)
        {
            if (ptr)
            {
                for (Size i = 0; i < count; ++i)
                {
                    ptr[i].~T();
                }
                Deallocate(allocator, ptr);
            }
        }

#pragma endregion
    };
}

#endif // MINTY_MEMORY_MEMORY_H