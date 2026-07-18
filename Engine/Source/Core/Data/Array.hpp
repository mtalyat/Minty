#pragma once

/**
 * @file Array.h
 * @brief Common array type definitions for the platform.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Alignment.hpp"
#include "Core/Debug/Debug.hpp"

namespace Minty
{
    /**
     * @brief A fixed-size array.
     * @tparam T The type of the elements in the array.
     */
    template <typename T, Size N>
    struct MINTY_ALIGN_TYPE(T, N) Array
    {
#pragma region Constructors

    public:
        constexpr Array() : m_data{} {}

        /**
         * @brief Creates an Array from a C-style array.
         * @param arr The C-style array to copy from.
         */
        constexpr Array(T const (&arr)[N])
        {
            for (Size i = 0; i < N; ++i)
            {
                m_data[i] = arr[i];
            }
        }

		/**
		 * @brief Creates an Array with all elements set to the given value.
		 * @param value The value to set all elements to.
		 */
		explicit constexpr Array(T const &value)
			: m_data()
		{
			for (Size i = 0; i < N; ++i)
			{
				m_data[i] = value;
			}
		}

        constexpr Array(Array const &other) = default;
        constexpr Array(Array &&other) = default;

#pragma endregion

#pragma region Iterators

    public:
        using Iterator = T*;
        using ConstIterator = T const*;

        constexpr Iterator begin()
        {
            return m_data;
        }

        constexpr ConstIterator begin() const
        {
            return m_data;
        }

        constexpr Iterator end()
        {
            return m_data + N;
        }

        constexpr ConstIterator end() const
        {
            return m_data + N;
        }

#pragma endregion

#pragma region Operators

    public:
        constexpr T &operator[](Size const index)
        {
            return m_data[index];
        }

        constexpr T const &operator[](Size const index) const
        {
            return m_data[index];
        }

        constexpr Array &operator=(T const (&arr)[N])
        {
            for (Size i = 0; i < N; ++i)
            {
                m_data[i] = arr[i];
            }
            return *this;
        }

        constexpr Array& operator=(Array const &other) = default;
        constexpr Array& operator=(Array &&other) = default;

#pragma endregion

#pragma region Accessors

    public:
        /**
         * @brief Gets the size of this Array.
         * @return The size.
         */
        constexpr Size get_size() const
        {
            return N;
        }

        /**
         * @brief Gets a pointer to the data of this Array.
         * @return A pointer to the data.
         */
        constexpr T *get_data()
        {
            return m_data;
        }

        /**
         * @brief Gets a pointer to the data of this Array.
         * @return A pointer to the data.
         */
        constexpr T const *get_data() const
        {
            return m_data;
        }

#pragma endregion

#pragma region Methods

    public:
        /**
		 * @brief Gets the element at the given index.
		 * @param index The index of the element.
		 */
		constexpr T &at(Size const index)
		{
			MINTY_ASSERT(index < N, ErrorCodeEnum::Argument_OutOfRange);
			return m_data[index];
		}

		/**
		 * @brief Gets the element at the given index.
		 * @param index The index of the element.
		 */
		constexpr T const &at(Size const index) const
		{
			MINTY_ASSERT(index < N, ErrorCodeEnum::Argument_OutOfRange);
			return m_data[index];
		}

		/**
		 * @brief Gets the first element in the Array.
		 * @returns The first element.
		 */
		constexpr T &front() { return at(0); }

		/**
		 * @brief Gets the first element in the Array.
		 * @returns The first element.
		 */
		constexpr T const &front() const { return at(0); }

		/**
		 * @brief Gets the last element in the Array.
		 * @returns The last element.
		 */
		constexpr T &back() { return at(N - 1); }

		/**
		 * @brief Gets the last element in the Array.
		 * @returns The last element.
		 */
		constexpr T const &back() const { return at(N - 1); }

		/**
		 * @brief Creates a sub-Array from the given start index and size.
		 * @tparam N The size of the sub-Array.
		 * @param start The starting index of the sub-Array.
		 */
		template <Size N>
		constexpr Array<T, N> sub(Size const start) const
		{
			MINTY_ASSERT(start < N, ErrorCodeEnum::Argument_OutOfRange);
			MINTY_ASSERT(start + N <= N, ErrorCodeEnum::Argument_InvalidSize);

			// create new array
			Array<T, N> result;
			for (Size i = 0; i < N; ++i)
			{
				result[i] = m_data[start + i];
			}

			return result;
		}

		/**
		 * @brief Finds the first occurrence of the given value.
		 * @param value The value to find.
		 */
		constexpr Iterator find(T const &value)
		{
			for (Size i = 0; i < N; ++i)
			{
				if (m_data[i] == value)
				{
					return Iterator(m_data + i);
				}
			}

			return end();
		}

		/**
		 * @brief Finds the first occurrence of the given value.
		 * @param value The value to find.
		 */
		constexpr ConstIterator find(T const &value) const
		{
			for (Size i = 0; i < N; ++i)
			{
				if (m_data[i] == value)
				{
					return ConstIterator(m_data + i);
				}
			}

			return end();
		}

		/**
		 * @brief Checks if the Array contains the given value.
		 * @param value The value to check for.
		 * @returns True if the value is found, false otherwise.
		 */
		constexpr Bool contains(T const &value) const { return find(value) != end(); }

#pragma endregion

#pragma region Variables

    private:
        T m_data[N];

#pragma endregion
    };
}
