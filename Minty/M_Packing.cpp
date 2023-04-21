#include "pch.h"
#include "M_Packing.h"

namespace minty
{
	MINTY_API int pack_int(byte const b0, byte const b1, byte const b2, byte const b3)
	{
		return (b3 << 24) | (b2 << 16) | (b1 << 8) | b0;
	}

	MINTY_API int pack_int(ushort const s0, ushort const s1)
	{
		return (s1 << 16) | s0;
	}

	MINTY_API int pack_get_int(int const data, int const offset, int const size)
	{
		return (data >> offset) & ((1 << size) - 1);
	}

	MINTY_API byte pack_get_byte(int const data, int const offset, int const size)
	{
		return pack_get_int(data, offset * 8, size * 8);
	}

	MINTY_API bool pack_get_bit(int const data, int const offset)
	{
		return pack_get_int(data, offset, 1);
	}

	MINTY_API int pack_set_int(int const data, int const offset, int const size, int const newData)
	{
		return (data & ~(((1 << size) - 1) << offset)) | (newData << offset);
	}

	MINTY_API int pack_set_byte(int const data, int const offset, int const size, byte const newData)
	{
		return pack_set_int(data, offset * 8, size * 8, static_cast<int>(newData));
	}

	MINTY_API int pack_set_bit(int const data, int const offset, bool const bit)
	{
		return pack_set_int(data, offset, 1, bit ? 1 : 0);
	}

	MINTY_API bool pack_get_bit(byte const data, int const offset)
	{
		return (data >> offset) & 1;
	}

	MINTY_API byte pack_set_bit(byte const data, int const offset, bool const bit)
	{
		return (data & ~(1 << offset)) | (bit << offset);
	}
}
