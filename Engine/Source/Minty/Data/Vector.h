#ifndef MINTY_DATA_VECTOR_H
#define MINTY_DATA_VECTOR_H

/**
 * @file Vector.h
 * @brief Header file for the Vector class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Constant.h"
#include "Minty/Core/Types.h"
#include "Minty/Debug/Assert.h"
#include "Minty/Memory/DefaultAllocator.h"
#include <iterator>

namespace Minty
{
	/**
	 * @brief A dynamic array that can resize itself automatically when elements are added or removed.
	 * @tparam T The type of elements stored in the Vector.
	 * @tparam AllocatorType The memory allocator to use for allocating and deallocating memory.
	 */
	template<typename T, template<typename> class AllocatorType = DefaultAllocator>
	class Vector
	{
#pragma region Types

	private:
		using Allocator = AllocatorType<T>;

#pragma endregion

#pragma region Constructors

	public:
		/**
		 * @brief Creates an empty Vector.
		 */
		Vector()
			: mp_data(nullptr), m_size(0), m_capacity(0)
		{}

		/**
		 * @brief Creates a Vector with the given initial capacity.
		 * @param capacity The initial capacity of the Vector.
		 */
		Vector(Size const capacity)
			: mp_data(nullptr), m_size(0), m_capacity(0)
		{
			reserve(capacity);
		}

		/**
		 * @brief Creates a Vector with the given size, initializing all elements to the given value.
		 * @param size The size of the Vector.
		 * @param value The value to initialize the elements with.
		 */
		Vector(Size const size, T const& value)
			: mp_data(nullptr), m_size(0), m_capacity(0)
		{
			resize(size, value);
		}
		
		/**
		 * @brief Creates a Vector with the elements from the given initializer list.
		 * @param list The initializer list containing the elements to add to the Vector.
		 */
		Vector(std::initializer_list<T> const& list)
			: mp_data(nullptr), m_size(0), m_capacity(0)
		{
			reserve(list.size());

			for (T const& value : list)
			{
				add(value);
			}
		}

		Vector(Vector const& other)
			: mp_data(Allocator().allocate(other.m_capacity))
			, m_size(other.m_size)
			, m_capacity(other.m_capacity)
		{
			for (Size i = 0; i < m_size; ++i)
			{
				new (&mp_data[i]) T(other.mp_data[i]);
			}
		}

		Vector(Vector&& other) noexcept
			: mp_data(other.mp_data)
			, m_size(other.m_size)
			, m_capacity(other.m_capacity)
		{
			other.mp_data = nullptr;
			other.m_size = 0;
			other.m_capacity = 0;
		}

		~Vector()
		{
			if (mp_data)
			{
				for (Size i = 0; i < m_size; ++i)
				{
					mp_data[i].~T();
				}
				Allocator().deallocate(mp_data, m_capacity);
			}
		}

#pragma endregion

#pragma region Iterators

	public:
		class Iterator
		{
			friend class Vector;

		public:
			using iterator_category = std::bidirectional_iterator_tag;
			using value_type = T;
			using difference_type = std::ptrdiff_t;
			using pointer = value_type*;
			using reference = value_type&;

		private:
			pointer mp_ptr;

		private:
			inline explicit Iterator(pointer const ptr)
				: mp_ptr(ptr)
			{
			}

		public:
			inline reference operator*() const
			{
				return *mp_ptr;
			}

			inline pointer operator->() const
			{
				return mp_ptr;
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

			Iterator& operator--()
			{
				--mp_ptr;
				return *this;
			}

			Iterator operator--(int)
			{
				Iterator temp = *this;
				--mp_ptr;
				return temp;
			}

			inline Iterator operator+(Size const value)
			{
				return Iterator(mp_ptr + value);
			}

			inline Iterator operator-(Size const value)
			{
				return Iterator(mp_ptr - value);
			}

			inline Bool operator==(Iterator const& other) const { return mp_ptr == other.mp_ptr; }
			inline Bool operator!=(Iterator const& other) const { return mp_ptr != other.mp_ptr; }
		};

		class ConstIterator
		{
			friend class Vector;

		public:
			using iterator_category = std::bidirectional_iterator_tag;
			using value_type = T;
			using difference_type = std::ptrdiff_t;
			using pointer = value_type const*;
			using reference = value_type const&;

		private:
			pointer mp_ptr;

		private:
			inline explicit ConstIterator(pointer const data)
				: mp_ptr(data)
			{
			}

		public:
			inline reference operator*()
			{
				return *mp_ptr;
			}

			inline pointer operator->() const
			{
				return mp_ptr;
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

			ConstIterator& operator--()
			{
				--mp_ptr;
				return *this;
			}

			ConstIterator operator--(int)
			{
				ConstIterator temp = *this;
				--mp_ptr;
				return temp;
			}

			inline ConstIterator operator+(Size const value)
			{
				return ConstIterator(mp_ptr + value);
			}

			inline ConstIterator operator-(Size const value)
			{
				return ConstIterator(mp_ptr - value);
			}

			inline Bool operator==(ConstIterator const& other) const { return mp_ptr == other.mp_ptr; }
			inline Bool operator!=(ConstIterator const& other) const { return mp_ptr != other.mp_ptr; }
		};

		class ReverseIterator
		{
			friend class Vector;

		public:
			using iterator_category = std::bidirectional_iterator_tag;
			using value_type = T;
			using difference_type = std::ptrdiff_t;
			using pointer = value_type*;
			using reference = value_type&;

		private:
			pointer mp_ptr;

		private:
			inline explicit ReverseIterator(pointer const ptr)
				: mp_ptr(ptr)
			{
			}

		public:
			inline reference operator*() const
			{
				return *mp_ptr;
			}

			inline pointer operator->() const
			{
				return mp_ptr;
			}

			ReverseIterator& operator++()
			{
				--mp_ptr;
				return *this;
			}

			ReverseIterator operator++(int)
			{
				ReverseIterator temp = *this;
				--mp_ptr;
				return temp;
			}

			ReverseIterator& operator--()
			{
				++mp_ptr;
				return *this;
			}

			ReverseIterator operator--(int)
			{
				ReverseIterator temp = *this;
				++mp_ptr;
				return temp;
			}

			inline ReverseIterator operator+(Size const value)
			{
				return ReverseIterator(mp_ptr - value);
			}

			inline ReverseIterator operator-(Size const value)
			{
				return ReverseIterator(mp_ptr + value);
			}

			inline Bool operator==(ReverseIterator const& other) const { return mp_ptr == other.mp_ptr; }
			inline Bool operator!=(ReverseIterator const& other) const { return mp_ptr != other.mp_ptr; }
		};

		class ConstReverseIterator
		{
			friend class Vector;

		public:
			using iterator_category = std::bidirectional_iterator_tag;
			using value_type = T;
			using difference_type = std::ptrdiff_t;
			using pointer = value_type const*;
			using reference = value_type const&;

		private:
			pointer mp_ptr;

		private:
			inline explicit ConstReverseIterator(pointer const data)
				: mp_ptr(data)
			{
			}

		public:
			inline reference operator*()
			{
				return *mp_ptr;
			}

			inline pointer operator->() const
			{
				return mp_ptr;
			}

			ConstReverseIterator& operator++()
			{
				--mp_ptr;
				return *this;
			}

			ConstReverseIterator operator++(int)
			{
				ConstReverseIterator temp = *this;
				--mp_ptr;
				return temp;
			}

			ConstReverseIterator& operator--()
			{
				++mp_ptr;
				return *this;
			}

			ConstReverseIterator operator--(int)
			{
				ConstReverseIterator temp = *this;
				++mp_ptr;
				return temp;
			}

			inline ConstReverseIterator operator+(Size const value)
			{
				return ConstReverseIterator(mp_ptr - value);
			}

			inline ConstReverseIterator operator-(Size const value)
			{
				return ConstReverseIterator(mp_ptr + value);
			}

			inline Bool operator==(ConstReverseIterator const& other) const { return mp_ptr == other.mp_ptr; }
			inline Bool operator!=(ConstReverseIterator const& other) const { return mp_ptr != other.mp_ptr; }
		};

		inline Iterator begin() { return Iterator(mp_data); }
		inline Iterator end() { return Iterator(mp_data + m_size); }
		inline ConstIterator begin() const { return ConstIterator(mp_data); }
		inline ConstIterator end() const { return ConstIterator(mp_data + m_size); }
		inline ReverseIterator rbegin() { return ReverseIterator(mp_data + m_size - 1); }
		inline ReverseIterator rend() { return ReverseIterator(mp_data - 1); }
		inline ConstReverseIterator rbegin() const { return ConstReverseIterator(mp_data + m_size - 1); }
		inline ConstReverseIterator rend() const { return ConstReverseIterator(mp_data - 1); }

#pragma endregion

#pragma region Operators

	public:
		Vector& operator=(Vector const& other)
		{
			if (this != &other)
			{
				// clear current data
				if (mp_data)
				{
					for (Size i = 0; i < m_size; ++i)
					{
						mp_data[i].~T();
					}
					Allocator().deallocate(mp_data, m_capacity);
				}

				// copy data from other
				m_capacity = other.m_capacity;
				m_size = other.m_size;
				mp_data = Allocator().allocate(m_capacity);
				for (Size i = 0; i < m_size; ++i)
				{
					new (&mp_data[i]) T(other.mp_data[i]);
				}
			}
			return *this;
		}

		Vector& operator=(Vector&& other) noexcept
		{
			if (this != &other)
			{
				// clear current data
				if (mp_data)
				{
					for (Size i = 0; i < m_size; ++i)
					{
						mp_data[i].~T();
					}
					Allocator().deallocate(mp_data, m_capacity);
				}

				// move data from other
				mp_data = other.mp_data;
				m_size = other.m_size;
				m_capacity = other.m_capacity;

				other.mp_data = nullptr;
				other.m_size = 0;
				other.m_capacity = 0;
			}
			return *this;
		}

		/**
		 * @brief Gets the value at the specified index.
		 * @param index The index of the value to get.
		 */
		inline T& operator[](Size const index) { return at(index); }

		/**
		 * @brief Gets the value at the specified index.
		 * @param index The index of the value to get.
		 */
		inline T const& operator[](Size const index) const { return at(index); }

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the capacity of this Vector.
		 * @returns The maximum number of elements.
		 */
		inline Size get_capacity() const { return m_capacity; }

		/**
		 * @brief Gets the size of this Vector.
		 * @returns The number of elements stored in the Vector.
		 */
		inline Size get_size() const { return m_size; }

		/**
		 * @brief Gets the internal pointer to the data.
		 * @returns A pointer to the data.
		 */
		inline T* get_data() { return mp_data; }

		/**
		 * @brief Gets the internal pointer to the data.
		 * @returns A const pointer to the data.
		 */
		inline T const* get_data() const { return mp_data; }

		/**
		 * @brief Checks if this Vector is empty.
		 * @returns True, if the size is zero.
		 */
		inline Bool is_empty() const { return get_size() == 0; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Reserves space in the Vector for the given capacity.
		 * @param capacity The new capacity of the Vector.
		 */
		void reserve(Size const capacity)
		{
			// do nothing if smaller or equal capacity
			if (capacity <= m_capacity)
			{
				return;
			}

			// create new array
			T* newData = Allocator().allocate(capacity);
			MINTY_ASSERT(newData != nullptr, ErrorCode::Memory_AllocationFailed);
			
			// move data over, if it exists
			for (Size i = 0; i < m_size; ++i)
			{
				new (&newData[i]) T(std::move(mp_data[i]));
			}

			// replace data
			mp_data = std::move(newData);
			m_capacity = capacity;
		}

		/**
		 * @brief Resizes the Vector to the given size, initializing new elements with the given value.
		 * @param size The new size of the Vector.
		 */
		template<typename... Args>
		void resize(Size const size, Args&&... args)
		{
			// if same size, do nothing
			if (size == get_size())
			{
				return;
			}

			// if larger than capacity, reserve more
			if (size > get_capacity())
			{
				reserve(size);
			}

			// initialize new elements
			if (size > get_size())
			{
				for (Size i = get_size(); i < size; ++i)
				{
					new (&mp_data[i]) T(std::forward<Args>(args)...);
				}
			}
			// destruct removed elements
			else if (size < get_size())
			{
				for (Size i = size; i < get_size(); ++i)
				{
					mp_data[i].~T();
				}
			}

			m_size = size;
		}

		/**
		 * @brief Gets the value at the specified index.
		 * @param index The index of the value to get.
		 */
		void add(T const& value)
		{
			// if larger than capacity, reserve more
			if (get_size() >= get_capacity())
			{
				if (get_capacity() == 0)
				{
					reserve(DEFAULT_COLLECTION_SIZE);
				}
				else
				{
					reserve(get_capacity() * 2);
				}
			}

			// add value
			new (&mp_data[m_size++]) T(value);
		}

		/**
		 * @brief Gets the value at the specified index.
		 * @param index The index of the value to get.
		 */
		void add(T&& value)
		{
			// if larger than capacity, reserve more
			if (get_size() >= get_capacity())
			{
				if (get_capacity() == 0)
				{
					reserve(DEFAULT_COLLECTION_SIZE);
				}
				else
				{
					reserve(get_capacity() * 2);
				}
			}

			// add value
			new (&mp_data[m_size++]) T(std::move(value));
		}

		/**
		 * @brief Gets the value at the specified index.
		 * @param index The index of the value to get.
		 */
		void insert(Size const index, T const& value)
		{
			MINTY_ASSERT_F(index <= get_size(), ErrorCode::Argument_OutOfRange, index);

			// add to end
			if (index == get_size())
			{
				add(value);
				return;
			}

			// if larger than capacity, reserve more
			if (get_size() >= get_capacity())
			{
				if (get_capacity() == 0)
				{
					reserve(DEFAULT_COLLECTION_SIZE);
				}
				else
				{
					reserve(get_capacity() * 2);
				}
			}

			// move data
			for (Size i = get_size(); i > index; --i)
			{
				mp_data[i] = std::move(mp_data[i - 1]);
			}

			// add value
			mp_data[index] = value;
			++m_size;
		}

		/**
		 * @brief Gets the value at the specified index.
		 * @param index The index of the value to get.
		 */
		void insert(Size const index, T&& value)
		{
			MINTY_ASSERT_F(index <= get_size(), ErrorCode::Argument_OutOfRange, index);

			// add to end
			if (index == get_size())
			{
				add(std::move(value));
				return;
			}

			// if larger than capacity, reserve more
			if (get_size() >= get_capacity())
			{
				if (get_capacity() == 0)
				{
					reserve(DEFAULT_COLLECTION_SIZE);
				}
				else
				{
					reserve(get_capacity() * 2);
				}
			}

			// move data
			for (Size i = get_size(); i > index; --i)
			{
				mp_data[i] = std::move(mp_data[i - 1]);
			}

			// add value
			mp_data[index] = std::move(value);
			++m_size;
		}

		/**
		 * @brief Removes the element at the given index.
		 * @param index The index of the element to be removed.
		 */
		void remove(Size const index)
		{
			MINTY_ASSERT_F(index < get_size(), ErrorCode::Argument_OutOfRange, index);

			// move data
			for (Size i = index; i < get_size() - 1; ++i)
			{
				mp_data[i] = std::move(mp_data[i + 1]);
			}

			m_size--;
		}

		/**
		 * @brief Removes a number of elements starting at the given index.
		 * @param index The index of the first element to be removed.
		 */
		void remove(Size const index, Size const count)
		{
			MINTY_ASSERT_F(index < get_size(), ErrorCode::Argument_OutOfRange, index);
			MINTY_ASSERT_F(index + count <= get_size(), ErrorCode::Argument_InvalidSize, count);
			MINTY_ASSERT(count != 0, ErrorCode::Argument_ExpectedNonZero);

			// move data
			for (Size i = index; i < get_size() - count; ++i)
			{
				mp_data[i] = std::move(mp_data[i + count]);
			}

			m_size -= count;
		}

		/**
		 * @brief Gets the element at the given index.
		 * @param index The index of the element.
		 * @returns A reference to the element at the given index.
		 */
		inline T& at(Size const index)
		{
			MINTY_ASSERT_F(index < get_size(), ErrorCode::Argument_OutOfRange, index);
			return mp_data[index];
		}
		
		/**
		 * @brief Gets the element at the given index.
		 * @param index The index of the element.
		 * @returns A const reference to the element at the given index.
		 */
		inline T const& at(Size const index) const
		{
			MINTY_ASSERT_F(index < get_size(), ErrorCode::Argument_OutOfRange, index);
			return mp_data[index];
		}

		/**
		 * @brief Gets the first element in the Vector.
		 * @returns The first element.
		 */
		inline T& front() { return at(0); }

		/**
		 * @brief Gets the first element in the Vector.
		 * @returns The first element.
		 */
		inline T const& front() const { return at(0); }

		/**
		 * @brief Gets the last element in the Vector.
		 * @returns The last element.
		 */
		inline T& back() { return at(get_size() - 1); }

		/**
		 * @brief Gets the last element in the Vector.
		 * @returns The last element.
		 */
		inline T const& back() const { return at(get_size() - 1); }

		/**
		 * @brief Creates a sub-Vector from the given index and length.
		 * @param index The starting index of the sub-Vector.
		 * @param length The number of elements in the sub-Vector.
		 * @returns A new Vector containing the specified range of elements.
		 */
		Vector<T> sub(Size const index, Size const length) const
		{
			MINTY_ASSERT_F(index < get_size(), ErrorCode::Argument_OutOfRange, index);
			MINTY_ASSERT_F(index + length <= get_size(), ErrorCode::Argument_InvalidSize, length);
			MINTY_ASSERT(length > 0, ErrorCode::Argument_ExpectedNonZero);

			// create new array
			Vector result(length);
			for (Size i = 0; i < length; ++i)
			{
				result.add(mp_data[index + i]);
			}

			return result;
		}

		/**
		 * @brief Finds the first occurrence of the given value.
		 * @param value The value to find.
		 */
		Iterator find(T const& value)
		{
			for (Size i = 0; i < get_size(); ++i)
			{
				if (mp_data[i] == value)
				{
					return Iterator(mp_data + i);
				}
			}

			return end();
		}

		/**
		 * @brief Finds the first occurrence of the given value.
		 * @param value The value to find.
		 */
		ConstIterator find(T const& value) const
		{
			for (Size i = 0; i < get_size(); ++i)
			{
				if (mp_data[i] == value)
				{
					return ConstIterator(mp_data + i);
				}
			}

			return end();
		}

		/**
		 * @brief Checks if the Vector contains the given value.
		 * @param value The value to check for.
		 */
		inline Bool contains(T const& value) const { return find(value) != end(); }

		/**
		 * @brief Removes all elements from the Vector.
		 */
		void clear()
		{
			for (Size i = 0; i < get_size(); ++i)
			{
				mp_data[i].~T();
			}
			m_size = 0;
		}

#pragma endregion

#pragma region Variables

	private:
		T* mp_data = nullptr;
		Size m_size = 0;
		Size m_capacity = 0;

#pragma endregion
	};
}

#endif // MINTY_DATA_VECTOR_H