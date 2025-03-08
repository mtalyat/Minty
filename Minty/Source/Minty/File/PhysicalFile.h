#pragma once
#include "Minty/File/File.h"

namespace Minty
{
	/// <summary>
	/// Handles reading/writing to a physical file on the disk.
	/// </summary>
	class PhysicalFile
		: public File
	{
#pragma region Variables

	protected:
		// file stream, could be in or out
		std::fstream m_stream;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates an empty PhysicalFile.
		/// </summary>
		PhysicalFile() = default;

		/// <summary>
		/// Creates a PhysicalFile with the given Path and Flags.
		/// </summary>
		/// <param name="path">The Path to the File.</param>
		/// <param name="flags">The Flags for accessing the file.</param>
		PhysicalFile(Path const& path, Flags const flags)
			: File() {
			open(path, flags);
		}

		virtual ~PhysicalFile() = default;

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the size of the file.
		/// </summary>
		/// <returns></returns>
		virtual Size_t get_size() const override;

#pragma endregion


#pragma region Methods

	public:
		/// <summary>
		/// Checks if this File is open.
		/// </summary>
		/// <returns>True, if the file is currently being accessed.</returns>
		virtual Bool is_open() const override;

		/// <summary>
		/// Opens this File at the given Path with the given Flags.
		/// </summary>
		/// <param name="path">The location of the File to open.</param>
		/// <param name="flags">The accessor Flags for this File.</param>
		virtual void open(Path const& path, Flags const flags) override;

		/// <summary>
		/// Pushes any cached changes to the disk.
		/// </summary>
		virtual void flush() override;

		/// <summary>
		/// Flushes and closes the File.
		/// </summary>
		virtual void close() override;

		/// <summary>
		/// Moves the cursor(s) to a new location within the file.
		/// </summary>
		/// <param name="offset">The offset at which the file is relative to the direction.</param>
		/// <param name="dir">The anchor point of the offset.</param>
		virtual void seek(Position_t const offset, Direction const dir = Direction::Begin) override;

		/// <summary>
		/// Moves the read cursor to a new location within the file.
		/// </summary>
		/// <param name="offset">The offset at which the file is relative to the direction.</param>
		/// <param name="dir">The anchor point of the offset.</param>
		virtual void seek_read(Position_t const offset, Direction const dir = Direction::Begin) override;

		/// <summary>
		/// Moves the write cursor to a new location within the file.
		/// </summary>
		/// <param name="offset">The offset at which the file is relative to the direction.</param>
		/// <param name="dir">The anchor point of the offset.</param>
		virtual void seek_write(Position_t const offset, Direction const dir = Direction::Begin) override;

		/// <summary>
		/// Checks if the cursor is at or past the end of the file.
		/// </summary>
		/// <returns></returns>
		virtual Bool end_of_file() override;

		/// <summary>
		/// Gets the current position of the cursor.
		/// </summary>
		/// <returns></returns>
		virtual Position_t tell() override;

		/// <summary>
		/// Gets the current position of the read cursor.
		/// </summary>
		/// <returns></returns>
		virtual Position_t tell_read() override;

		/// <summary>
		/// Gets the current position of the write cursor.
		/// </summary>
		/// <returns></returns>
		virtual Position_t tell_write() override;

		/// <summary>
		/// Checks the next character after the cursor.
		/// </summary>
		/// <returns></returns>
		virtual Char peek() override;

		/// <summary>
		/// Gets the next character after the cursor, and moves the cursor to that position.
		/// </summary>
		/// <returns></returns>
		virtual Char read() override;

		/// <summary>
		/// Reads the given size of data into the given buffer, and moves the cursor size bytes.
		/// </summary>
		/// <param name="buffer">The location to read the data to.</param>
		/// <param name="size">The number of bytes to read.</param>
		virtual void read(void* const buffer, Size_t const size) override;

		/// <summary>
		/// Reads the next line of text, and moves the cursor the appropriate amount of bytes.
		/// </summary>
		/// <param name="delimiter">The separating character.</param>
		/// <returns></returns>
		virtual Bool read_line(String& line) override;

		/// <summary>
		/// Writes the given size of data to the file, and moves the cursor size number of bytes.
		/// </summary>
		/// <param name="buffer">The location to write the data from.</param>
		/// <param name="size">The number of bytes to write.</param>
		virtual void write(void const* const buffer, Size_t const size) override;

#pragma endregion	
	};
}