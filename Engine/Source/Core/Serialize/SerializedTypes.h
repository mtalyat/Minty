#pragma once

/**
 * @file SerializedTypes.h
 * @brief Header file defining serialized types for the Minty engine.
 * @author Mitchell Talyat
 */

#include "Reader.h"
#include "Writer.h"
#include "Platform/Type/Primitive.h"
#include "Core/Data/Vector.h"

namespace Minty
{
    template <typename T, template <typename> class AllocatorType>
    struct Serializer<Vector<T, AllocatorType>>
    {
        static Bool serialize(Writer &writer, Vector<T, AllocatorType> const &value)
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
                value.add(std::move(element));
                element = {};
            }
            return true;
        }
    };
}
