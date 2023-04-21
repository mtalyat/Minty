#pragma once

#include "M_Main.h"

#define uchar unsigned char
#define ushort unsigned short
#define uint unsigned int

namespace minty
{
	/// <summary>
	/// Combines the four given bytes into one integer.
	/// </summary>
	/// <param name="b0">The least significant byte.</param>
	/// <param name="b1"></param>
	/// <param name="b2"></param>
	/// <param name="b3">The most significant byte.</param>
	/// <returns>An int with all of the packed bytes.</returns>
	MINTY_API inline int pack_int(uchar const b0, uchar const b1, uchar const b2, uchar const b3);

	/// <summary>
	/// Combines the two given unsigned shorts into one integer.
	/// </summary>
	/// <param name="s0">The least significant unsigned short.</param>
	/// <param name="s1">The most significant unsigned short.</param>
	/// <returns></returns>
	MINTY_API inline int pack_int(ushort const s0, ushort const s1);

	/// <summary>
	/// Gets the bits from the given data int.
	/// </summary>
	/// <param name="data">The int to get the bits from.</param>
	/// <param name="offset">The offset within data to the bits to get, in bits.</param>
	/// <param name="size">The number of bits to get.</param>
	/// <returns>The desired bits, in an int.</returns>
	MINTY_API inline int pack_get_int(int const data, int const offset, int const size);

	/// <summary>
	/// Gets the bytes from the given data int.
	/// </summary>
	/// <param name="data">The int to get the bytes from.</param>
	/// <param name="offset">The offset within the data to the bytes to get, in bytes.</param>
	/// <param name="size">The number of bytes to get.</param>
	/// <returns>The desired bytes, in an int.</returns>
	MINTY_API inline uchar pack_get_byte(int const data, int const offset, int const size);

	/// <summary>
	/// Gets a bit from the given data int.
	/// </summary>
	/// <param name="data">The int to get the bit from.</param>
	/// <param name="offset">The offset within the data to the bit to get.</param>
	/// <returns>The desired bit, as a bool.</returns>
	MINTY_API inline bool pack_get_bit(int const data, int const offset);

	/// <summary>
	/// Sets the bits to the given data int.
	/// </summary>
	/// <param name="data">The int to set the bits to.</param>
	/// <param name="offset">The offset within the data to the bits to set, in bits.</param>
	/// <param name="size">The number of bits to set.</param>
	/// <param name="newData">The bits to set, in an int, starting at the least significant bit.</param>
	/// <returns>Data, with the new bits set.</returns>
	MINTY_API inline int pack_set_int(int const data, int const offset, int const size, int const newData);

	/// <summary>
	/// Sets the bytes to the given data int.
	/// </summary>
	/// <param name="data">The int to set the bytes to.</param>
	/// <param name="offset">The offset within the data to the bytes to set, in bytes.</param>
	/// <param name="size">The number of bytes to set.</param>
	/// <param name="newData">The bytes to set, in an int, starting at the least significant bit.</param>
	/// <returns>Data, with the new bytes set.</returns>
	MINTY_API inline int pack_set_byte(int const data, int const offset, int const size, uchar const newData);

	/// <summary>
	/// Sets the bit to the given data int.
	/// </summary>
	/// <param name="data">The int to set the bit to.</param>
	/// <param name="offset">The offset within the data to the bit to set, in bits.</param>
	/// <param name="bit">The bit to set.</param>
	/// <returns>Data, with the new bit set.</returns>
	MINTY_API inline int pack_set_bit(int const data, int const offset, bool const bit);

	/// <summary>
	/// Gets the bit from the given data byte.
	/// </summary>
	/// <param name="data">The byte to get the bit from.</param>
	/// <param name="offset">The offset within the data to the bit to get, in bits.</param>
	/// <returns>The desired bit, as a bool.</returns>
	MINTY_API inline bool pack_get_bit(uchar const data, int const offset);

	/// <summary>
	/// Sets the bit to the given data byte.
	/// </summary>
	/// <param name="data">The byte to set the bit to.</param>
	/// <param name="offset">The offset within the data to the bit to set, in bits.</param>
	/// <param name="bit">The bit to set.</param>
	/// <returns>Data, with the new bit set.</returns>
	MINTY_API inline unsigned char pack_set_bit(uchar const data, int const offset, bool const bit);
}