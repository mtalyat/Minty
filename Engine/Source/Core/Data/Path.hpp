#ifndef MINTY_DATA_PATH_H
#define MINTY_DATA_PATH_H

/**
 * @file Path.hpp
 * @brief Defines the Path class for representing file system paths.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Core/Constant/Default.hpp"
#include "Core/Constant/Invalid.hpp"
#include "Core/Serialize/Parser.hpp"
#include <filesystem>

namespace Minty
{
	/**
	 * @class Path
	 * @brief Represents a file system path.
	 */
	class Path
	{
		friend struct Parser<Path>;

#pragma region Type

	public:
		using DirectoryIterator = std::filesystem::directory_iterator;

#pragma endregion

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
				MINTY_ASSERT(mp_current, ErrorCodeEnum::Object_InvalidState);
				return *mp_current;
			}

			pointer operator->() const
			{
				MINTY_ASSERT(mp_current, ErrorCodeEnum::Object_InvalidState);
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
				MINTY_ASSERT(mp_current, ErrorCodeEnum::Object_InvalidState);
				return *mp_current;
			}

			pointer operator->() const
			{
				MINTY_ASSERT(mp_current, ErrorCodeEnum::Object_InvalidState);
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

		Iterator begin() { return Iterator(m_path.begin()); }
		Iterator end() { return Iterator(m_path.end()); }
		ConstIterator begin() const { return ConstIterator(m_path.begin()); }
		ConstIterator end() const { return ConstIterator(m_path.end()); }

#pragma endregion

#pragma region Constructors

	public:
		/**
		 * @brief Creates an empty Path.
		 * @param allocator The Allocator to use.
		 */
		Path();

		/**
		 * @brief Creates a Path based on the given String.
		 * @param string The String to create the Path from.
		 */
		Path(String const& string);

		/**
		 * @brief Creates a Path based on the given character array.
		 * @param data The character array to create the Path from.
		 */
		Path(Char const* data);

#pragma endregion

#pragma region Operators

	public:
		Bool operator==(Path const& other) const { return m_path == other.m_path; }
		Bool operator!=(Path const& other) const { return !(*this == other); }
		Bool operator<(Path const& other) const { return m_path < other.m_path; }
		Bool operator>(Path const& other) const { return other < *this; }
		Bool operator<=(Path const& other) const { return !(other < *this); }
		Bool operator>=(Path const& other) const { return !(*this < other); }
		Path operator+(Path const& other) const;
		Path operator/(Path const& other) const;
		Path& operator+=(Path const& other) { return append(other); }
		Path& operator/=(Path const& other) { return append(other); }

		friend std::ostream& operator<<(std::ostream& stream, Path const& str);

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the capacity of the Path.
		 * @returns The capacity.
		 */
		inline Size get_capacity() const { return m_path.string().capacity(); }

		/**
		 * @brief Gets the size of the Path.
		 * @returns The size.
		 */
		inline Size get_size() const { return m_path.string().size(); }

		/**
		 * @brief Gets the Path as a String.
		 * @returns The Path as a String.
		 */
		inline String get_string() const { return String(m_path.generic_string().c_str()); }

		/**
		 * @brief Gets the Path relative to another Path.
		 * @param other The other Path.
		 * @returns The relative Path.
		 */
		Path get_relative_to(Path const& other) const;

		/**
		 * @brief Gets the parent directory of this Path.
		 * @returns The parent Path.
		 */
		Path get_parent() const;

		/**
		 * @brief Checks whether this path is absolute.
		 * @returns True if absolute, false if relative.
		 */
		inline Bool is_absolute() const { return m_path.is_absolute(); }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Reserves space for the given capacity.
		 * @param capacity The capacity to reserve.
		 */
		void reserve(Size const capacity);

		/**
		 * @brief Appends another Path to this Path.
		 * @param other The other Path to append.
		 * @returns This Path, with the other Path appended.
		 */
		Path& append(Path const& other);

		/**
		 * @brief Checks if this Path is empty.
		 * @returns True if the Path is empty.
		 */
		inline Bool is_empty() const { return get_size() == 0; }

		/**
		 * @brief Gets the absolute Path.
		 * @returns The absolute Path.
		 */
		Path get_absolute() const;

		/**
		 * @brief Checks if this Path has an extension.
		 * @returns True if the Path has an extension.
		 */
		inline Bool has_extension() const { return m_path.has_extension(); }

		/**
		 * @brief Checks if this Path has the given extension.
		 * @param extension The extension to check for, including the '.'.
		 * @returns True if the path has the given extension.
		 */
		inline Bool has_extension(Path const& extension) const{ return m_path.has_extension() && m_path.extension() == extension.m_path; }

		/**
		 * @brief Checks if this Path has a parent directory.
		 * @returns True if there is a parent directory.
		 */
		inline Bool has_parent() const { return m_path.has_parent_path(); }

		/**
		 * @brief Gets the extension of this Path.
		 * @returns A Path with the extension.
		 */
		Path get_extension() const;

		/**
		 * @brief Gets the full extension of this Path.
		 * @returns A path with the full extension.
		 */
		Path get_extension_full() const;

		/**
		 * @brief Gets the name of the file.
		 * @returns A Path with the file name and extension.
		 */
		inline Path get_file_name() const { return Path(m_path.filename().string().c_str()); }

		/**
		 * @brief Gets the name of the file without the extension.
		 * @returns A Path with the file name.
		 */
		inline Path get_name() const { return Path(m_path.stem().string().c_str()); }

		/**
		 * @brief Gets the directory iterator for this Path.
		 * @returns A DirectoryIterator for this Path.
		 */
		DirectoryIterator get_directory_iterator() const { return DirectoryIterator(m_path); }

		/**
		 * @brief Checks if the given Path exists.
		 * @param path The Path to check.
		 * @returns True, if the path is valid and exists on the disk.
		 */
		static Bool exists(Path const& path);

		/**
		 * @brief Checks if the given Path exists and is a file.
		 * @param path The Path to check.
		 * @returns True, if the path is a file and exists on the disk.
		 */
		static Bool is_file(Path const& path);

		/**
		 * @brief Checks if the given Path exists and is a directory.
		 * @param path The Path to check.
		 * @returns True, if the path is a directory and exists on the disk.
		 */
		static Bool is_directory(Path const& path);

		/**
		 * @brief Gets the size of the File at the given Path.
		 * @param path The Path to the File.
		 * @returns The size of the File in Bytes.
		 */
		static Size get_file_size(Path const& path);

		/**
		 * @brief Creates the directories at the given Path.
		 * @param path The Path to create.
		 * @returns True, if the directories were created.
		 */
		static Bool create(Path const& path);

		/**
		 * @brief Destroys the file or directory at the given Path.
		 * @param path The Path to destroy.
		 */
		static void destroy(Path const& path);

#pragma endregion

#pragma region Variables

	private:
		std::filesystem::path m_path;

#pragma endregion
	};

    template<>
    struct Parser<Path>
    {
        static Bool parse(StringView const str, Path &value);
        static String to_string(Path const &value);
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

#endif // MINTY_DATA_PATH_H