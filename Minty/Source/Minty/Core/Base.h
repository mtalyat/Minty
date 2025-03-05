#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Memory/Allocator.h"
#include <utility>

namespace Minty
{
	void* allocate(Size const size, Allocator const allocator);

	template<typename T, typename... Args>
	T* construct(Allocator const allocator, Args&&... args)
	{
		return new(allocate(sizeof(T), allocator)) T(std::forward<Args>(args)...);
	}

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

	void deallocate(void* const ptr, Size const size, Allocator const allocator);

	template<typename T>
	void destruct(T* const ptr, Allocator const allocator)
	{
		ptr->~T();
		deallocate(ptr, sizeof(T), allocator);
	}

	/// <summary>
	/// Destroys the given array of objects.
	/// </summary>
	/// <typeparam name="T">The type of objects.</typeparam>
	/// <param name="ptr">A pointer to the array.</param>
	/// <param name="size">The number of objects within the array.</param>
	/// <param name="allocator">The allocation method used when creating the object.</param>
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