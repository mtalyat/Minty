#ifndef MINTY_STREAM_MEMORYSTREAM_H
#define MINTY_STREAM_MEMORYSTREAM_H

/**
 * @file MemoryStream.hpp
 * @brief Header file defining the MemoryStream class for in-memory stream operations.
 * @author Mitchell Talyat
 */

#include "Stream.hpp"
#include "Core/Data/Container.hpp"
#include "Core/Data/Shared.hpp"

namespace Minty
{
    /**
     * @brief A MemoryStream provides stream operations on a memory buffer.
     */
    class MemoryStream
        : public Stream
    {
#pragma region Constructors

    public:
        /**
         * @brief Creates a MemoryStream with the given Container.
         * @param container The Container to use as the memory buffer.
         */
        MemoryStream(Shared<Container> const& container);

        ~MemoryStream() override = default;

#pragma endregion

#pragma region Accessors

    public:
        StreamPosition get_position() override;

        void set_position(StreamPosition const position, StreamDirectionEnum const direction = StreamDirectionEnum::Begin) override;

        StreamSize get_size() const override;

#pragma endregion

#pragma region Methods

    public:
        void write(PointerConst const data, Size const size) override;

        Bool read(Pointer data, Size const size) override;

        Char peek() override;

        Bool end_of_stream() override;

        void flush() override;

#pragma endregion

#pragma region Variables

    private:
        Shared<Container> m_container;
        StreamPosition m_position;

#pragma endregion
    };
}

#endif // MINTY_STREAM_MEMORYSTREAM_H