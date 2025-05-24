#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Memory/Allocator.h"
#include <utility>

namespace Minty
{
	/// <summary>
	/// Allocates a block of memory of the given size using the given allocator.
	/// 
	/// Requires a Context instance to be created before calling this function, if any Allocator other than Default is used.
	/// </summary>
	/// <param name="size">The number of bytes to allocate.</param>
	/// <param name="allocator">The allocator to use.</param>
	/// <returns></returns>
	void* allocate(Size const size, Allocator const allocator);

	/// <summary>
	/// Creates a new object of the given type using the given allocator.
	/// 
	/// Requires a Context instance to be created before calling this function, if any Allocator other than Default is used.
	/// </summary>
	/// <typeparam name="T">The type of object.</typeparam>
	/// <typeparam name="...Args">The argument types for the object.</typeparam>
	/// <param name="allocator">The allocator to use.</param>
	/// <param name="...args">The arguments for the object.</param>
	/// <returns>A pointer to the newly created object.</returns>
	template<typename T, typename... Args>
	T* construct(Allocator const allocator, Args&&... args)
	{
		return new(allocate(sizeof(T), allocator)) T(std::forward<Args>(args)...);
	}

	/// <summary>
	/// Creates a new array of objects of the given type using the given allocator.
	/// 
	/// Requires a Context instance to be created before calling this function, if any Allocator other than Default is used.
	/// </summary>
	/// <typeparam name="T">The type of elements in the array.</typeparam>
	/// <typeparam name="...Args">The argument types for each element within the array. Uses the same arguments for all elements.</typeparam>
	/// <param name="size">The number of elements in the array.</param>
	/// <param name="allocator">The allocator to use.</param>
	/// <param name="...args">The arguments for each element within the array. Uses the same arguments for all elements.</param>
	/// <returns>A pointer to the newly created array.</returns>
	template<typename T, typename... Args>
	T* construct_array(Size const size, Allocator const allocator, Args&&... args)
	{
		void* ptr = allocate(size * sizeof(T), allocator);
		T* array = static_cast<T*>(ptr);
		for (Size i = 0; i < size; ++i)
		{
			new(array + i) T(std::forward<Args>(args)...);
		}
		return array;
	}

	/// <summary>
	/// Frees the memory allocated by the given pointer using the given allocator.
	/// 
	/// Requires a Context instance to be created before calling this function, if any Allocator other than Default is used.
	/// </summary>
	/// <param name="ptr">A pointer to the data.</param>
	/// <param name="size">The number of bytes that were allocated.</param>
	/// <param name="allocator">The Allocator used when allocating the data.</param>
	void deallocate(void* const ptr, Size const size, Allocator const allocator);

	/// <summary>
	/// Destroys the given object.
	/// 
	/// Requires a Context instance to be created before calling this function, if any Allocator other than Default is used.
	/// </summary>
	/// <typeparam name="T">The type of object.</typeparam>
	/// <param name="ptr">A pointer to the object.</param>
	/// <param name="allocator">The Allocator used to create the object.</param>
	template<typename T>
	void destruct(T* const ptr, Allocator const allocator)
	{
		ptr->~T();
		deallocate(ptr, sizeof(T), allocator);
	}

	/// <summary>
	/// Destroys the given array of objects.
	/// 
	/// Requires a Context instance to be created before calling this function, if any Allocator other than Default is used.
	/// </summary>
	/// <typeparam name="T">The type of objects.</typeparam>
	/// <param name="ptr">A pointer to the array.</param>
	/// <param name="size">The number of objects within the array.</param>
	/// <param name="allocator">The Allocator used to create the object.</param>
	template<typename T>
	void destruct_array(T* const ptr, Size const size, Allocator const allocator)
	{
		for (Size i = 0; i < size; ++i)
		{
			ptr[i].~T();
		}
		deallocate(ptr, size * sizeof(T), allocator);
	}
}