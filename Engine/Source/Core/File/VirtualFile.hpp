#pragma once

/**
 * @file VirtualFile.hpp
 * @brief Header file for virtual file handling utilities.
 * @author Mitchell Talyat
 */

#include "PhysicalFile.hpp"

namespace Minty
{
	/**
	 * @brief Treats a part of a PhysicalFile as if it were an entire file.
	 */
	class VirtualFile
		: public PhysicalFile
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates an empty VirtualFile.
		 */
		VirtualFile()
			: PhysicalFile(), m_virtualOffset(), m_virtualSize()
		{
		}

		VirtualFile(VirtualFile const& other) = delete;

		/**
		 * @brief Moves the given VirtualFile.
		 * @param other The VirtualFile to move.
		 */
		VirtualFile(VirtualFile&& other) noexcept
			: PhysicalFile(std::move(other))
			, m_virtualOffset(std::move(other.m_virtualOffset))
			, m_virtualSize(std::move(other.m_virtualSize))
		{
		}

		virtual ~VirtualFile()
		{
		}

#pragma endregion

#pragma region Operators

	public:
		VirtualFile& operator=(VirtualFile const& other) = delete;

		VirtualFile& operator=(VirtualFile&& other) noexcept
		{
			if (this != &other)
			{
				PhysicalFile::operator=(std::move(other));
				m_virtualOffset = std::move(other.m_virtualOffset);
				m_virtualSize = std::move(other.m_virtualSize);
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

		/**
		 * @brief Gets the position of this VirtualFile within the PhysicalFile.
		 * @return The position of this VirtualFile.
		 */
		virtual StreamPosition get_virtual_offset() const { return m_virtualOffset; }

		/**
		 * @brief Gets the size of this VirtualFile within the PhysicalFile.
		 * @return The size of this VirtualFile.
		 */
		virtual StreamSize get_virtual_size() const { return m_virtualSize; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Opens this File at the given Path with the given Flags.
		 * @param path The location of the File to open.
		 * @param flags The accessor Flags for this File.
		 * @param offset The offset within the PhysicalFile.
		 * @param size The size within the PhysicalFile.
		 */
		virtual Bool open(Path const& path, FileFlags const flags, StreamPosition const offset, Size const size);
		
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
		virtual void set_position(StreamPosition const offset, StreamDirectionEnum const dir = StreamDirectionEnum::Begin) override;

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
		virtual Bool read(Pointer const buffer, StreamSize const size) override;

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
		virtual void write(PointerConst const buffer, StreamSize const size) override;

#pragma endregion

#pragma region Variables

	protected:
		// offset within the physical file
		StreamPosition m_virtualOffset;
		// size within the physical file
		StreamSize m_virtualSize;

#pragma endregion
	};
}
