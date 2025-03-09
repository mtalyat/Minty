#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Data/Path.h"
#include <fstream>
#include <streambuf>
#include <iostream>

namespace Minty
{
	class DualBuffer
		: public std::streambuf
	{
#pragma region Variables

	private:
		std::ostream* mp_stream;
		std::streambuf* mp_originalBuffer;
		std::ofstream m_fileStream;
		Bool m_inEscapeSequence;

#pragma endregion

#pragma region Constructors

	public:
		DualBuffer(std::ostream& stream, Path const& filePath)
			: mp_stream(&stream)
			, mp_originalBuffer(stream.rdbuf())
			, m_fileStream(filePath.get_string().get_data(), std::ios::out)
			, m_inEscapeSequence(false)
		{
			MINTY_ASSERT(m_fileStream.is_open(), "Failed to open file.");

			stream.rdbuf(this);
		}

		~DualBuffer()
		{
			m_fileStream.close();
			mp_stream->rdbuf(mp_originalBuffer);
		}

#pragma endregion

#pragma region Methods

	protected:
		virtual int overflow(int c) override
		{
			// check for escape sequence
			if (c == '\\')
			{
				m_inEscapeSequence = true;
				mp_originalBuffer->sputc(c);
				return c;
			}

			// if in an escape sequence, write to console, then go back to normal
			if (m_inEscapeSequence)
			{
				mp_originalBuffer->sputc(c);
				m_inEscapeSequence = false;
				return c;
			}

			// normal
			if (c != EOF)
			{
				mp_originalBuffer->sputc(c);
				m_fileStream.put(c);
			}

			return c;
		}

#pragma endregion

	};
}