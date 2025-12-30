#ifndef MINTY_SERIALIZATION_PARSER_H
#define MINTY_SERIALIZATION_PARSER_H

/**
 * @file Parser.h
 * @brief Header file defining the Parser class for serialization.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Core/Math.h"
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

    template<>
    struct Parser<Char>
    {
        static Bool parse(StringView const str, Char &value);
        static String to_string(Char const &value);
    };

    template<>
    struct Parser<Char const*>
    {
        inline static Bool parse(StringView const str, Char const*& value) { return false; }
        inline static String to_string(Char const* const& value) { return StringView(value); }
    };

    template<Size N>
    struct Parser<Char[N]> 
    {
        inline static Bool parse(StringView const str, Char(&value)[N]) { return false; }
        inline static String to_string(Char const(&value)[N]) { return StringView(value); }
    };

    template<>
    struct Parser<StringView>
    {
        inline static Bool parse(StringView const str, StringView &value) { value = str; return true; }
        inline static String to_string(StringView const &value) { return String(value); }
    };

    template <>
    struct Parser<String>
    {
        inline static Bool parse(StringView const str, String &value) { value = String(str); return true; }
        inline static String to_string(String const &value) { return value; }
    };

    template <>
    struct Parser<Bool2>
    {
        static Bool parse(StringView const str, Bool2 &value);
        static String to_string(Bool2 const &value);
    };

    template<>
    struct Parser<Bool3>
    {
        static Bool parse(StringView const str, Bool3 &value);
        static String to_string(Bool3 const &value);
    };

    template<>
    struct Parser<Bool4>
    {
        static Bool parse(StringView const str, Bool4 &value);
        static String to_string(Bool4 const &value);
    };

    template<>
    struct Parser<Int2>
    {
        static Bool parse(StringView const str, Int2 &value);
        static String to_string(Int2 const &value);
    };

    template<>
    struct Parser<Int3>
    {
        static Bool parse(StringView const str, Int3 &value);
        static String to_string(Int3 const &value);
    };

    template<>
    struct Parser<Int4>
    {
        static Bool parse(StringView const str, Int4 &value);
        static String to_string(Int4 const &value);
    };

    template<>
    struct Parser<UInt2>
    {
        static Bool parse(StringView const str, UInt2 &value);
        static String to_string(UInt2 const &value);
    };

    template<>
    struct Parser<UInt3>
    {
        static Bool parse(StringView const str, UInt3 &value);
        static String to_string(UInt3 const &value);
    };

    template<>
    struct Parser<UInt4>
    {
        static Bool parse(StringView const str, UInt4 &value);
        static String to_string(UInt4 const &value);
    };

    template<>
    struct Parser<Float2>
    {
        static Bool parse(StringView const str, Float2 &value);
        static String to_string(Float2 const &value);
    };

    template<>
    struct Parser<Float3>
    {
        static Bool parse(StringView const str, Float3 &value);
        static String to_string(Float3 const &value);
    };

    template<>
    struct Parser<Float4>
    {
        static Bool parse(StringView const str, Float4 &value);
        static String to_string(Float4 const &value);
    };

    template<>
    struct Parser<WInt2>
    {
        static Bool parse(StringView const str, WInt2 &value);
        static String to_string(WInt2 const &value);
    };

    template<>
    struct Parser<WInt3>
    {
        static Bool parse(StringView const str, WInt3 &value);
        static String to_string(WInt3 const &value);
    };

    template<>
    struct Parser<WInt4>
    {
        static Bool parse(StringView const str, WInt4 &value);
        static String to_string(WInt4 const &value);
    };

    template<>
    struct Parser<UWInt2>
    {
        static Bool parse(StringView const str, UWInt2 &value);
        static String to_string(UWInt2 const &value);
    };

    template<>
    struct Parser<UWInt3>
    {
        static Bool parse(StringView const str, UWInt3 &value);
        static String to_string(UWInt3 const &value);
    };

    template<>
    struct Parser<UWInt4>
    {
        static Bool parse(StringView const str, UWInt4 &value);
        static String to_string(UWInt4 const &value);
    };

    template<>
    struct Parser<WFloat2>
    {
        static Bool parse(StringView const str, WFloat2 &value);
        static String to_string(WFloat2 const &value);
    };

    template<>
    struct Parser<WFloat3>
    {
        static Bool parse(StringView const str, WFloat3 &value);
        static String to_string(WFloat3 const &value);
    };

    template<>
    struct Parser<WFloat4>
    {
        static Bool parse(StringView const str, WFloat4 &value);
        static String to_string(WFloat4 const &value);
    };
};

#endif // MINTY_SERIALIZATION_PARSER_H