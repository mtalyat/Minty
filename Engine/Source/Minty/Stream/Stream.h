#ifndef MINTY_STREAM_STREAM_H
#define MINTY_STREAM_STREAM_H

/**
 * @file Stream.h
 * @brief Header file defining the Stream class for data streaming.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Stream/StreamDirection.h"

namespace Minty
{
    class File;

    /**
     * @brief Class representing a stream in the serialization process.
     */
    class Stream
    {
#pragma region Constructors

    public:
        Stream() = default;

        virtual ~Stream() = default;

#pragma endregion

#pragma region Accessors

    public:
        virtual StreamPosition get_position() = 0;

        virtual void set_position(StreamPosition const position, StreamDirection const direction = StreamDirection::Begin) = 0;

        virtual StreamSize get_size() const = 0;

#pragma endregion

#pragma region Methods

    public:
        virtual void write(AnyConst const data, Size const size) = 0;

        virtual Bool read(Any data, Size const size) = 0;

        virtual Char peek() = 0;

        virtual Bool end_of_stream() = 0;

        virtual void flush() = 0;

#pragma endregion
    };
}

#endif // MINTY_STREAM_STREAM_H