#ifndef MINTY_SERIALIZATION_SERIALIZEDTYPES_H
#define MINTY_SERIALIZATION_SERIALIZEDTYPES_H

/**
 * @file SerializedTypes.h
 * @brief Header file defining serialized types for the Minty engine.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Data/Vector.h"

namespace Minty
{
    template <typename T, template <typename> class AllocatorType>
    struct Serializer<Vector<T, AllocatorType>>
    {
        static void serialize(Writer &writer, Vector<T, AllocatorType> const &value)
        {
            MINTY_NOT_IMPLEMENTED();
        }

        static Bool deserialize(Reader &reader, Vector<T, AllocatorType> &value)
        {
            value.clear();

            // read each element in the vector, with no name
            String dummyName;
            T element;
            while(reader.read_next(dummyName, element))
            {
                value.add(element);
            }
            return true;
        }
    };
}

#endif // MINTY_SERIALIZATION_SERIALIZEDTYPES_H