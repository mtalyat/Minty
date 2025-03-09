#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Data/Path.h"
#include <ostream>

namespace Minty
{
	/// <summary>
	/// Logs messages to a stream.
	/// </summary>
	class Logger
	{
#pragma region Variables

	private:
		// the stream to log to
		std::ostream* mp_stream;
		// if true, delete on destruction
		Bool m_ownsStream;

#pragma endregion

#pragma region Constructors

	private:
		Logger() = delete;

		Logger(std::ostream* mp_stream, Bool ownsStream)
			: mp_stream(mp_stream)
			, m_ownsStream(ownsStream)
		{
		}

	public:
		/// <summary>
		/// Creates a new Logger that writes to the given file.
		/// </summary>
		/// <param name="path">The path to the file. The file is created if it does not exist.</param>
		Logger(Path const& path);

		/// <summary>
		/// Creates a new Logger that writes to the given stream.
		/// </summary>
		/// <param name="stream">The stream to write to.</param>
		Logger(std::ostream& stream);

		Logger(Logger const& other) = delete;

		/// <summary>
		/// Moves the given Logger to this Logger.
		/// </summary>
		/// <param name="other">The Logger to move.</param>
		Logger(Logger&& other) noexcept
			: mp_stream(other.mp_stream)
			, m_ownsStream(other.m_ownsStream)
		{
			other.mp_stream = nullptr;
			other.m_ownsStream = false;
		}

		~Logger()
		{
			if (m_ownsStream)
			{
				delete mp_stream;
			}
		}

#pragma endregion

#pragma region Operators

	public:
		Logger& operator=(Logger const& other) = delete;

		Logger& operator=(Logger&& other) noexcept
		{
			if (this != &other)
			{
				mp_stream = other.mp_stream;
				m_ownsStream = other.m_ownsStream;
				other.mp_stream = nullptr;
				other.m_ownsStream = false;
			}
			return *this;
		}

#pragma endregion

#pragma region Methods

	public:
		

#pragma endregion
	};
}