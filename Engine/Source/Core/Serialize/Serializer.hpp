#pragma once

/**
 * @file Serializer.hpp
 * @brief Header file defining the Serializer class for serialization.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include <concepts>

namespace Minty
{
    class Reader;
    class Writer;

    /*
    
    template<>
    struct Serializer<NAME>
    {
        static Bool serialize(Writer& writer, NAME const& value);
        static Bool deserialize(Reader& reader, NAME& value);
    };
    
    */

    template<typename T>
    struct Serializer;

    template<typename T>
    concept Serializable = requires(Writer& writer, Reader& reader, T const& writeValue, T& readValue)
    {
        { Serializer<T>::serialize(writer, writeValue) } -> std::same_as<Bool>;
        { Serializer<T>::deserialize(reader, readValue) } -> std::same_as<Bool>;
    };
}
