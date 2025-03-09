#pragma once
#include "Minty/Core/Macro.h"
#include "Minty/Core/ToString.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Path.h"
#include "Minty/File/PhysicalFile.h"

namespace Minty
{
	/// <summary>
	/// Logs messages to a stream.
	/// </summary>
	class Logger
	{
#pragma region Variables

	private:
		PhysicalFile* mp_file;

#pragma endregion

#pragma region Constructors

	private:
		Logger() = delete;

	public:
		/// <summary>
		/// Creates a new Logger that writes to the given file.
		/// </summary>
		/// <param name="path">The path to the file. The file is created if it does not exist.</param>
		Logger(Path const& path);

		Logger(Logger const& other) = delete;

		/// <summary>
		/// Moves the given Logger to this Logger.
		/// </summary>
		/// <param name="other">The Logger to move.</param>
		Logger(Logger&& other) noexcept
			: mp_file(other.mp_file)
		{
			other.mp_file = nullptr;
		}

		~Logger()
		{
			mp_file->close();
			delete mp_file;
		}

#pragma endregion

#pragma region Operators

	public:
		Logger& operator=(Logger const& other) = delete;

		Logger& operator=(Logger&& other) noexcept
		{
			if (this != &other)
			{
				mp_file = other.mp_file;
				other.mp_file = nullptr;
			}
			return *this;
		}

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Writes nothing.
		/// </summary>
		void write() const {}

		/// <summary>
		/// Writes the given value(s) to the stream.
		/// </summary>
		/// <typeparam name="T">The type of value.</typeparam>
		/// <typeparam name="...Args">The types of additional values.</typeparam>
		/// <param name="value">The value.</param>
		/// <param name="...args">The additional values.</param>
		template<typename T, typename... Args>
		void write(T const& value, Args const&... args) const
		{
			mp_file->write(to_string(value));
			write(args...);
		}

		/// <summary>
		/// Writes a newline.
		/// </summary>
		void write_line() const
		{
			mp_file->write("\n", sizeof(Char));
		}

		/// <summary>
		/// Writes the given value(s) to the stream and then writes a newline.
		/// </summary>
		/// <typeparam name="T">The type of value.</typeparam>
		/// <typeparam name="...Args">The types of additional values.</typeparam>
		/// <param name="value">The value.</param>
		/// <param name="...args">The additional values.</param>
		template<typename T, typename... Args>
		void write_line(T const& value, Args const&... args) const
		{
			write(value, args...);
			write_line();
		}

		/// <summary>
		/// Flushes the stream.
		/// </summary>
		void flush() const
		{
			mp_file->flush();
		}

#pragma endregion
	};
}