#include "Minty/File/PhysicalFile.h"

namespace Minty
{
	/// <summary>
	/// Handles reading/writing to a virtual file.
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
		VirtualFile()
			: PhysicalFile(), m_virtualOffset(), m_virtualSize()
		{
		}

		VirtualFile(Path const& path, Flags const flags, Position_t const offset, Size const size)
			: PhysicalFile(), m_virtualOffset(), m_virtualSize() {
			open(path, flags, offset, size);
		}

		virtual ~VirtualFile() = default;

#pragma endregion

#pragma region Get Set

	public:
		virtual Size_t get_size() const override;

#pragma endregion

#pragma region Methods

	public:
		virtual void open(Path const& path, Flags const flags, Position_t const offset, Size const size);

		virtual void seek_read(Position_t const offset, Direction dir = Direction::Begin) override;

		virtual void seek_write(Position_t const offset, Direction const dir = Direction::Begin) override;

		virtual Bool end_of_file() override;

		virtual Position_t tell_read() override;

		virtual Position_t tell_write() override;

		virtual void read(void* const buffer, Size_t const size) override;

		virtual void write(void const* const buffer, Size_t const size) override;

#pragma endregion		
	};
}