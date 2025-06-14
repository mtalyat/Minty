#pragma once
#include "Minty/Core/Base.h"
#include "Minty/Core/Constant.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/String.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Serialization/Parseable.h"
#include <filesystem>

namespace Minty
{
	/// <summary>
	/// A collection of text representing a file path.
	/// </summary>
	class Path
		: public Parseable
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
				mp_current = new Path(m_it->string().c_str());
			}

			Iterator(Iterator const& other)
				: m_it(other.m_it)
				, mp_current(new Path(*other.mp_current))
			{
			}

		public:
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
				mp_current = new Path(m_it->string().c_str());
			}

		public:
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
		ConstIterator begin() const { return ConstIterator(m_path.begin()); }

		/// <summary>
		/// Gets an Iterator to the end of the Path.
		/// </summary>
		/// <returns>An Iterator pointing to the null terminating character.</returns>
		ConstIterator end() const { return ConstIterator(m_path.end()); }

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
		/// <returns>The String form of this Path.</returns>
		String get_string() const { return String(m_path.generic_string().c_str()); }

		/// <summary>
		/// Gets the absolute path of this Path.
		/// </summary>
		/// <returns>The full path.</returns>
		Path get_absolute() const;

		/// <summary>
		/// Gets the last extension of this Path.
		/// </summary>
		/// <returns>A path with just the extension.</returns>
		Path get_extension() const;

		/// <summary>
		/// Gets the full extension of this Path, including multiple extensions.
		/// </summary>
		/// <returns>A path with just the extension.</returns>
		Path get_extension_full() const;

		/// <summary>
		/// Gets the lexically relative path to the given Path.
		/// </summary>
		/// <param name="other">The destination Path.</param>
		/// <returns>A new Path, relative from this Path to the given Path.</returns>
		Path get_relative_to(Path const& other) const;

		/// <summary>
		/// Gets the parent directory's Path.
		/// </summary>
		/// <returns>The Path to the parent.</returns>
		Path get_parent() const;

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

		/// <summary>
		/// Checks if this Path has an extension.
		/// </summary>
		/// <returns>True, if there is an extension.</returns>
		Bool has_extension() const { return m_path.has_extension(); }

		/// <summary>
		/// Checks if this Path has the given extension.
		/// </summary>
		/// <param name="extension">The extension to check for, including the '.'.</param>
		/// <returns>True if the path has the given extension.</returns>
		Bool has_extension(Path const& extension) const
		{
			return m_path.has_extension() && m_path.extension() == extension.m_path;
		}

		/// <summary>
		/// Checks if this Path has a parent directory.
		/// </summary>
		/// <returns>True if there is a parent directory.</returns>
		Bool has_parent() const { return m_path.has_parent_path(); }

		/// <summary>
		/// Gets the extension of this Path.
		/// </summary>
		/// <returns>A Path with the extension.</returns>
		Path get_extension() { return Path(m_path.extension().string().c_str()); }

		/// <summary>
		/// Gets the name of the file.
		/// </summary>
		/// <returns>A Path with the file name and extension.</returns>
		Path get_file_name() const { return Path(m_path.filename().string().c_str()); }

		/// <summary>
		/// Gets the name of the file without the extension.
		/// </summary>
		/// <returns>A Path with the file name.</returns>
		Path get_name() const { return Path(m_path.stem().string().c_str()); }

		/// <summary>
		/// Reads the data for this object from a String.
		/// </summary>
		/// <param name="text">A String of this object.</param>
		/// <returns>True on success.</returns>
		Bool parse(String const& text) override;

		/// <summary>
		/// Converts the data in this object to a String.
		/// </summary>
		/// <returns>A String of this object.</returns>
		String to_string() const override;

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Checks if the given Path exists.
		/// </summary>
		/// <param name="path">The Path to check.</param>
		/// <returns>True, if the path is valid and exists on the disk.</returns>
		static Bool exists(Path const& path);

		/// <summary>
		/// Checks if the given Path exists and is a file.
		/// </summary>
		/// <param name="path">The Path to check.</param>
		/// <returns>True, if the path is a file and exists on the disk.</returns>
		static Bool is_file(Path const& path);

		/// <summary>
		/// Checks if the given Path exists and is a directory.
		/// </summary>
		/// <param name="path">The Path to check.</param>
		/// <returns>True, if the path is a directory and exists on the disk.</returns>
		static Bool is_directory(Path const& path);

		/// <summary>
		/// Gets the size of the File at the given Path.
		/// </summary>
		/// <param name="path">The Path to the File.</param>
		/// <returns>The size of the File in Bytes.</returns>
		static Size get_file_size(Path const& path);

		/// <summary>
		/// Gets the files within the directory at the given Path.
		/// </summary>
		/// <param name="path">The path to the directory.</param>
		/// <param name="recursive">If true, get the sub-directory files as well.</param>
		/// <returns>A Vector of Paths to the Files within directory at the given Path.</returns>
		static Vector<Path> get_files(Path const& path, Bool const recursive = false);

		/// <summary>
		/// Gets the directories within the directory at the given Path.
		/// </summary>
		/// <param name="path">The path to the directory.</param>
		/// <param name="recursive">If true, get the sub-directory directories as well.</param>
		/// <returns>A Vector of Paths to the directories within directory at the given Path.</returns>
		static Vector<Path> get_directories(Path const& path, Bool const recursive = false);

		/// <summary>
		/// Gets all of the files and directories within the directory at the given Path.
		/// </summary>
		/// <param name="path">The path to the directory.</param>
		/// <param name="recursive">If true, get the sub-directory files and directories as well.</param>
		/// <returns>A Vector of Paths to the files and directories within directory at the given Path.</returns>
		static Vector<Path> get_contents(Path const& path, Bool const recursive = false);

		/// <summary>
		/// Creates the directories at the given Path.
		/// </summary>
		/// <param name="path">The Path to create.</param>
		/// <returns>True, if the directories were created.</returns>
		static Bool create(Path const& path);

#pragma endregion
	};
}

namespace std
{
	template<>
	struct hash<Minty::Path>
	{
		std::size_t operator()(Minty::Path const& path) const noexcept
		{
			return std::hash<std::string>{}(std::string(path.get_string().get_data()));
		}
	};
}