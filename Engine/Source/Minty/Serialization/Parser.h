#ifndef MINTY_SERIALIZATION_PARSER_H
#define MINTY_SERIALIZATION_PARSER_H

/**
 * @file Parser.h
 * @brief Header file defining the Parser class for serialization.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/String.h"
#include "Minty/Data/StringView.h"

namespace Minty
{
    /**
     * @brief Template struct for parsing different data types during serialization.
     */
    template <typename T>
    struct Parser;

    /*
    
    template<>
    struct Parser<NAME>
    {
        static Bool parse(StringView const str, NAME &value);
        static String to_string(NAME const &value);
    };

    */

    template <>
    struct Parser<Bool>
    {
        static Bool parse(StringView const str, Bool &value);
        static String to_string(Bool const &value);
    };

    template <>
    struct Parser<Int8>
    {
        static Bool parse(StringView const str, Int8 &value);
        static String to_string(Int8 const &value);
    };

    template <>
    struct Parser<Int16>
    {
        static Bool parse(StringView const str, Int16 &value);
        static String to_string(Int16 const &value);
    };

    template <>
    struct Parser<Int32>
    {
        static Bool parse(StringView const str, Int32 &value);
        static String to_string(Int32 const &value);
    };

    template <>
    struct Parser<Int64>
    {
        static Bool parse(StringView const str, Int64 &value);
        static String to_string(Int64 const &value);
    };

    template <>
    struct Parser<UInt8>
    {
        static Bool parse(StringView const str, UInt8 &value);
        static String to_string(UInt8 const &value);
    };

    template <>
    struct Parser<UInt16>
    {
        static Bool parse(StringView const str, UInt16 &value);
        static String to_string(UInt16 const &value);
    };

    template <>
    struct Parser<UInt32>
    {
        static Bool parse(StringView const str, UInt32 &value);
        static String to_string(UInt32 const &value);
    };

    template <>
    struct Parser<UInt64>
    {
        static Bool parse(StringView const str, UInt64 &value);
        static String to_string(UInt64 const &value);
    };

    template <>
    struct Parser<Float32>
    {
        static Bool parse(StringView const str, Float32 &value);
        static String to_string(Float32 const &value);
    };

    template <>
    struct Parser<Float64>
    {
        static Bool parse(StringView const str, Float64 &value);
        static String to_string(Float64 const &value);
    };
};

#endif // MINTY_SERIALIZATION_PARSER_H