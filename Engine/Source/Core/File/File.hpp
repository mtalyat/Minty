#pragma once

/**
 * @file File.h
 * @brief Header file for file handling utilities.
 * @author Mitchell Talyat
 */

#include "FileFlags.hpp"
#include "Platform/Type/Primitive.hpp"
#include "Core/Data/Path.hpp"
#include "Core/Data/Vector.hpp"
#include "Core/Stream/StreamDirection.hpp"
#include <fstream>

namespace Minty
{
	/**
	 * @brief Handles reading/writing to a file.
	 */
	class File
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates an empty File.
		 */
		File()
			: m_path()
			, m_flags(FileFlagsEnum::None)
		{
		}

		File(File const& other) = delete;

		/**
		 * @brief Moves the given File.
		 * @param other The File to move.
		 */
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

#pragma region Accessors

	public:
		/**
		 * @brief Gets the Path to this File.
		 * @return The Path to the File.
		 */
		Path const& get_path() const { return m_path; }

		/**
		 * @brief Gets the Flags for accessing this File.
		 * @return The accessor flags.
		 */
		FileFlags get_flags() const { return m_flags; }

		/**
		 * @brief Gets the size of the file.
		 * @return The size of the file.
		 */
		virtual StreamSize get_size() const = 0;

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Checks if this File is open.
		 * @return True, if the file is currently being accessed.
		 */
		virtual Bool is_open() const = 0;

		/**
		 * @brief Opens this File at the given Path with the given Flags.
		 * @param path The location of the File to open.
		 * @param flags The accessor Flags for this File.
		 */
		virtual Bool open(Path const& path, FileFlags const flags) = 0;

		/**
		 * @brief Pushes any cached changes to the disk.
		 */
		virtual void flush() = 0;

		/**
		 * @brief Flushes and closes the File.
		 */
		virtual void close() = 0;

		/**
		 * @brief Gets the current position of the cursor.
		 * @return The current position of the cursor.
		 */
		virtual StreamPosition get_position() = 0;

		/**
		 * @brief Moves the cursor(s) to a new location within the file.
		 * @param offset The offset at which the file is relative to the direction.
		 * @param dir The anchor point of the offset.
		 */
		virtual void set_position(StreamPosition const offset, StreamDirectionEnum const dir = StreamDirectionEnum::Begin) = 0;

		/**
		 * @brief Checks if the cursor is at or past the end of the file.
		 * @return True if at or past the end of the file.
		 */
		virtual Bool end_of_file() = 0;

		/**
		 * @brief Checks the next character after the cursor.
		 * @return The next character after the cursor.
		 */
		virtual Char peek() = 0;

		/**
		 * @brief Gets the next character after the cursor, and moves the cursor to that position.
		 * @return The next character.
		 */
		virtual Char read() = 0;

		/**
		 * @brief Reads the given size of data into the given buffer, and moves the cursor size bytes.
		 * @param buffer The location to read the data to.
		 * @param size The number of bytes to read.
		 */
		virtual Bool read(Pointer const buffer, StreamSize const size) = 0;

		/**
		 * @brief Reads the next line of text, and moves the cursor the appropriate amount of bytes.
		 * @param line The string to store the line in.
		 * @return True if a line was read successfully.
		 */
		virtual Bool read_line(String& line) = 0;

		/**
		 * @brief Reads all of the text from the file, and moves the cursor to the end.
		 * @return A String containing all the text.
		 */
		String read_text();

		/**
		 * @brief Reads all of the lines of text from the file, and moves the cursor to the end.
		 * @return A Vector containing all the lines.
		 */
		Vector<String> read_lines();

		/**
		 * @brief Reads all of the bytes from the file, and moves the cursor to the end.
		 * @return A Vector containing all of the bytes of data.
		 */
		Vector<Byte> read_bytes();

		/**
		 * @brief Writes the given size of data to the file, and moves the cursor size number of bytes.
		 * @param buffer The location to write the data from.
		 * @param size The number of bytes to write.
		 */
		virtual void write(PointerConst const buffer, StreamSize const size) = 0;

		/**
		 * @brief Writes the given line of text to the file, and moves the cursor the appropriate amount of bytes.
		 * @param line The line of text to write.
		 */
		void write_text(String const& text);

		/**
		 * @brief Writes the given lines of text to the file, and moves the cursor the appropriate amount of bytes.
		 * @param lines The lines of text to write.
		 */
		void write_lines(Vector<String> const& lines);

		/**
		 * @brief Writes the given bytes of data to the file, and moves the cursor the appropriate amount of bytes.
		 * @param bytes The bytes of data to write.
		 */
		void write_bytes(Vector<Byte> const& bytes);

		/**
		 * @brief Copies a File from one location to another.
		 * @param from The from location.
		 * @param to The to location.
		 */
		static void copy(Path const& from, Path const& to);

		/**
		 * @brief Moves a File from one location to another.
		 * @param from The from location.
		 * @param to The to location.
		 */
		static void move(Path const& from, Path const& to);

		/**
		 * @brief Creates an empty File.
		 * @param path The Path to the File.
		 */
		static void create(Path const& path);

		/**
		 * @brief Destroys a File.
		 * @param path The Path to the File.
		 */
		static void destroy(Path const& path);

		/**
		 * @brief Reads all of the text from a File.
		 * @param path The Path to the File.
		 * @return A String containing all the text.
		 */
		static String read_text(Path const& path);

		/**
		 * @brief Reads all of the lines of text from a File.
		 * @param path The Path to the File.
		 * @return A Vector containing all the lines.
		 */
		static Vector<String> read_lines(Path const& path);

		/**
		 * @brief Reads all of the bytes from a File.
		 * @param path The Path to the File.
		 * @return A Vector containing all of the bytes of data.
		 */
		static Vector<Byte> read_bytes(Path const& path);

		/**
		 * @brief Writes all of the text to a File.
		 * @param path The Path to the File.
		 * @param text The text to write.
		 */
		static Bool write_text(Path const& path, String const& text);

		/**
		 * @brief Writes all of the lines of text to a File.
		 * @param path The Path to the File.
		 * @param lines The lines to write.
		 */
		static Bool write_lines(Path const& path, Vector<String> const& lines);

		/**
		 * @brief Writes all of the bytes to a File.
		 * @param path The Path to the File.
		 * @param bytes The bytes to write.
		 */
		static Bool write_bytes(Path const& path, Vector<Byte> const& bytes);

#pragma endregion

#pragma region Variables

	protected:
		Path m_path;
		FileFlags m_flags;

#pragma endregion
	};
}
