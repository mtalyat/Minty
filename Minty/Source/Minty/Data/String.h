#pragma once
#include "Minty/Core/Constant.h"
#include "Minty/Core/Macro.h"
#include "Minty/Core/Types.h"
#include <utility>

namespace Minty
{
	class String
	{
#pragma region Variables

	private:
		Size m_capacity;
		Size m_size;
		Char* mp_data;

#pragma endregion

#pragma region Constructors

	public:
		constexpr String()
			: m_capacity(0)
			, m_size(0)
			, mp_data(nullptr)
		{}

		String(Size const capacity);

		String(Char const* data);

		String(String const& other)
			: m_capacity(other.m_capacity)
			, m_size(other.m_size)
			, mp_data(new Char[m_capacity + 1])
		{
			memcpy(mp_data, other.mp_data, m_size * sizeof(Char));
			mp_data[m_size] = '\0';
		}

		String(String&& other) noexcept
			: m_capacity(other.m_capacity)
			, m_size(other.m_size)
			, mp_data(other.mp_data)
		{
			other.m_capacity = 0;
			other.m_size = 0;
			other.mp_data = nullptr;
		}

		~String();

#pragma endregion

#pragma region Operators

	public:
		String& operator=(String const& other)
		{
			if (this != &other)
			{
				if (m_capacity < other.m_size)
				{
					delete[] mp_data;
					mp_data = new Char[other.m_capacity + 1];
					m_capacity = other.m_capacity;
				}
				m_size = other.m_size;
				memcpy(mp_data, other.mp_data, m_size * sizeof(Char));
				mp_data[m_size] = '\0';
			}
			return *this;
		}

		String& operator=(String&& other) noexcept
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
				other.m_capacity = 0;
				other.m_size = 0;
				other.mp_data = nullptr;
			}
			return *this;
		}

		Char operator[](Size const index) const
		{
			return at(index);
		}

		Bool operator==(String const& other) const
		{
			return m_size == other.m_size && memcmp(mp_data, other.mp_data, m_size * sizeof(Char)) == 0;
		}

		Bool operator!=(String const& other) const
		{
			return !(*this == other);
		}

		Bool operator<(String const& other) const
		{
			Size const length = m_size < other.m_size ? m_size : other.m_size;
			int result = std::memcmp(mp_data, other.mp_data, length);

			if (result < 0) {
				return true;
			}
			else if (result > 0) {
				return false;
			}
			return m_size < other.m_size;
		}

		Bool operator>(String const& other) const
		{
			return other < *this;
		}

		Bool operator<=(String const& other) const
		{
			return !(other < *this);
		}

		Bool operator>=(String const& other) const
		{
			return !(*this < other);
		}

#pragma endregion

#pragma region Get Set

	public:
		constexpr Size get_capacity() const { return m_capacity; }

		constexpr Size get_size() const { return m_size; }

		constexpr Char* get_data() const { return mp_data; }

#pragma endregion

#pragma region Methods

	public:
		void reserve(Size const capacity);

		void resize(Size const size);

		constexpr Bool is_empty() const { return m_size == 0; }

		constexpr Char at(Size const index) const
		{
			MINTY_ASSERT(index < m_size, "The given index is out of range.");
			return mp_data[index];
		}

		String sub(Size const start, Size const length) const;

		Size find(String const& sub) const;

		Bool contains(String const& sub) const
		{
			return find(sub) != INVALID_INDEX;
		}

#pragma endregion
	};
}