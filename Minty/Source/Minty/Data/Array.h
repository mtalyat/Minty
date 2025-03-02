#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Core/Macro.h"

namespace Minty
{
	template<typename T, Size S>
	class Array
	{
	public:
		class Iterator
		{
		public:
			using iterator_category = std::forward_iterator_tag;
			using value_type = T;
			using difference_type = std::ptrdiff_t;
			using pointer = value_type*;
			using reference = value_type&;

		private:
			pointer mp_ptr;

		public:
			explicit Iterator(pointer const ptr)
				: mp_ptr(ptr)
			{}

			reference operator*() const
			{
				return *mp_ptr;
			}

			Iterator& operator++()
			{
				++mp_ptr;
				return *this;
			}

			Iterator operator++(int)
			{
				Iterator temp = *this;
				++mp_ptr;
				return temp;
			}

			Iterator& operator+(Size const value)
			{
				mp_ptr += value;
				return *this;
			}

			Iterator& operator-(Size const value)
			{
				mp_ptr -= value;
				return *this;
			}

			Bool operator==(Iterator const& other) const { return mp_ptr == other.mp_ptr; }
			Bool operator!=(Iterator const& other) const { return mp_ptr != other.mp_ptr; }
		};

		class ConstIterator
		{
		public:
			using iterator_category = std::forward_iterator_tag;
			using value_type = T;
			using difference_type = std::ptrdiff_t;
			using pointer = value_type const*;
			using reference = value_type const&;

		private:
			pointer mp_ptr;

		public:
			explicit ConstIterator(T const* data)
				: mp_ptr(data)
			{}

			T const& operator*()
			{
				return *mp_ptr;
			}

			ConstIterator& operator++()
			{
				++mp_ptr;
				return *this;
			}

			ConstIterator operator++(int)
			{
				ConstIterator temp = *this;
				++mp_ptr;
				return temp;
			}

			ConstIterator& operator+(Size const value)
			{
				mp_ptr += value;
				return *this;
			}

			ConstIterator& operator-(Size const value)
			{
				mp_ptr -= value;
				return *this;
			}

			Bool operator==(ConstIterator const& other) const { return mp_ptr == other.mp_ptr; }
			Bool operator!=(ConstIterator const& other) const { return mp_ptr != other.mp_ptr; }
		};

	private:
		T m_data[S];

	public:
		Array()
			: m_data()
		{}

		Array(T const& value)
			: m_data()
		{
			for (Size i = 0; i < S; i++)
			{
				m_data[i] = value;
			}
		}

		Array(Array const& other)
			: m_data()
		{
			for (Size i = 0; i < S; i++)
			{
				m_data[i] = other.m_data[i];
			}
		}

		Array(Array&& other) noexcept
			: m_data()
		{
			for (Size i = 0; i < S; i++)
			{
				m_data[i] = std::remove(other.m_data[i]);
			}
		}

		~Array()
		{}

		Array& operator=(Array const& other)
		{
			if (this != &other)
			{
				for (Size i = 0; i < S; i++)
				{
					m_data[i] = other.m_data[i];
				}
			}
			return *this;
		}

		Array& operator=(Array&& other) noexcept
		{
			if (this != &other)
			{
				for (Size i = 0; i < S; i++)
				{
					m_data[i] = std::move(other.m_data[i]);
				}
			}
			return *this;
		}

		T& operator[](Size const index)
		{
			return at(index);
		}

		T const& operator[](Size const index) const
		{
			return at(index);
		}

	public:
		Size get_size() const { return S; }

		Size get_capacity() const { return S; }

		T* get_data() { return m_data; }

		T const* get_data() const { return m_data; }

		Bool is_empty() const { return S == 0; }

		T& at(Size const index)
		{
			MINTY_ASSERT(index < S, "The given index is out of range.");
			return m_data[index];
		}

		T const& at(Size const index) const
		{
			MINTY_ASSERT(index < S, "The given index is out of range.");
			return m_data[index];
		}

		Iterator begin() { return Iterator(m_data); }
		Iterator end() { return Iterator(m_data + S); }

		ConstIterator begin() const { return ConstIterator(m_data); }
		ConstIterator end() const { return ConstIterator(m_data + S); }
	};
}