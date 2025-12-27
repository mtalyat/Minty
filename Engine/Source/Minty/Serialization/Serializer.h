#ifndef MINTY_SERIALIZATION_SERIALIZER_H
#define MINTY_SERIALIZATION_SERIALIZER_H

/**
 * @file Serializer.h
 * @brief Header file defining the Serializer class for serialization.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"

namespace Minty
{
    class Reader;
    class Writer;

    template<typename T>
    struct Serializer;

    /*
    
    template<>
    struct Serializer<NAME>
    {
        static void serialize(Writer& writer, NAME const& value);
        static void deserialize(Reader& reader, NAME& value);
    };
    
    */
}

#endif // MINTY_SERIALIZATION_SERIALIZER_H