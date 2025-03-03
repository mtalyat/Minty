#pragma once
#include "Minty/Core/Base.h"
#include "Minty/Core/Types.h"
#include "Minty/Core/Macro.h"
#include <vector>
#include <functional>

namespace Minty
{
	/// <summary>
	/// Allows for allocation of memory in a stack.
	/// </summary>
	class StackAllocator
	{
#pragma region Variables

	private:
		Size m_capacity;
		Size m_size;
		Byte* mp_data;
		std::vector<std::function<void()>> m_destructors;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new StackAllocator with the given capacity in Bytes.
		/// </summary>
		/// <param name="capacity"></param>
		StackAllocator(Size const capacity)
			: m_capacity(capacity)
			, m_size(0)
			, mp_data(new Byte[capacity])
			, m_destructors()
		{}

		StackAllocator(StackAllocator const& other) = delete;

		/// <summary>
		/// Moves the given StackAllocator.
		/// </summary>
		/// <param name="other">The StackAllocator to move.</param>
		StackAllocator(StackAllocator&& other) noexcept
			: m_capacity(other.m_capacity)
			, m_size(other.m_size)
			, mp_data(other.mp_data)
			, m_destructors(std::move(other.m_destructors))
		{
			other.mp_data = nullptr;
			other.m_size = 0;
			other.m_capacity = 0;
		}

		~StackAllocator()
		{
			delete[] mp_data;
		};

#pragma endregion

#pragma region Operators

	public:
		StackAllocator& operator=(StackAllocator const& other) = delete;

		/// <summary>
		/// Moves the given StackAllocator.
		/// </summary>
		/// <param name="other">The StackAllocator to move.</param>
		/// <returns>This StackAllocator.</returns>
		StackAllocator& operator=(StackAllocator&& other) noexcept
		{
			if (this != &other)
			{
				if (mp_data)
				{
					delete[] mp_data;
				}
				m_capacity = other.m_capacity;
				m_size = other.m_size;
				mp_data = other.mp_data;
				m_destructors = std::move(other.m_destructors);
				other.m_capacity = 0;
				other.m_size = 0;
				other.mp_data = nullptr;
			}

			return *this;
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the capacity of this StackAllocator.
		/// </summary>
		/// <returns>The total number of bytes that can be allocated.</returns>
		Size get_capacity() const { return m_capacity; }

		/// <summary>
		/// Gets the size of this StackAllocator.
		/// </summary>
		/// <returns>The number of bytes that have been allocated.</returns>
		Size get_size() const { return m_size; }

		/// <summary>
		/// Gets the pointer to the internal data array.
		/// </summary>
		/// <returns>The data pointer.</returns>
		void* get_data() const { return mp_data; }

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Allocates space for the given size of bytes.
		/// </summary>
		/// <param name="size">The number of bytes to allocate.</param>
		/// <returns>A pointer to the data in memory.</returns>
		void* allocate(Size const size);

		/// <summary>
		/// Creates a new object.
		/// </summary>
		/// <typeparam name="T">The object to create.</typeparam>
		/// <typeparam name="...Args">The argument types used to construct the object.</typeparam>
		/// <param name="...args">The arguments used to construct the object.</param>
		/// <returns>A pointer to the new object.</returns>
		template<typename T, typename... Args>
		T* construct(Args&&... args)
		{
			void* ptr = allocate(sizeof(T));
			T* obj = new(ptr) T(std::forward<Args>(args)...);
			m_destructors.push_back([obj]() { obj->~T(); });
			return obj;
		}

		/// <summary>
		/// Deallocates all data within this StackAllocator.
		/// </summary>
		void clear();

#pragma endregion
	};
}