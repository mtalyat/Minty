#pragma once
#include "Minty/Core/Base.h"
#include "Minty/Core/Constant.h"
#include "Minty/Core/Macro.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/String.h"
#include <filesystem>

namespace Minty
{
	/// <summary>
	/// A collection of text representing a file path.
	/// </summary>
	class Path
	{
#pragma region Iterators

	public:
		class Iterator
		{
			friend class Path;

		public:
			using iterator_category = std::forward_iterator_tag;
			using value_type = Path;
			using difference_type = std::ptrdiff_t;
			using pointer = value_type*;
			using reference = value_type&;

		private:
			std::filesystem::path::iterator m_it;
			Path* mp_current;

		private:
			explicit Iterator(std::filesystem::path::iterator const it)
				: m_it(it)
				, mp_current(nullptr)
			{
				if (m_it != std::filesystem::path::iterator())
				{
					mp_current = new Path(m_it->string().c_str());
				}
			}

			Iterator(Iterator const& other)
				: m_it(other.m_it)
				, mp_current(new Path(*other.mp_current))
			{
			}

			~Iterator()
			{
				if (mp_current)
				{
					delete mp_current;
				}
			}

		public:
			reference operator*() const
			{
				MINTY_ASSERT(mp_current, "Path Iterator is invalid.");
				return *mp_current;
			}

			pointer operator->() const
			{
				MINTY_ASSERT(mp_current, "Path Iterator is invalid.");
				return mp_current;
			}

			Iterator& operator++()
			{
				++m_it;
				*mp_current = Path(m_it->string().c_str());
				return *this;
			}

			Iterator operator++(int)
			{
				Iterator temp = *this;
				++m_it;
				*mp_current = Path(m_it->string().c_str());
				return temp;
			}

			Bool operator==(Iterator const& other) const { return m_it == other.m_it; }
			Bool operator!=(Iterator const& other) const { return m_it != other.m_it; }
		};

		class ConstIterator
		{
			friend class Path;

		public:
			using iterator_category = std::forward_iterator_tag;
			using value_type = Path const;
			using difference_type = std::ptrdiff_t;
			using pointer = value_type*;
			using reference = value_type&;

		private:
			std::filesystem::path::const_iterator m_it;
			Path* mp_current;

		private:
			explicit ConstIterator(std::filesystem::path::const_iterator const it)
				: m_it(it)
				, mp_current(nullptr)
			{
				if (m_it != std::filesystem::path::const_iterator())
				{
					mp_current = new Path(m_it->string().c_str());
				}
			}

			ConstIterator(ConstIterator const& other)
				: m_it(other.m_it)
				, mp_current(new Path(*other.mp_current))
			{
			}

			~ConstIterator()
			{
				if (mp_current)
				{
					delete mp_current;
				}
			}

		public:
			reference operator*() const
			{
				MINTY_ASSERT(mp_current, "Path ConstIterator is invalid.");
				return *mp_current;
			}

			pointer operator->() const
			{
				MINTY_ASSERT(mp_current, "Path ConstIterator is invalid.");
				return mp_current;
			}

			ConstIterator& operator++()
			{
				++m_it;
				*mp_current = Path(m_it->string().c_str());
				return *this;
			}

			ConstIterator operator++(int)
			{
				ConstIterator temp = *this;
				++m_it;
				*mp_current = Path(m_it->string().c_str());
				return temp;
			}

			Bool operator==(ConstIterator const& other) const { return m_it == other.m_it; }
			Bool operator!=(ConstIterator const& other) const { return m_it != other.m_it; }
		};

		/// <summary>
		/// Gets an Iterator to the beginning of the Path.
		/// </summary>
		/// <returns>An Iterator pointing to the first character.</returns>
		Iterator begin() { return Iterator(m_path.begin()); }

		/// <summary>
		/// Gets an Iterator to the end of the Path.
		/// </summary>
		/// <returns>An Iterator pointing to the null terminating character.</returns>
		Iterator end() { return Iterator(m_path.end()); }

		/// <summary>
		/// Gets an Iterator to the beginning of the Path.
		/// </summary>
		/// <returns>An Iterator pointing to the first character.</returns>
		ConstIterator cbegin() const { return ConstIterator(m_path.begin()); }

		/// <summary>
		/// Gets an Iterator to the end of the Path.
		/// </summary>
		/// <returns>An Iterator pointing to the null terminating character.</returns>
		ConstIterator cend() const { return ConstIterator(m_path.end()); }

#pragma endregion

#pragma region Variables

	private:
		std::filesystem::path m_path;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates an empty Path.
		/// </summary>
		/// <param name="allocator">The Allocator to use.</param>
		constexpr Path(Allocator const allocator = Allocator::Default)
			: m_path()
		{
		}

		/// <summary>
		/// Creates a Path based on the given String.
		/// </summary>
		/// <param name="string">The String to create the Path from.</param>
		/// <param name="allocator">The Allocator to use.</param>
		Path(String const& string, Allocator const allocator = Allocator::Default);

		/// <summary>
		/// Creates a Path and copies the given data.
		/// </summary>
		/// <param name="data">The text to copy.</param>
		/// <param name="allocator">The Allocator to use.</param>
		Path(Char const* data, Allocator const allocator = Allocator::Default);

#pragma endregion

#pragma region Operators

	public:
		Bool operator==(Path const& other) const
		{
			return m_path == other.m_path;
		}

		Bool operator!=(Path const& other) const
		{
			return !(*this == other);
		}

		Bool operator<(Path const& other) const
		{
			return m_path < other.m_path;
		}

		Bool operator>(Path const& other) const
		{
			return other < *this;
		}

		Bool operator<=(Path const& other) const
		{
			return !(other < *this);
		}

		Bool operator>=(Path const& other) const
		{
			return !(*this < other);
		}

		Path operator+(Path const& other) const;

		Path operator/(Path const& other) const;

		Path& operator+=(Path const& other)
		{
			return append(other);
		}

		Path& operator/=(Path const& other)
		{
			return append(other);
		}

		friend std::ostream& operator<<(std::ostream& stream, Path const& str);

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the capacity of the Path.
		/// </summary>
		/// <returns>The capacity.</returns>
		constexpr Size get_capacity() const { return m_path.string().capacity(); }

		/// <summary>
		/// Gets the size of the Path.
		/// </summary>
		/// <returns>The size.</returns>
		constexpr Size get_size() const { return m_path.string().size(); }

		/// <summary>
		/// Gets the internal String of this Path.
		/// </summary>
		/// <returns></returns>
		String get_string() const { return String(m_path.generic_string().c_str()); }

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Allocates characters using the given capacity.
		/// </summary>
		/// <param name="capacity">The new capacity.</param>
		void reserve(Size const capacity);

		/// <summary>
		/// Adds the given Path to the end of this Path.
		/// </summary>
		/// <param name="other">The Path to add.</param>
		/// <returns>This Path, with the other Path appended.</returns>
		Path& append(Path const& other);

		/// <summary>
		/// Checks if this Path is empty.
		/// </summary>
		/// <returns>True if the Path is empty.</returns>
		constexpr Bool is_empty() const { return get_size() == 0; }

#pragma endregion
	};
}