#pragma once

#include "M_Main.h"

#define uchar unsigned char
#define ushort unsigned short
#define uint unsigned int

namespace minty
{
	MINTY_API inline int pack_int(uchar const b0, uchar const b1, uchar const b2, uchar const b3);

	MINTY_API inline int pack_int(ushort const s0, ushort const s1);

	MINTY_API inline int pack_get_int(int const data, int const offset, int const size);

	MINTY_API inline uchar pack_get_byte(int const data, int const offset, int const size);

	MINTY_API inline bool pack_get_bit(int const data, int const offset);

	MINTY_API inline int pack_set_int(int const data, int const offset, int const size, int const newData);

	MINTY_API inline int pack_set_byte(int const data, int const offset, int const size, uchar const newData);

	MINTY_API inline int pack_set_bit(int const data, int const offset, bool const bit);

	MINTY_API inline bool pack_get_bit(uchar const data, int const offset);

	MINTY_API inline unsigned char pack_set_bit(uchar const data, int const offset, bool const bit);
}