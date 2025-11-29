#ifndef MINTY_MEMORY_COPY_H
#define MINTY_MEMORY_COPY_H

/**
 * @file Copy.h
 * @brief Header file for memory copy utilities.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Type.h"
#include "Minty/Memory/Memory.h"

namespace Minty
{
    /**
     * @brief Perform a shallow copy of memory from source to destination.
     * @param dest The destination memory address.
     * @param src The source memory address.
     * @param size The number of bytes to copy.
     */
    void ShallowCopy(Any dest, AnyConst const src, WUInt const size);

    /**
     * @brief Perform a shallow copy of an array from source to destination.
     * @tparam T The type of the data to copy.
     * @param dest The destination array pointer.
     * @param src The source array pointer.
     * @param count The number of elements to copy.
     */
    template<typename T>
    inline void ShallowCopyArray(T* const dest, T const* const src, WUInt const count)
    {
        ShallowCopy(static_cast<Any>(dest), static_cast<AnyConst>(src), count * sizeof(T));
    }

    /**
     * @brief Perform a deep copy of data from source to destination.
     * @tparam T The type of the data to copy.
     * @param dest The destination data reference.
     * @param src The source data reference.
     */
    template<typename T>
    inline void DeepCopy(T& dest, T const& src)
    {
        dest = src;
    }

    /**
     * @brief Perform a deep copy of an array from source to destination.
     * @tparam T The type of the data to copy.
     * @param dest The destination array pointer.
     * @param src The source array pointer.
     * @param count The number of elements to copy.
     */
    template<typename T>
    void DeepCopyArray(T* const dest, T const* const src, WUInt const count)
    {
        for (WUInt i = 0; i < count; i++)
        {
            DeepCopy(dest[i], src[i]);
        }
    }

    /**
     * @brief Clone an object by performing a deep copy.
     * @tparam T The type of the object to clone.
     * @param src The source object to clone.
     * @param allocator The allocator to use for memory allocation.
     * @return A pointer to the cloned object.
     */
    template<typename T>
    T* Clone(T const& src, AllocatorType const allocator = AllocatorType::Default)
    {
        T* dest = Construct<T>(allocator);
        DeepCopy(*dest, src);
        return dest;
    }

    /**
     * @brief Clone an array by performing a deep copy.
     * @tparam T The type of the objects in the array.
     * @param src The source array to clone.
     * @param count The number of elements in the array.
     * @param allocator The allocator to use for memory allocation.
     * @return A pointer to the cloned array.
     */
    template<typename T>
    T* CloneArray(T const* const src, WUInt const count, AllocatorType const allocator = AllocatorType::Default)
    {
        T* dest = ConstructArray<T>(allocator, count);
        DeepCopyArray(dest, src, count);
        return dest;
    }

    /**
     * @brief Set a block of memory to a specified byte value.
     * @param dest The destination memory address.
     * @param value The byte value to set.
     * @param size The number of bytes to set.
     */
    void ShallowSet(Any dest, Byte const value, WUInt const size);

    /**
     * @brief Set a block of memory to a specified byte value.
     * @tparam T The type of the data.
     */
    template<typename T>
    inline void ShallowSet(T& dest, Byte const value, WUInt const size)
    {
        ShallowSet(static_cast<Any>(&dest), value, size);
    }

    /**
     * @brief Set an array to a specified byte value.
     * @tparam T The type of the data.
     * @param dest The destination array pointer.
     * @param value The byte value to set.
     */
    template<typename T>
    inline void ShallowSetArray(T* const dest, Byte const value, WUInt const count)
    {
        ShallowSet(static_cast<Any>(dest), value, count * sizeof(T));
    }

    /**
     * @brief Set data to a specified value using deep set.
     * @tparam T The type of the data.
     * @param dest The destination data reference.
     * @param value The value to set.
     */
    template<typename T>
    inline void DeepSet(T& dest, T const& value)
    {
        dest = value;
    }

    /**
     * @brief Set an array to a specified value using deep set.
     * @tparam T The type of the data.
     * @param dest The destination array pointer.
     * @param value The value to set.
     * @param count The number of elements in the array.
     */
    template<typename T>
    void DeepSetArray(T* const dest, T const& value, WUInt const count)
    {
        for (WUInt i = 0; i < count; i++)
        {
            DeepSet(dest[i], value);
        }
    }
}

#endif // MINTY_MEMORY_COPY_H