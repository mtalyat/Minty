#pragma once
#include "Minty/Core/Macro.h"
#include "Minty/Data/String.h"
#include "Minty/Serialization/Parse.h"

namespace Minty
{
    /// <summary>
	/// Describes how a buffer is used.
    /// </summary>
    enum class BufferUsage
    {
        /// <summary>
        /// Invalid.
        /// </summary>
        Undefined = 0x0,

        /// <summary>
		/// Transfer source buffer.
        /// </summary>
        TransferSrc = 0x1,

        /// <summary>
        /// Transfer destination buffer.
        /// </summary>
        TransferDst = 0x2,

        /// <summary>
		/// Vertex buffer.
        /// </summary>
        Vertex = 0x4,

        /// <summary>
		/// Index buffer.
        /// </summary>
        Index = 0x8,

        /// <summary>
		/// Uniform buffer.
        /// </summary>
        Uniform =  0x10,

		Max = Uniform,
    };

	MINTY_ENUM_FLAGS_OPERATORS(BufferUsage)

    String to_string(BufferUsage const obj);
    BufferUsage parse_to_buffer_usage(String const& string);
    Bool parse_try_buffer_usage(String const& string, BufferUsage& value);
    template<>
    inline BufferUsage parse_to<BufferUsage>(String const& string) { return parse_to_buffer_usage(string); }
    template<>
    inline Bool parse_try<BufferUsage>(String const& string, BufferUsage& value) { return parse_try_buffer_usage(string, value); }
}