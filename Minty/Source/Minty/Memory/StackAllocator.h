#pragma once
#include "Minty/Core/Types.h"

namespace Minty
{
	class StackAllocator
	{
	private:
		Byte* mp_buffer;
		Size m_size;
		Size m_capacity;

	public:
		StackAllocator(Size size)
			: mp_buffer(nullptr)
			, m_size(0)
			, m_capacity(size)
		{
			mp_buffer = new Byte[size];
		}

		~StackAllocator()
		{
			delete[] mp_buffer;
		};

		StackAllocator(StackAllocator const& other) = delete;
		StackAllocator& operator=(StackAllocator const& other) = delete;

		StackAllocator(StackAllocator&& other) noexcept
			: mp_buffer(other.mp_buffer)
			, m_size(other.m_size)
			, m_capacity(other.m_capacity)
		{
			other.mp_buffer = nullptr;
			other.m_size = 0;
			other.m_capacity = 0;
		}

		StackAllocator& operator=(StackAllocator&& other) noexcept
		{
			if (this != &other)
			{
				delete[] mp_buffer;

				mp_buffer = other.mp_buffer;
				m_size = other.m_size;
				m_capacity = other.m_capacity;

				other.mp_buffer = nullptr;
				other.m_size = 0;
				other.m_capacity = 0;
			}

			return *this;
		}

		//template<typename T>
		//T* Allocate(Size count = 1)
		//{
		//	Size size = count * sizeof(T);

		//	if (m_size + size > m_capacity)
		//	{

		//		return nullptr;
		//	}


		//}
	};
}