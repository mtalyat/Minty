#pragma once
#include "Minty/Core/Base.h"
#include "Minty/Core/Constant.h"
#include "Minty/Core/Types.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Memory/Allocator.h"
#include <iterator>

namespace Minty
{
	/// <summary>
	/// Holds a collection of elements with a dynamic size.
	/// </summary>
	/// <typeparam name="T">Then type of element.</typeparam>
	template<typename T>
	class Vector
	{
#pragma region Variables

	private:
		Allocator m_allocator;
		Size m_capacity;
		Size m_size;
		T* mp_data;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates an empty Vector.
		/// </summary>
		/// <param name="allocator">The memory allocator to use.</param>
		constexpr Vector(Allocator const allocator = Allocator::Default)
			: m_allocator(allocator)
			, m_capacity(0)
			, m_size(0)
			, mp_data(nullptr)
		{}

		/// <summary>
		/// Creates an empty Vector with the given capacity.
		/// </summary>
		/// <param name="capacity">The maximum number of elements.</param>
		/// <param name="allocator">The memory allocator to use.</param>
		Vector(Size const capacity, Allocator const allocator = Allocator::Default)
			: m_allocator(allocator)
			, m_capacity(0)
			, m_size(0)
			, mp_data(nullptr)
		{
			reserve(capacity);
		}

		/// <summary>
		/// Creates a Vector and fills it with the given value.
		/// </summary>
		/// <param name="size">The number of elements to populate.</param>
		/// <param name="value">The value to use.</param>
		/// <param name="allocator">The memory allocator to use.</param>
		Vector(Size const size, T const& value, Allocator const allocator = Allocator::Default)
			: m_allocator(allocator)
			, m_capacity(0)
			, m_size(0)
			, mp_data(nullptr)
		{
			resize(size, value);

			for (Size i = 0; i < m_size; ++i)
			{
				mp_data[i] = value;
			}
		}

		/// <summary>
		/// Creates a Vector with the given values.
		/// </summary>
		/// <param name="list">The values to set the Vector data to.</param>
		/// <param name="allocator">The memory allocator to use.</param>
		Vector(std::initializer_list<T> const& list, Allocator const allocator = Allocator::Default)
			: m_allocator(allocator)
			, m_capacity(0)
			, m_size(0)
			, mp_data(nullptr)
		{
			reserve(list.size());

			for (T const& value : list)
			{
				add(value);
			}
		}

		/// <summary>
		/// Copies the given Vector.
		/// </summary>
		/// <param name="other">The Vector to copy.</param>
		Vector(Vector const& other)
			: m_allocator(other.m_allocator)
			, m_capacity(other.m_capacity)
			, m_size(other.m_size)
			, mp_data(static_cast<T*>(allocate(m_capacity * sizeof(T), m_allocator)))
		{
			for (Size i = 0; i < m_size; ++i)
			{
				new (&mp_data[i]) T(other.mp_data[i]);
			}
		}

		/// <summary>
		/// Moves the given Vector.
		/// </summary>
		/// <param name="other">The Vector to move.</param>
		Vector(Vector&& other) noexcept
			: m_allocator(other.m_allocator)
			, m_capacity(other.m_capacity)
			, m_size(other.m_size)
			, mp_data(other.mp_data)
		{
			other.m_allocator = Allocator::Default;
			other.m_capacity = 0;
			other.m_size = 0;
			other.mp_data = nullptr;
		}

		constexpr ~Vector()
		{
			clear();
			if (mp_data)
			{
				deallocate(mp_data, m_capacity * sizeof(T), m_allocator);
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
			constexpr explicit Iterator(pointer const ptr)
				: mp_ptr(ptr)
			{
			}

		public:
			constexpr reference operator*() const
			{
				return *mp_ptr;
			}

			constexpr pointer operator->() const
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

			constexpr Iterator operator+(Size const value)
			{
				return Iterator(mp_ptr + value);
			}

			constexpr Iterator operator-(Size const value)
			{
				return Iterator(mp_ptr - value);
			}

			constexpr Bool operator==(Iterator const& other) const { return mp_ptr == other.mp_ptr; }
			constexpr Bool operator!=(Iterator const& other) const { return mp_ptr != other.mp_ptr; }
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
			constexpr explicit ConstIterator(pointer const data)
				: mp_ptr(data)
			{
			}

		public:
			constexpr reference operator*()
			{
				return *mp_ptr;
			}

			constexpr pointer operator->() const
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

			constexpr ConstIterator operator+(Size const value)
			{
				return ConstIterator(mp_ptr + value);
			}

			constexpr ConstIterator operator-(Size const value)
			{
				return ConstIterator(mp_ptr - value);
			}

			constexpr Bool operator==(ConstIterator const& other) const { return mp_ptr == other.mp_ptr; }
			constexpr Bool operator!=(ConstIterator const& other) const { return mp_ptr != other.mp_ptr; }
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
			constexpr explicit ReverseIterator(pointer const ptr)
				: mp_ptr(ptr)
			{
			}

		public:
			constexpr reference operator*() const
			{
				return *mp_ptr;
			}

			constexpr pointer operator->() const
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

			constexpr ReverseIterator operator+(Size const value)
			{
				return ReverseIterator(mp_ptr - value);
			}

			constexpr ReverseIterator operator-(Size const value)
			{
				return ReverseIterator(mp_ptr + value);
			}

			constexpr Bool operator==(ReverseIterator const& other) const { return mp_ptr == other.mp_ptr; }
			constexpr Bool operator!=(ReverseIterator const& other) const { return mp_ptr != other.mp_ptr; }
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
			constexpr explicit ConstReverseIterator(pointer const data)
				: mp_ptr(data)
			{
			}

		public:
			constexpr reference operator*()
			{
				return *mp_ptr;
			}

			constexpr pointer operator->() const
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

			constexpr ConstReverseIterator operator+(Size const value)
			{
				return ConstReverseIterator(mp_ptr - value);
			}

			constexpr ConstReverseIterator operator-(Size const value)
			{
				return ConstReverseIterator(mp_ptr + value);
			}

			constexpr Bool operator==(ConstReverseIterator const& other) const { return mp_ptr == other.mp_ptr; }
			constexpr Bool operator!=(ConstReverseIterator const& other) const { return mp_ptr != other.mp_ptr; }
		};

		/// <summary>
		/// Gets an Iterator to the beginning of the Vector.
		/// </summary>
		/// <returns>An Iterator pointing to the first element.</returns>
		constexpr Iterator begin() { return Iterator(mp_data); }

		/// <summary>
		/// Gets an Iterator to the end of the Vector.
		/// </summary>
		/// <returns>An Iterator pointing to the last element + 1.</returns>
		constexpr Iterator end() { return Iterator(mp_data + m_size); }

		/// <summary>
		/// Gets an ConstIterator to the beginning of the Vector.
		/// </summary>
		/// <returns>A ConstIterator pointing to the first element.</returns>
		constexpr ConstIterator begin() const { return ConstIterator(mp_data); }

		/// <summary>
		/// Gets an ConstIterator to the end of the Vector.
		/// </summary>
		/// <returns>A ConstIterator pointing to the last element + 1.</returns>
		constexpr ConstIterator end() const { return ConstIterator(mp_data + m_size); }

		/// <summary>
		/// Gets a ReverseIterator to the beginning of the Vector.
		/// </summary>
		/// <returns>A ReverseIterator pointing to the first element.</returns>
		constexpr ReverseIterator rbegin() { return ReverseIterator(mp_data + m_size - 1); }

		/// <summary>
		/// Gets an ReverseIterator to the end of the Vector.
		/// </summary>
		/// <returns>An ReverseIterator pointing to the last element + 1.</returns>
		constexpr ReverseIterator rend() { return ReverseIterator(mp_data - 1); }

		/// <summary>
		/// Gets an ConstReverseIterator to the beginning of the Vector.
		/// </summary>
		/// <returns>A ConstReverseIterator pointing to the first element.</returns>
		constexpr ConstReverseIterator rbegin() const { return ConstReverseIterator(mp_data + m_size - 1); }

		/// <summary>
		/// Gets an ConstReverseIterator to the end of the Vector.
		/// </summary>
		/// <returns>A ConstReverseIterator pointing to the last element + 1.</returns>
		constexpr ConstReverseIterator rend() const { return ConstReverseIterator(mp_data - 1); }

#pragma endregion

#pragma region Operators

	public:
		constexpr Vector& operator=(Vector const& other)
		{
			if (this != &other)
			{
				if (mp_data)
				{
					deallocate(mp_data, m_capacity * sizeof(T), m_allocator);
					mp_data = nullptr;
				}
				m_allocator = other.m_allocator;
				m_capacity = other.m_capacity;
				m_size = other.m_size;
				if (other.mp_data)
				{
					mp_data = static_cast<T*>(allocate(m_capacity * sizeof(T), m_allocator));
					for (Size i = 0; i < m_size; ++i)
					{
						new (&mp_data[i]) T(other.mp_data[i]);
					}
				}
				
			}
			return *this;
		}

		constexpr Vector& operator=(Vector&& other) noexcept
		{
			if (this != &other)
			{
				if (mp_data)
				{
					deallocate(mp_data, m_capacity * sizeof(T), m_allocator);
					mp_data = nullptr;
				}
				m_allocator = other.m_allocator;
				m_capacity = other.m_capacity;
				m_size = other.m_size;
				mp_data = other.mp_data;
				other.m_allocator = Allocator::Default;
				other.m_capacity = 0;
				other.m_size = 0;
				other.mp_data = nullptr;
			}
			return *this;
		}

		constexpr T& operator[](Size const index)
		{
			return at(index);
		}

		constexpr T const& operator[](Size const index) const
		{
			return at(index);
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the capacity of this Vector.
		/// </summary>
		/// <returns>The maximum number of elements.</returns>
		constexpr Size get_capacity() const { return m_capacity; }

		/// <summary>
		/// Gets the size of this Vector.
		/// </summary>
		/// <returns>The number of elements.</returns>
		constexpr Size get_size() const { return m_size; }

		/// <summary>
		/// Gets the internal pointer to the data.
		/// </summary>
		/// <returns>A pointer to the data.</returns>
		constexpr T* get_data() { return mp_data; }

		/// <summary>
		/// Gets the internal pointer to the data.
		/// </summary>
		/// <returns>A pointer to the data.</returns>
		constexpr T const* get_data() const { return mp_data; }

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Resizes the internal array to the given capacity, if it is larger than the current capacity.
		/// </summary>
		/// <param name="capacity">The new capacity of the Vector.</param>
		void reserve(Size const capacity)
		{
			// do nothing if smaller or equal capacity
			if (capacity <= m_capacity)
			{
				return;
			}

			// create new array
			T* newData = static_cast<T*>(allocate(capacity * sizeof(T), m_allocator));

			// clear for good measure
			memset(newData, 0, capacity * sizeof(T));
			
			// move data over, if it exists
			if (mp_data)
			{
				for (Size i = 0; i < m_size; ++i)
				{
					new (&newData[i]) T(std::move(mp_data[i]));
					mp_data[i].~T();
				}
				deallocate(mp_data, m_capacity * sizeof(T), m_allocator);
			}

			// replace data
			mp_data = newData;
			m_capacity = capacity;
		}

		/// <summary>
		/// Resizes the Vector to the given size.
		/// </summary>
		/// <param name="size">The new size of the Vector.</param>
		/// <param name="value">The value to fill the new elements with.</param>
		void resize(Size const size, T const& value)
		{
			// if same size, do nothing
			if (size == m_size)
			{
				return;
			}

			// if larger than capacity, reserve more
			if (size > m_capacity)
			{
				reserve(size);
			}

			// call constructors/destructors
			if (size > m_size)
			{
				for (Size i = m_size; i < size; ++i)
				{
					new (&mp_data[i]) T(value);
				}
			}
			else if (size < m_size)
			{
				for (Size i = size; i < m_size; ++i)
				{
					mp_data[i].~T();
				}
			}

			// set size
			m_size = size;
		}

		/// <summary>
		/// Adds an element to the end of the Vector.
		/// </summary>
		/// <param name="value">The value to add.</param>
		void add(T const& value)
		{
			// if larger than capacity, reserve more
			if (m_size >= m_capacity)
			{
				if (m_capacity == 0)
				{
					reserve(DEFAULT_COLLECTION_SIZE);
				}
				else
				{
					reserve(m_capacity * 2);
				}
			}

			// add value
			void* ptr = &mp_data[m_size++];
			new (ptr) T(value);
		}

		/// <summary>
		/// Adds an element to the end of the Vector.
		/// </summary>
		/// <param name="value">The value to add.</param>
		void add(T&& value)
		{
			// if larger than capacity, reserve more
			if (m_size >= m_capacity)
			{
				if (m_capacity == 0)
				{
					reserve(DEFAULT_COLLECTION_SIZE);
				}
				else
				{
					reserve(m_capacity * 2);
				}
			}

			// add value
			void* ptr = &mp_data[m_size++];
			new (ptr) T(std::move(value));
		}

		/// <summary>
		/// Adds the range of elements to the end of the Vector.
		/// </summary>
		/// <typeparam name="IteratorType">The iterator type to use.</typeparam>
		/// <param name="begin">The beginning of the range.</param>
		/// <param name="end">The end of the range.</param>
		template<typename IteratorType>
		std::enable_if<!std::is_integral<IteratorType>::value, void>::type
		add(IteratorType const& begin, IteratorType const& end)
		{
			for (IteratorType it = begin; it != end; ++it)
			{
				add(*it);
			}
		}

		/// <summary>
		/// Inserts the given value at the given index.
		/// </summary>
		/// <param name="index">The location to insert at.</param>
		/// <param name="value">The value to insert.</param>
		void insert(Size const index, T const& value)
		{
			MINTY_ASSERT(index <= m_size, "Index is out of bounds.");

			// add to end
			if (index == m_size)
			{
				add(value);
				return;
			}

			// if larger than capacity, reserve more
			if (m_size >= m_capacity)
			{
				if (m_capacity == 0)
				{
					reserve(DEFAULT_COLLECTION_SIZE);
				}
				else
				{
					reserve(m_capacity * 2);
				}
			}

			// move data
			for (Size i = m_size; i > index; --i)
			{
				mp_data[i] = std::move(mp_data[i - 1]);
			}

			// add value
			mp_data[index] = value;
			++m_size;
		}

		/// <summary>
		/// Inserts the given value at the given index.
		/// </summary>
		/// <param name="index">The location to insert at.</param>
		/// <param name="value">The value to insert.</param>
		void insert(Size const index, T&& value)
		{
			MINTY_ASSERT(index <= m_size, "Index is out of bounds.");

			// add to end
			if (index == m_size)
			{
				add(std::move(value));
				return;
			}

			// if larger than capacity, reserve more
			if (m_size >= m_capacity)
			{
				if (m_capacity == 0)
				{
					reserve(DEFAULT_COLLECTION_SIZE);
				}
				else
				{
					reserve(m_capacity * 2);
				}
			}

			// move data
			for (Size i = m_size; i > index; --i)
			{
				mp_data[i] = std::move(mp_data[i - 1]);
			}

			// add value
			mp_data[index] = std::move(value);
			++m_size;
		}

		/// <summary>
		/// Inserts the given value at the given iterator position.
		/// </summary>
		/// <typeparam name="IteratorType">The iterator type to use.</typeparam>
		/// <param name="it">The iterator to insert at.</param>
		/// <param name="value">The value to insert.</param>
		template<typename IteratorType>
		typename std::enable_if<!std::is_integral<IteratorType>::value, void>::type
		insert(IteratorType const& it, T const& value)
		{
			insert(&(*it) - mp_data, value);
		}

		/// <summary>
		/// Inserts the given value at the given iterator position.
		/// </summary>
		/// <typeparam name="IteratorType">The iterator type to use.</typeparam>
		/// <param name="it">The iterator to insert at.</param>
		/// <param name="value">The value to insert.</param>
		template<typename IteratorType>
		typename std::enable_if<!std::is_integral<IteratorType>::value, void>::type
		insert(IteratorType const& it, T&& value)
		{
			insert(&(*it) - mp_data, std::move(value));
		}

		/// <summary>
		/// Inserts the range of elements at the given index.
		/// </summary>
		/// <typeparam name="IteratorType">The type of iterator.</typeparam>
		/// <param name="index">The index to insert at.</param>
		/// <param name="begin">The beginning of the range.</param>
		/// <param name="end">The end of the range.</param>
		template<typename IteratorType>
		typename std::enable_if<!std::is_integral<IteratorType>::value, void>::type
		insert(Size const index, IteratorType const& begin, IteratorType const& end)
		{
			MINTY_ASSERT(index <= m_size, "Index is out of bounds.");

			// add to end
			if (index == m_size)
			{
				add(begin, end);
				return;
			}

			// get count
			Size count = 0;
			for (IteratorType it = begin; it != end; ++it)
			{
				++count;
			}

			// make space for elements
			if (m_size + count > m_capacity)
			{
				if (m_capacity * 2 >= m_size + count)
				{
					reserve(m_capacity * 2);
				}
				else
				{
					reserve(m_capacity + count);
				}
			}

			// move data
			for (Size i = m_size - 1; i >= index; --i)
			{
				mp_data[i + count] = std::move(mp_data[i]);
			}

			// add values
			Size i = index;
			for (IteratorType it = begin; it != end; ++it)
			{
				mp_data[i++] = *it;
			}

			// increment size
			m_size += count;
		}

		/// <summary>
		/// Inserts the range of elements at the given iterator.
		/// </summary>
		/// <typeparam name="InsertIteratorType">The type of iterator.</typeparam>
		/// <typeparam name="IteratorType">The type of iterator.</typeparam>
		/// <param name="it">The iterator to insert at.</param>
		/// <param name="begin">The beginning of the range.</param>
		/// <param name="end">The end of the range.</param>
		template<typename InsertIteratorType, typename IteratorType>
		typename std::enable_if<!std::is_integral<InsertIteratorType>::value && !std::is_integral<IteratorType>::value, void>::type
		insert(InsertIteratorType const& it, IteratorType const& begin, IteratorType const& end)
		{
			Size index = &(*it) - mp_data;
			insert(index, begin, end);
		}

		/// <summary>
		/// Removes the element at the given index.
		/// </summary>
		/// <param name="index">The index to remove the element from.</param>
		void remove(Size const index)
		{
			MINTY_ASSERT(index < m_size, "Index is out of bounds.");

			// call destructor
			mp_data[index].~T();

			// move data
			for (Size i = index; i < m_size - 1; ++i)
			{
				mp_data[i] = std::move(mp_data[i + 1]);
			}

			// decrement size
			--m_size;
		}

		/// <summary>
		/// Removes the element at the given iterator.
		/// </summary>
		/// <typeparam name="IteratorType">The type of iterator.</typeparam>
		/// <param name="it">The iterator for the element to be removed.</param>
		template<typename IteratorType>
		typename std::enable_if<!std::is_integral<IteratorType>::value, void>::type
		remove(IteratorType const& it)
		{
			remove(&(*it) - mp_data);
		}

		/// <summary>
		/// Removes a range of elements from the Vector.
		/// </summary>
		/// <param name="index">The first element to remove.</param>
		/// <param name="count">The number of elements to remove.</param>
		void remove(Size const index, Size const count)
		{
			MINTY_ASSERT(index < m_size, "Begin index is out of bounds.");
			MINTY_ASSERT(index + count <= m_size, "End index is out of bounds.");
			MINTY_ASSERT(count != 0, "Cannot remove zero elements.");

			// call destructors
			for (Size i = index; i < index + count; ++i)
			{
				mp_data[i].~T();
			}

			// move data
			for (Size i = index; i < m_size - count; ++i)
			{
				mp_data[i] = std::move(mp_data[i + count]);
			}

			// decrement size
			m_size -= count;
		}

		/// <summary>
		/// Removes a range of elements from the Vector.
		/// </summary>
		/// <typeparam name="IteratorType">The type of iterator.</typeparam>
		/// <param name="begin">The first element to remove.</param>
		/// <param name="end">The end of the range of elements to remove.</param>
		template<typename IteratorType>
		typename std::enable_if<!std::is_integral<IteratorType>::value, void>::type
		remove(IteratorType const& begin, IteratorType const& end)
		{
			Size index = &(*begin) - mp_data;
			Size count = &(*end) - mp_data - index;
			remove(index, count);
		}

		/// <summary>
		/// Checks if this Vector is empty.
		/// </summary>
		/// <returns>True, if the size is zero.</returns>
		Bool is_empty() const { return m_size == 0; }

		/// <summary>
		/// Gets the element at the given index.
		/// </summary>
		/// <param name="index">The index of the element.</param>
		/// <returns>The element at the given index.</returns>
		constexpr T& at(Size const index)
		{
			MINTY_ASSERT(index < m_size, "Index is out of bounds.");
			return mp_data[index];
		}

		/// <summary>
		/// Gets the element at the given index.
		/// </summary>
		/// <param name="index">The index of the element.</param>
		/// <returns>The element at the given index.</returns>
		constexpr T const& at(Size const index) const
		{
			MINTY_ASSERT(index < m_size, "Index is out of bounds.");
			return mp_data[index];
		}

		/// <summary>
		/// Gets the first element in the Vector.
		/// </summary>
		/// <returns>The first element.</returns>
		constexpr T& front() { return at(0); }

		/// <summary>
		/// Gets the first element in the Vector.
		/// </summary>
		/// <returns>The first element.</returns>
		constexpr T const& front() const { return at(0); }

		/// <summary>
		/// Gets the last element in the Vector.
		/// </summary>
		/// <returns>The last element.</returns>
		constexpr T& back() { return at(m_size - 1); }

		/// <summary>
		/// Gets the last element in the Vector.
		/// </summary>
		/// <returns>The last element.</returns>
		constexpr T const& back() const { return at(m_size - 1); }

		/// <summary>
		/// Creates a Vector with the elements from the given start index to the given length.
		/// </summary>
		/// <param name="index">The starting index to create the Vector at.</param>
		/// <param name="length">Number of elements to put into the sub Vector.</param>
		/// <returns>An Vector with the copied elements in the given range.</returns>
		constexpr Vector<T> sub(Size const index, Size const length) const
		{
			MINTY_ASSERT(index < m_size, "Start index is out of bounds.");
			MINTY_ASSERT(index + length <= m_size, "Index + length is out of bounds.");
			MINTY_ASSERT(length > 0, "Length must be greater than zero.");

			// create new array
			Vector result(length);
			for (Size i = 0; i < length; ++i)
			{
				result.add(mp_data[index + i]);
			}

			return result;
		}

		/// <summary>
		/// Finds the first occurrence of the given value.
		/// </summary>
		/// <param name="value">The value to find.</param>
		/// <returns>An Iterator to the value, if found.</returns>
		constexpr Iterator find(T const& value)
		{
			for (Size i = 0; i < m_size; ++i)
			{
				if (mp_data[i] == value)
				{
					return Iterator(mp_data + i);
				}
			}

			return end();
		}

		/// <summary>
		/// Finds the first occurrence of the given value.
		/// </summary>
		/// <param name="value">The value to find.</param>
		/// <returns>An Iterator to the value, if found.</returns>
		constexpr ConstIterator find(T const& value) const
		{
			for (Size i = 0; i < m_size; ++i)
			{
				if (mp_data[i] == value)
				{
					return ConstIterator(mp_data + i);
				}
			}

			return end();
		}

		/// <summary>
		/// Checks if the given Value is within this Vector.
		/// </summary>
		/// <param name="value">The value to check.</param>
		/// <returns>True, if the value exists.</returns>
		constexpr Bool contains(T const& value) const { return find(value) != end(); }

		/// <summary>
		/// Removes all elements from the Vector.
		/// </summary>
		void clear()
		{
			for (Size i = 0; i < m_size; ++i)
			{
				mp_data[i].~T();
			}
			m_size = 0;
		}

		inline void push(T const& value)
		{
			add(value);
		}

		inline void push(T&& value)
		{
			add(std::move(value));
		}

		inline T& peek()
		{
			return back();
		}

		inline T const& peek() const
		{
			return back();
		}

		T pop()
		{
			MINTY_ASSERT(m_size > 0, "Cannot pop from an empty Vector.");
			return std::move(mp_data[--m_size]);
		}

#pragma endregion
	};
}