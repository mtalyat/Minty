#pragma once

/**
 * @file FileStream.hpp
 * @brief Header file defining the FileStream class for file serialization.
 * @author Mitchell Talyat
 */

#include "Stream.hpp"
#include "Core/Data/Path.hpp"
#include "Core/Data/Unique.hpp"

namespace Minty
{
    class File;

    /**
     * @class FileStream
     * @brief Class representing a file stream for serialization.
     */
    class FileStream
        : public Stream
    {
#pragma region Constructors

    public:
        /**
         * @brief Creates a FileStream that reads/writes to the given File.
         * @param file The File to read/write to.
         */
        explicit FileStream(Unique<File> &&file);

#pragma endregion

#pragma region Accessors

    public:
        StreamPosition get_position() override;

        void set_position(StreamPosition const position, StreamDirectionEnum const direction = StreamDirectionEnum::Begin) override;

        StreamSize get_size() const override;

#pragma endregion

#pragma region Methods

    public:
        /**

         * @brief Writes data to the file stream.
         * @param data The data to write.
         * @param size The size of the data to write.
         * @return True if the write was successful, false otherwise.
         */
        void write(PointerConst const data, Size const size) override;

        /**
         * @brief Reads data from the file stream.
         * @param data The buffer to read data into.
         * @param size The size of the data to read.
         * @return True if the read was successful, false otherwise.
         */
        Bool read(Pointer data, Size const size) override;

        /**
         * @brief Peeks at the next character in the file stream without advancing the cursor.
         * @return The next character in the stream.
         */
        Char peek() override;

        /**
         * @brief Checks if the end of the file stream has been reached.
         * @return True if at the end of the stream, false otherwise.
         */
        Bool end_of_stream() override;

        /**
         * @brief Flushes any buffered data to the file.
         */
        void flush() override;

#pragma endregion

#pragma region Variables

    private:
        Unique<File> m_file;

#pragma endregion
    };
}
