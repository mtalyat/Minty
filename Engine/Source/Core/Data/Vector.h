#pragma once

/**
 * @file Vector.h
 * @brief Common vector type definitions for the platform.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"
#include "Core/Constant/Default.h"
#include "Core/Constant/Limit.h"
#include "Core/Debug/Debug.h"
#include "Core/Memory/DefaultAllocator.h"
#include "Core/Math/Math.h"
#include "Span.h"
#include <initializer_list>

namespace Minty
{
    /**
     * @brief A resizable array.
     * @tparam T The type of the elements in the vector.
     */
    template <typename T, typename Allocator = DefaultAllocator>
    class Vector
    {
#pragma region Type

	public:
		using Iterator = T *;
		using ConstIterator = T const *;

#pragma endregion

#pragma region Constructor

    public:
		/**
		 * @brief Creates an empty Vector.
		 */
        Vector() : mp_data{nullptr}, m_size{0}, m_capacity{0}, m_allocator{} {}

		/**
		 * @brief Creates a Vector with the given initial capacity.
		 * @param capacity The initial capacity of the Vector.
		 */
		Vector(Size const capacity)
			: mp_data(nullptr), m_size(0), m_capacity(0), m_allocator()
		{
			reserve(capacity);
		}

		/**
		 * @brief Creates a Vector with the given size, initializing all elements to the given value.
		 * @param size The size of the Vector.
		 * @param value The value to initialize the elements with.
		 */
		Vector(Size const size, T const &value)
			: mp_data(nullptr), m_size(0), m_capacity(0), m_allocator()
		{
			resize(size, value);
		}

		/**
		 * @brief Creates a Vector with the elements from the given initializer list.
		 * @param list The initializer list containing the elements to add to the Vector.
		 */
		Vector(std::initializer_list<T> const &list)
			: mp_data(nullptr), m_size(0), m_capacity(0), m_allocator()
		{
			reserve(list.size());

			for (T const &value : list)
			{
				add(value);
			}
		}

		Vector(Vector const &other)
			: mp_data(nullptr), m_size(other.m_size), m_capacity(other.m_capacity), m_allocator()
		{
			if (m_size == 0)
			{
				return;
			}
			mp_data = m_allocator.allocate<T>(m_capacity);
			for (Size i = 0; i < m_size; ++i)
			{
				new (&mp_data[i]) T(other.mp_data[i]);
			}
		}

		Vector(Vector &&other) noexcept
			: mp_data(other.mp_data), m_size(other.m_size), m_capacity(other.m_capacity), m_allocator(std::move(other.m_allocator))
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
				m_allocator.deallocate(mp_data);
			}
		}

#pragma endregion

#pragma region Iterator

    public:
        T *begin()
        {
            return mp_data;
        }

        T const *begin() const
        {
            return mp_data;
        }

        T *end()
        {
            return mp_data + m_size;
        }

        T const *end() const
        {
            return mp_data + m_size;
        }

#pragma endregion

#pragma region Operator

    public:
        T &operator[](Size const index)
        {
            MINTY_ASSERT(index < m_size, ErrorCodeEnum::Argument_OutOfRange);
            return mp_data[index];
        }

        T const &operator[](Size const index) const
        {
            MINTY_ASSERT(index < m_size, ErrorCodeEnum::Argument_OutOfRange);
            return mp_data[index];
        }

		Vector &operator=(Vector const &other)
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
					m_allocator.deallocate(mp_data);
				}

				// copy data from other
				m_capacity = other.m_capacity;
				m_size = other.m_size;
				if (m_size == 0)
				{
					mp_data = nullptr;
				}
				else
				{
					mp_data = m_allocator.allocate<T>(m_capacity);
					MINTY_ASSERT(mp_data != nullptr, ErrorCodeEnum::Memory_AllocationFailed);
					for (Size i = 0; i < m_size; ++i)
					{
						new (&mp_data[i]) T(other.mp_data[i]);
					}
				}
			}
			return *this;
		}

		Vector &operator=(Vector &&other) noexcept
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
					m_allocator.deallocate(mp_data);
				}

				// move data from other
				mp_data = other.mp_data;
				m_size = other.m_size;
				m_capacity = other.m_capacity;
				m_allocator = std::move(other.m_allocator);
				other.mp_data = nullptr;
				other.m_size = 0;
				other.m_capacity = 0;
			}
			return *this;
		}

		// Implicit conversion to Span
		operator Span<T>() const { return Span<T>(mp_data, m_size); }

		// Implicit conversion to View
		operator View() const { return View(mp_data, m_size); }

#pragma endregion

#pragma region Accessor

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
		inline T *get_data() { return mp_data; }

		/**
		 * @brief Gets the internal pointer to the data.
		 * @returns A const pointer to the data.
		 */
		inline T const *get_data() const { return mp_data; }

		/**
		 * @brief Checks if this Vector is empty.
		 * @returns True, if the size is zero.
		 */
		inline Bool is_empty() const { return get_size() == 0; }

#pragma endregion

#pragma region Method

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
			T *newData = m_allocator.allocate<T>(capacity);
			MINTY_ASSERT(newData != nullptr, ErrorCodeEnum::Memory_AllocationFailed);

			// move data over, if it exists
			for (Size i = 0; i < m_size; ++i)
			{
				new (&newData[i]) T(std::move(mp_data[i]));
			}

			// replace data
			if (mp_data)
			{
				// data has been moved, so just deallocate old array
				for (Size i = 0; i < m_size; ++i)
				{
					mp_data[i].~T();
				}
				m_allocator.deallocate(mp_data);
			}
			mp_data = newData;
			m_capacity = capacity;
		}

		/**
		 * @brief Resizes the Vector to the given size, initializing new elements with the given value.
		 * @param size The new size of the Vector.
		 */
		template <typename... Args>
		void resize(Size const size, Args &&...args)
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
						// Intentionally do not forward here: forwarding rvalue args repeatedly would
						// move from the same object multiple times across iterations.
						new (&mp_data[i]) T(args...);
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
		void add(T const &value)
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
		void add(T &&value)
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
		void insert(Size const index, T const &value)
		{
			MINTY_ASSERT_A(index <= get_size(), ErrorCodeEnum::Argument_OutOfRange, index);

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
		void insert(Size const index, T &&value)
		{
			MINTY_ASSERT_A(index <= get_size(), ErrorCodeEnum::Argument_OutOfRange, index);

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
			MINTY_ASSERT_A(index < get_size(), ErrorCodeEnum::Argument_OutOfRange, index);

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
			MINTY_ASSERT_A(index < get_size(), ErrorCodeEnum::Argument_OutOfRange, index);
			MINTY_ASSERT_A(index + count <= get_size(), ErrorCodeEnum::Argument_InvalidSize, count);
			MINTY_ASSERT(count != 0, ErrorCodeEnum::Argument_ExpectedNonZero);

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
		inline T &at(Size const index)
		{
			MINTY_ASSERT_A(index < get_size(), ErrorCodeEnum::Argument_OutOfRange, index);
			return mp_data[index];
		}

		/**
		 * @brief Gets the element at the given index.
		 * @param index The index of the element.
		 * @returns A const reference to the element at the given index.
		 */
		inline T const &at(Size const index) const
		{
			MINTY_ASSERT_A(index < get_size(), ErrorCodeEnum::Argument_OutOfRange, index);
			return mp_data[index];
		}

		/**
		 * @brief Gets the first element in the Vector.
		 * @returns The first element.
		 */
		inline T &front() { return at(0); }

		/**
		 * @brief Gets the first element in the Vector.
		 * @returns The first element.
		 */
		inline T const &front() const { return at(0); }

		/**
		 * @brief Gets the last element in the Vector.
		 * @returns The last element.
		 */
		inline T &back() { return at(get_size() - 1); }

		/**
		 * @brief Gets the last element in the Vector.
		 * @returns The last element.
		 */
		inline T const &back() const { return at(get_size() - 1); }

		/**
		 * @brief Creates a sub-Vector from the given index and length.
		 * @param index The starting index of the sub-Vector.
		 * @param length The number of elements in the sub-Vector.
		 * @returns A new Vector containing the specified range of elements.
		 */
		Vector<T> sub(Size const index, Size const length) const
		{
			MINTY_ASSERT_A(index < get_size(), ErrorCodeEnum::Argument_OutOfRange, index);
			MINTY_ASSERT_A(index + length <= get_size(), ErrorCodeEnum::Argument_InvalidSize, length);
			MINTY_ASSERT(length > 0, ErrorCodeEnum::Argument_ExpectedNonZero);

			// create new array
			Vector result(length);
			for (Size i = 0; i < length; ++i)
			{
				result.add(mp_data[index + i]);
			}

			return result;
		}

        Span<T> span(Size const index = 0, Size const length = MAX_SIZE) const
        {
			MINTY_ASSERT_A(is_empty() || index < get_size(), ErrorCodeEnum::Argument_OutOfRange, index);
			MINTY_ASSERT_A(length == MAX_SIZE || index + length <= get_size(), ErrorCodeEnum::Argument_InvalidSize, length);

            return Span<T>(mp_data + index, Math::min(length, get_size() - index));
        }

		View view(Size const index = 0, Size const length = MAX_SIZE) const
		{
			MINTY_ASSERT_A(is_empty() || index < get_size(), ErrorCodeEnum::Argument_OutOfRange, index);
			MINTY_ASSERT_A(length == MAX_SIZE || index + length <= get_size(), ErrorCodeEnum::Argument_InvalidSize, length);

			return View(mp_data + index, Math::min(length, get_size() - index));
		}

		/**
		 * @brief Finds the first occurrence of the given value.
		 * @param value The value to find.
		 */
		Iterator find(T const &value)
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
		ConstIterator find(T const &value) const
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
		inline Bool contains(T const &value) const { return find(value) != end(); }

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

#pragma region Variable

    public:
        T *mp_data;
        Size m_size;
        Size m_capacity;
		Allocator m_allocator;

#pragma endregion
    };
}