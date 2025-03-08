#pragma once
#include "Minty/Core/Base.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Path.h"
#include <fstream>

namespace Minty
{
	/// <summary>
	/// Handles reading/writing to a file.
	/// </summary>
	class File
	{
#pragma region Types

	public:
		using Position_t = std::streampos;
		using Size_t = std::streamsize;

#pragma endregion

#pragma region Classes

	public:
		/// <summary>
		/// The direction to which accessing the File is relative to.
		/// </summary>
		enum class Direction
		{
			/// <summary>
			/// Refer to the beginning of the File.
			/// </summary>
			Begin = std::ios_base::beg,

			/// <summary>
			/// Refer to the current cursor position.
			/// </summary>
			Current = std::ios_base::cur,

			/// <summary>
			/// Refer to the end of the File.
			/// </summary>
			End = std::ios_base::end,
		};

		/// <summary>
		/// The accessor Flags for a File.
		/// </summary>
		enum class Flags : Int
		{
			/// <summary>
			/// No Flags.
			/// </summary>
			None = 0,

			/// <summary>
			/// Read from the File.
			/// </summary>
			Read = std::ios_base::in,

			/// <summary>
			/// Write to the File.
			/// </summary>
			Write = std::ios_base::out,

			/// <summary>
			/// Read and/or write to the File.
			/// </summary>
			ReadWrite = std::ios_base::in | std::ios_base::out,

			/// <summary>
			/// ???
			/// </summary>
			End = std::ios_base::end,

			/// <summary>
			/// Add to the end of the File.
			/// </summary>
			Append = std::ios_base::app,

			/// <summary>
			/// Cut off all extra existing data in the File.
			/// </summary>
			Truncate = std::ios_base::trunc,

			/// <summary>
			/// Open the File in binary mode.
			/// </summary>
			Binary = std::ios_base::binary,
		};

		friend inline Flags operator|(Flags const left, Flags const right)
		{
			return static_cast<Flags>(static_cast<Int>(left) | static_cast<Int>(right));
		}

		friend inline Flags operator&(Flags const left, Flags const right)
		{
			return static_cast<Flags>(static_cast<Int>(left) & static_cast<Int>(right));
		}

#pragma endregion

#pragma region Variables

	protected:
		Path m_path;
		Flags m_flags;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates an empty File.
		/// </summary>
		File()
			: m_path()
			, m_flags(Flags::None)
		{
		}

		/// <summary>
		/// Creates a File with the given Path and Flags.
		/// </summary>
		/// <param name="path">The Path to the File.</param>
		/// <param name="flags">The Flags for accessing the file.</param>
		File(Path const& path, Flags const flags)
			: m_path(path)
			, m_flags(flags)
		{
		}

		File(File const& other) = delete;

		/// <summary>
		/// Moves the given File.
		/// </summary>
		/// <param name="other">The File to move.</param>
		File(File&& other) noexcept
			: m_path(std::move(other.m_path))
			, m_flags(std::move(other.m_flags))
		{
		}

		virtual ~File()
		{
		}

#pragma endregion

#pragma region Operators

	public:
		File& operator=(File const& other) = delete;

		File& operator=(File&& other) noexcept
		{
			if (this != &other)
			{
				close();
				m_path = std::move(other.m_path);
				m_flags = std::move(other.m_flags);
			}
			return *this;
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the Path to this File.
		/// </summary>
		/// <returns>The Path to the File.</returns>
		Path const& get_path() const { return m_path; }

		/// <summary>
		/// Gets the Flags for accessing this File.
		/// </summary>
		/// <returns>The accessor flags.</returns>
		Flags get_flags() const { return m_flags; }

		/// <summary>
		/// Gets the size of the file.
		/// </summary>
		/// <returns></returns>
		virtual Size_t get_size() const = 0;

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Checks if this File is open.
		/// </summary>
		/// <returns>True, if the file is currently being accessed.</returns>
		virtual Bool is_open() const = 0;

		/// <summary>
		/// Opens this File at the given Path with the given Flags.
		/// </summary>
		/// <param name="path">The location of the File to open.</param>
		/// <param name="flags">The accessor Flags for this File.</param>
		virtual void open(Path const& path, Flags const flags) = 0;

		/// <summary>
		/// Pushes any cached changes to the disk.
		/// </summary>
		virtual void flush() = 0;

		/// <summary>
		/// Flushes and closes the File.
		/// </summary>
		virtual void close() = 0;

		/// <summary>
		/// Moves the cursor(s) to a new location within the file.
		/// </summary>
		/// <param name="offset">The offset at which the file is relative to the direction.</param>
		/// <param name="dir">The anchor point of the offset.</param>
		virtual void seek(Position_t const offset, Direction const dir = Direction::Begin) = 0;

		/// <summary>
		/// Moves the read cursor to a new location within the file.
		/// </summary>
		/// <param name="offset">The offset at which the file is relative to the direction.</param>
		/// <param name="dir">The anchor point of the offset.</param>
		virtual void seek_read(Position_t const offset, Direction const dir = Direction::Begin) = 0;

		/// <summary>
		/// Moves the write cursor to a new location within the file.
		/// </summary>
		/// <param name="offset">The offset at which the file is relative to the direction.</param>
		/// <param name="dir">The anchor point of the offset.</param>
		virtual void seek_write(Position_t const offset, Direction const dir = Direction::Begin) = 0;

		/// <summary>
		/// Checks if the cursor is at or past the end of the file.
		/// </summary>
		/// <returns></returns>
		virtual Bool end_of_file() = 0;

		/// <summary>
		/// Gets the current position of the cursor.
		/// </summary>
		/// <returns></returns>
		virtual Position_t tell() = 0;

		/// <summary>
		/// Gets the current position of the read cursor.
		/// </summary>
		/// <returns></returns>
		virtual Position_t tell_read() = 0;

		/// <summary>
		/// Gets the current position of the write cursor.
		/// </summary>
		/// <returns></returns>
		virtual Position_t tell_write() = 0;

		/// <summary>
		/// Checks the next character after the cursor.
		/// </summary>
		/// <returns></returns>
		virtual Char peek() = 0;

		/// <summary>
		/// Gets the next character after the cursor, and moves the cursor to that position.
		/// </summary>
		/// <returns></returns>
		virtual Char read() = 0;

		/// <summary>
		/// Reads the given size of data into the given buffer, and moves the cursor size bytes.
		/// </summary>
		/// <param name="buffer">The location to read the data to.</param>
		/// <param name="size">The number of bytes to read.</param>
		virtual void read(void* const buffer, Size_t const size) = 0;

		/// <summary>
		/// Reads the next line of text, and moves the cursor the appropriate amount of bytes.
		/// </summary>
		/// <param name="delimiter">The separating character.</param>
		/// <returns></returns>
		virtual Bool read_line(String& line) = 0;

		/// <summary>
		/// Writes the given size of data to the file, and moves the cursor size number of bytes.
		/// </summary>
		/// <param name="buffer">The location to write the data from.</param>
		/// <param name="size">The number of bytes to write.</param>
		virtual void write(void const* const buffer, Size_t const size) = 0;

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Copies a File from one location to another.
		/// </summary>
		/// <param name="from">The from location.</param>
		/// <param name="to">The to location.</param>
		static void copy(Path const& from, Path const& to);

		/// <summary>
		/// Moves a File from one location to another.
		/// </summary>
		/// <param name="from">The from location.</param>
		/// <param name="to">The to location.</param>
		static void move(Path const& from, Path const& to);

		/// <summary>
		/// Creates an empty File.
		/// </summary>
		/// <param name="path">The Path to the File.</param>
		static void create(Path const& path);

		/// <summary>
		/// Destroys a File.
		/// </summary>
		/// <param name="path">The Path to the File.</param>
		static void destroy(Path const& path);

#pragma endregion
	};
}