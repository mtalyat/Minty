#pragma once
#include "Minty/Core/Base.h"
#include "Minty/Core/Types.h"
#include <fstream>

namespace Minty
{
	/// <summary>
	/// Handles reading/writing to a file.
	/// </summary>
	class File
	{
#pragma region Types

	public:
		using Position_t = std::streampos;
		using Size_t = std::streamsize;

#pragma endregion

#pragma region Classes

	public:
		enum class Direction
		{
			Begin = std::ios_base::beg,
			Current = std::ios_base::cur,
			End = std::ios_base::end,
		};

		enum class Flags : Int
		{
			None = 0,
			Read = std::ios_base::in,
			Write = std::ios_base::out,
			ReadWrite = std::ios_base::in | std::ios_base::out,
			End = std::ios_base::end,
			Append = std::ios_base::app,
			Truncate = std::ios_base::trunc,
			Binary = std::ios_base::binary,
		};

		friend inline Flags operator|(Flags const left, Flags const right)
		{
			return static_cast<Flags>(static_cast<Int>(left) | static_cast<Int>(right));
		}

		friend inline Flags operator&(Flags const left, Flags const right)
		{
			return static_cast<Flags>(static_cast<Int>(left) & static_cast<Int>(right));
		}

#pragma endregion

#pragma region Variables

	private:


#pragma endregion


#pragma region Constructors

	public:
		

#pragma endregion


	};
}