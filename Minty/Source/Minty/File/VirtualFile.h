#include "Minty/File/PhysicalFile.h"

namespace Minty
{
	/// <summary>
	/// Treats a part of a PhysicalFile as if it were an entire file.
	/// </summary>
	class VirtualFile
		: public PhysicalFile
	{
#pragma region Variables

	protected:
		// offset within the physical file
		Position_t m_virtualOffset;
		// size within the physical file
		Size_t m_virtualSize;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates an empty VirtualFile.
		/// </summary>
		VirtualFile()
			: PhysicalFile(), m_virtualOffset(), m_virtualSize()
		{
		}

		/// <summary>
		/// Creates a VirtualFile with the given Path and Flags, as well as the given virtual offset and size within the PhyiscalFile.
		/// </summary>
		/// <param name="path">The Path to the File.</param>
		/// <param name="flags">The Flags for accessing the file.</param>
		/// <param name="offset">The offset within the PhysicalFile.</param>
		/// <param name="size">The size within the PhysicalFile.</param>
		VirtualFile(Path const& path, Flags const flags, Position_t const offset, Size const size)
			: PhysicalFile(), m_virtualOffset(), m_virtualSize() {
			open(path, flags, offset, size);
		}

		virtual ~VirtualFile() = default;

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
		/// Opens this File at the given Path with the given Flags.
		/// </summary>
		/// <param name="path">The location of the File to open.</param>
		/// <param name="flags">The accessor Flags for this File.</param>
		virtual void open(Path const& path, Flags const flags, Position_t const offset, Size const size);

		/// <summary>
		/// Moves the read cursor to a new location within the file.
		/// </summary>
		/// <param name="offset">The offset at which the file is relative to the direction.</param>
		/// <param name="dir">The anchor point of the offset.</param>
		virtual void seek_read(Position_t const offset, Direction dir = Direction::Begin) override;

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
		/// Reads the given size of data into the given buffer, and moves the cursor size bytes.
		/// </summary>
		/// <param name="buffer">The location to read the data to.</param>
		/// <param name="size">The number of bytes to read.</param>
		virtual void read(void* const buffer, Size_t const size) override;

		/// <summary>
		/// Writes the given size of data to the file, and moves the cursor size number of bytes.
		/// </summary>
		/// <param name="buffer">The location to write the data from.</param>
		/// <param name="size">The number of bytes to write.</param>
		virtual void write(void const* const buffer, Size_t const size) override;

#pragma endregion		
	};
}