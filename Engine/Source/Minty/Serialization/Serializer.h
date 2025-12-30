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

    template<typename T>
    struct ItemSerializer;

    /*
    
    template<>
    struct ItemSerializer<NAME>
    {
        static void serialize_item(Writer& writer, StringView const name, NAME const& value);
        static void deserialize_item(Reader& reader, StringView const name, NAME& value);
    };

    */
}

#endif // MINTY_SERIALIZATION_SERIALIZER_H