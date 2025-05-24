#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Data/Path.h"
#include <fstream>
#include <streambuf>
#include <iostream>

namespace Minty
{
	/// <summary>
	/// Doubles as a buffer for a stream, and a file writer.
	/// </summary>
	class DualBuffer
		: public std::streambuf
	{
#pragma region Variables

	private:
		std::ostream* mp_stream;
		std::streambuf* mp_originalBuffer;
		std::ofstream m_fileStream;
		Bool m_inEscapeSequence;
		Bool m_isOpen;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates an empty DualBuffer.
		/// </summary>
		DualBuffer()
			: mp_stream(nullptr)
			, mp_originalBuffer(nullptr)
			, m_fileStream()
			, m_inEscapeSequence(false)
			, m_isOpen(false)
		{
		}

		/// <summary>
		/// Creates a DualBuffer using the given stream and file path.
		/// </summary>
		/// <param name="stream">The stream to use.</param>
		/// <param name="filePath">The path to the file to use.</param>
		DualBuffer(std::ostream& stream, Path const& filePath)
			: mp_stream(nullptr)
			, mp_originalBuffer(nullptr)
			, m_fileStream()
			, m_inEscapeSequence(false)
			, m_isOpen(false)
		{
			open(stream, filePath);
		}

		~DualBuffer()
		{
			if (m_isOpen)
			{
				close();
			}
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Checks if this DualBuffer is open.
		/// </summary>
		/// <returns>True, if open.</returns>
		Bool is_open() const { return m_isOpen; }

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

		virtual int sync() override
		{
			mp_originalBuffer->pubsync();
			m_fileStream.flush();
			return 0;
		}

	public:
		/// <summary>
		/// Uses the given stream and file path to open a DualBuffer.
		/// </summary>
		/// <param name="stream">The stream to write to.</param>
		/// <param name="filePath">The file to write to.</param>
		void open(std::ostream& stream, Path const& filePath)
		{
			MINTY_ASSERT(!m_isOpen, "DualBuffer is already open.");

			mp_stream = &stream;
			mp_originalBuffer = stream.rdbuf();
			m_fileStream.open(filePath.get_string().get_data(), std::ios::out);
			MINTY_ASSERT(m_fileStream.is_open(), "Failed to open file.");
			stream.rdbuf(this);
			m_isOpen = true;
		}

		/// <summary>
		/// Returns the Stream to its original buffer, and closes the file.
		/// </summary>
		void close()
		{
			MINTY_ASSERT(m_isOpen, "DualBuffer is not open.");

			mp_stream->rdbuf(mp_originalBuffer);
			mp_stream = nullptr;
			mp_originalBuffer = nullptr;
			m_fileStream.close();
			m_inEscapeSequence = false;
			m_isOpen = false;
		}

#pragma endregion

	};
}