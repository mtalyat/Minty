#ifndef MINTY_FILE_PHYSICALFILE_H
#define MINTY_FILE_PHYSICALFILE_H

/**
 * @file PhysicalFile.h
 * @brief Header file for physical file handling utilities.
 * @author Mitchell Talyat
 */

#include "Minty/File/File.h"

namespace Minty
{
	/**
	 * @brief Handles reading/writing to a physical file on the disk.
	 */
	class PhysicalFile
		: public File
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates an empty PhysicalFile.
		 */
		PhysicalFile() = default;

		/**
		 * @brief Creates a PhysicalFile with the given Path and Flags.
		 * @param path The Path to the File.
		 * @param flags The Flags for accessing the file.
		 */
		PhysicalFile(Path const& path, FileFlags const flags)
			: File() {
			open(path, flags);
		}

		/**
		 * @brief Moves the given PhysicalFile.
		 * @param other The PhysicalFile to move.
		 */
		PhysicalFile(PhysicalFile&& other) noexcept
			: File(std::move(other))
			, m_stream(std::move(other.m_stream))
		{
		}

		virtual ~PhysicalFile()
		{
			close();
		}

#pragma endregion

#pragma region Operators

	public:
		PhysicalFile& operator=(PhysicalFile const& other) = delete;

		PhysicalFile& operator=(PhysicalFile&& other) noexcept
		{
			if (this != &other)
			{
				File::operator=(std::move(other));
				m_stream = std::move(other.m_stream);
			}
			return *this;
		}

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the size of the file.
		 * @return The size of the file.
		 */
		virtual StreamSize get_size() const override;

#pragma endregion


#pragma region Methods

	public:
		/**
		 * @brief Checks if this File is open.
		 * @return True, if the file is currently being accessed.
		 */
		virtual Bool is_open() const override;

		/**
		 * @brief Opens this File at the given Path with the given Flags.
		 * @param path The location of the File to open.
		 * @param flags The accessor Flags for this File.
		 */
		virtual Bool open(Path const& path, FileFlags const flags) override;

		/**
		 * @brief Pushes any cached changes to the disk.
		 */
		virtual void flush() override;

		/**
		 * @brief Flushes and closes the File.
		 */
		virtual void close() override;

		/**
		 * @brief Gets the current position of the cursor.
		 * @return The current position of the cursor.
		 */
		virtual StreamPosition get_position() override;

		/**
		 * @brief Moves the cursor(s) to a new location within the file.
		 * @param offset The offset at which the file is relative to the direction.
		 * @param dir The anchor point of the offset.
		 */
		virtual void set_position(StreamPosition const offset, StreamDirection const dir = StreamDirection::Begin) override;

		/**
		 * @brief Checks if the cursor is at or past the end of the file.
		 * @return True if at or past the end of the file.
		 */
		virtual Bool end_of_file() override;

		/**
		 * @brief Checks the next character after the cursor.
		 * @return The next character after the cursor.
		 */
		virtual Char peek() override;

		/**
		 * @brief Gets the next character after the cursor, and moves the cursor to that position.
		 * @return The next character.
		 */
		virtual Char read() override;

		/**
		 * @brief Reads the given size of data into the given buffer, and moves the cursor size bytes.
		 * @param buffer The location to read the data to.
		 * @param size The number of bytes to read.
		 */
		virtual Bool read(Any const buffer, StreamSize const size) override;

		/**
		 * @brief Reads the next line of text, and moves the cursor the appropriate amount of bytes.
		 * @param line The string to store the line in.
		 * @return True if a line was read successfully.
		 */
		virtual Bool read_line(String& line) override;

		/**
		 * @brief Writes the given size of data to the file, and moves the cursor size number of bytes.
		 * @param buffer The location to write the data from.
		 * @param size The number of bytes to write.
		 */
		virtual Bool write(AnyConst const buffer, StreamSize const size) override;

#pragma endregion

#pragma region Variables

	protected:
		// file stream, could be in or out
		std::fstream m_stream;

#pragma endregion
	};
}

#endif // MINTY_FILE_PHYSICALFILE_H