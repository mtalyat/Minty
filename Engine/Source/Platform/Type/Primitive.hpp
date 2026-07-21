#pragma once

/**
 * @file Primitive.hpp
 * @brief Common type definitions for the platform.
 * @author Mitchell Talyat
 */

#include <typeindex>

namespace Minty
{
    using Bool = bool;
    using Char = char;
    using Int8 = signed char;
    using UInt8 = unsigned char;
    using Int16 = signed short;
    using UInt16 = unsigned short;
    using Int32 = signed int;
    using UInt32 = unsigned int;
    using Int64 = signed long long;
    using UInt64 = unsigned long long;
    using Float32 = float;
    using Float64 = double;

    using Byte = UInt8;
    using Int = Int32;
    using UInt = UInt32;
    using WInt = Int64;
    using WUInt = UInt64;
    using Float = Float32;
    using WFloat = Float64;

    using Index = UInt32;
    using Generation = UInt32;
    using Size = size_t;
    using Bookmark = Size;
    using TimePoint = Int64;

    using TypeID = std::type_index;
    using TypeInfo = std::type_info;
    using TypeIndex = Size;

    using StreamPosition = long long;
    using StreamSize = long long;

    using Pointer = void*;
    using PointerConst = void const*;
    using Null = std::nullptr_t;
}