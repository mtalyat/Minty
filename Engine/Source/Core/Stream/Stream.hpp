#ifndef MINTY_STREAM_STREAM_H
#define MINTY_STREAM_STREAM_H

/**
 * @file Stream.hpp
 * @brief Header file defining the Stream class for data streaming.
 * @author Mitchell Talyat
 */

#include "StreamDirection.hpp"
#include "Platform/Type/Primitive.hpp"

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
        /**
         * @brief Default constructor for Stream.
         */
        Stream() = default;

        virtual ~Stream() = default;

#pragma endregion

#pragma region Accessors

    public:
        /** 
         * @brief Gets the current position in the stream.
         * @return The current position in the stream.
         */
        virtual StreamPosition get_position() = 0;

        /**
         * @brief Sets the current position in the stream.
         * @param position The position to set.
         * @param direction The direction from which to set the position.
         */
        virtual void set_position(StreamPosition const position, StreamDirectionEnum const direction = StreamDirectionEnum::Begin) = 0;

        /**
         * @brief Gets the size of the stream.
         * @return The size of the stream.
         */
        virtual StreamSize get_size() const = 0;

#pragma endregion

#pragma region Methods

    public:
        /**
         * @brief Writes data to the stream.
         * @param data Pointer to the data to write.
         * @param size The size of the data to write.
         */
        virtual void write(PointerConst const data, Size const size) = 0;

        /**
         * @brief Reads data from the stream.
         * @param data Pointer to the buffer to read data into.
         * @param size The size of the data to read.
         * @return True if the read was successful, otherwise false.
         */
        virtual Bool read(Pointer data, Size const size) = 0;

        /**
         * @brief Peeks at the next character in the stream without advancing the position.
         * @return The next character in the stream.
         */
        virtual Char peek() = 0;

        /**
         * @brief Checks if the end of the stream has been reached.
         * @return True if the end of the stream has been reached, otherwise false.
         */
        virtual Bool end_of_stream() = 0;

        /**
         * @brief Flushes the stream, ensuring all data is written.
         */
        virtual void flush() = 0;

        /**
         * @brief Resets the stream position to the beginning.
         */
        inline void reset() { set_position(0, StreamDirectionEnum::Begin); }

#pragma endregion
    };
}

#endif // MINTY_STREAM_STREAM_H