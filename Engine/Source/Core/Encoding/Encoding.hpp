#ifndef MINTY_CORE_ENCODING_H
#define MINTY_CORE_ENCODING_H

/**
 * @file Encoding.h
 * @brief Header file for encoding and decoding utilities.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"

namespace Minty
{
#pragma region Base 64



#pragma endregion

#pragma region Base 16

	/**
	 * @brief Encodes raw data to a Base16 (hexadecimal) string.
	 * @param data Pointer to the raw data to encode.
	 * @param size The size of the data in bytes.
	 * @param buffer Pointer to the buffer to store the encoded string.
	 * @param bufferSize On input, the size of the buffer; on output, the size of the encoded string.
	 * @returns The Base16 encoded string.
	 */
	void encode_base16(PointerConst const data, Size const size, Char* const buffer, Size const bufferSize);

	/**
	 * @brief Decodes a Base16 (hexadecimal) string to raw data.
	 * @param string The Base16 string to decode.
	 * @param size The size of the data to decode in bytes.
	 * @param buffer Pointer to the buffer to store decoded data.
	 * @param bufferSize On input, the size of the buffer; on output, the number of bytes written.
	 */
	void decode_base16(Char const* const data, Size const size, Pointer const buffer, Size const bufferSize);

#pragma endregion

}

#endif // MINTY_CORE_ENCODING_H