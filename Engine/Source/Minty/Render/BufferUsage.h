#ifndef MINTY_RENDER_BUFFERUSAGE_H
#define MINTY_RENDER_BUFFERUSAGE_H

/**
 * @file BufferUsage.h
 * @brief Header file defining the BufferUsage enum.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Enum.h"
#include "Minty/Serialization/Parser.h"

namespace Minty
{
    /**
	 * @brief Describes how a buffer is used.
     */
    enum class BufferUsage
    {
        /**
         * @brief Invalid.
         */
        Undefined = 0x0,

        /**
		 * @brief Transfer source buffer.
         */
        TransferSrc = 0x1,

        /**
         * @brief Transfer destination buffer.
         */
        TransferDst = 0x2,

        /**
		 * @brief Vertex buffer.
         */
        Vertex = 0x4,

        /**
		 * @brief Index buffer.
         */
        Index = 0x8,

        /**
		 * @brief Uniform buffer.
         */
        Uniform =  0x10,

		Max = Uniform,
    };

	MINTY_ENABLE_ENUM_OPERATORS(BufferUsage)

    template<>
    struct Parser<BufferUsage>
    {
        static Bool parse(StringView const str, BufferUsage& value);
        static String to_string(BufferUsage const& obj);
    };
}

#endif // MINTY_RENDER_BUFFERUSAGE_H