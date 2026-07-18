#include "pch.hpp"
#include "ParsedTypes.hpp"
#include "Core/Data/StringBuilder.hpp"
#include "Core/Tool/Enum.hpp"

using namespace Minty;

template <typename T>
static Bool parse_binary(StringView const str, T &value)
{
    if (str.is_empty())
    {
        return false;
    }

    T result = 0;
    for (Size i = 0; i < str.get_size(); ++i)
    {
        Char const c = str[i];
        if (c != '0' && c != '1')
        {
            return false;
        }
        result = (result << 1) | static_cast<T>(c - '0');
    }

    value = result;
    return true;
}

template <typename T>
static Bool parse_hexadecimal(StringView const str, T &value)
{
    if (str.is_empty())
    {
        return false;
    }

    T result = 0;
    for (Size i = 0; i < str.get_size(); ++i)
    {
        Char const c = str[i];
        result <<= 4;

        if (c >= '0' && c <= '9')
        {
            result |= static_cast<T>(c - '0');
        }
        else if (c >= 'A' && c <= 'F')
        {
            result |= static_cast<T>(c - 'A' + 10);
        }
        else if (c >= 'a' && c <= 'f')
        {
            result |= static_cast<T>(c - 'a' + 10);
        }
        else
        {
            return false;
        }
    }

    value = result;
    return true;
}

template <typename T>
static Bool parse_integer_unsigned(StringView const str, T &value)
{
    if (str.is_empty())
    {
        return false;
    }

    if (str[0] == '-')
    {
        return false;
    }

    Size startIndex = 0;

    if (str[0] == '+')
    {
        startIndex = 1;
    }

    // Check for empty string after sign
    if (startIndex == str.get_size())
    {
        return false;
    }

    if (str.get_size() > 2 && str[startIndex] == '0')
    {
        switch (str[startIndex + 1])
        {
        case 'b':
        case 'B':
            return parse_binary(str.sub(startIndex + 2), value);
        case 'x':
        case 'X':
            return parse_hexadecimal(str.sub(startIndex + 2), value);
        }
    }

    T result = 0;
    for (Size i = startIndex; i < str.get_size(); ++i)
    {
        Char const c = str[i];
        if (c < '0' || c > '9')
        {
            return false;
        }
        result = result * 10 + static_cast<T>(c - '0');
    }

    value = result;
    return true;
}

template <typename T>
static Bool parse_integer_signed(StringView const str, T &value)
{
    if (str.is_empty())
    {
        return false;
    }

    Bool isNegative = false;
    Size startIndex = 0;

    if (str[0] == '-')
    {
        isNegative = true;
        startIndex = 1;
    }
    else if (str[0] == '+')
    {
        startIndex = 1;
    }

    // Check for empty string after sign
    if (startIndex == str.get_size())
    {
        return false;
    }

    if (str.get_size() > 2 && str[startIndex] == '0')
    {
        switch (str[startIndex + 1])
        {
        case 'b':
        case 'B':
        {
            T result = 0;
            Bool success = parse_binary(str.sub(startIndex + 2), result);
            if (!success)
            {
                return false;
            }
            value = isNegative ? -result : result;
            return true;
        }
        case 'x':
        case 'X':
        {
            T result = 0;
            Bool success = parse_hexadecimal(str.sub(startIndex + 2), result);
            if (!success)
            {
                return false;
            }
            value = isNegative ? -result : result;
            return true;
        }
        }
    }

    T result = 0;
    for (Size i = startIndex; i < str.get_size(); ++i)
    {
        Char const c = str[i];
        if (c < '0' || c > '9')
        {
            return false;
        }
        result = result * 10 + static_cast<T>(c - '0');
    }

    value = isNegative ? -result : result;
    return true;
}

template <typename T>
static Bool parse_floating_point(StringView const str, T &value)
{
    if (str.is_empty())
    {
        return false;
    }

    Bool isNegative = false;
    Size startIndex = 0;
    if (str[0] == '-')
    {
        isNegative = true;
        startIndex = 1;
    }
    else if (str[0] == '+')
    {
        startIndex = 1;
    }

    // Check for empty string after sign
    if (startIndex == str.get_size())
    {
        return false;
    }

    Bool decimalFound = false;
    T decimalFactor = static_cast<T>(0.1);
    T const decimalFactorReduction = static_cast<T>(0.1);
    T result = 0;
    for (Size i = startIndex; i < str.get_size(); ++i)
    {
        Char const c = str[i];
        if (c == '.')
        {
            if (decimalFound)
            {
                return false;
            }
            decimalFound = true;
            continue;
        }

        if (c < '0' || c > '9')
        {
            return false;
        }

        if (!decimalFound)
        {
            result = result * 10 + static_cast<T>(c - '0');
        }
        else
        {
            result += static_cast<T>(c - '0') * decimalFactor;
            decimalFactor *= decimalFactorReduction;
        }
    }
    value = isNegative ? -result : result;
    return true;
}

template<typename T, typename SingleT>
static Bool parse_2(StringView const str, T &value, Bool (*parseFunc)(StringView const, SingleT &))
{
    if (str.is_empty())
    {
        return false;
    }

    if (!str.starts_with('(') || !str.ends_with(')'))
    {
        return false;
    }

    Size separatorIndex = str.find_first(',');
    if (separatorIndex == INVALID_SIZE)
    {
        return false;
    }

    StringView firstPart = str.sub(1, separatorIndex - 1);
    StringView secondPart = str.sub(separatorIndex + 2, str.get_size() - separatorIndex - 3);

    SingleT firstValue;
    SingleT secondValue;

    if (!parseFunc(firstPart, firstValue) || !parseFunc(secondPart, secondValue))
    {
        return false;
    }

    value = T(firstValue, secondValue);
    return true;
}

template<typename T, typename SingleT>
static Bool parse_3(StringView const str, T &value, Bool (*parseFunc)(StringView const, SingleT &))
{
    if (str.is_empty())
    {
        return false;
    }

    if (!str.starts_with('(') || !str.ends_with(')'))
    {
        return false;
    }

    Size firstSeparatorIndex = str.find_first(',');
    if (firstSeparatorIndex == INVALID_SIZE)
    {
        return false;
    }

    Size secondSeparatorIndex = str.find_first(',', firstSeparatorIndex + 1);
    if (secondSeparatorIndex == INVALID_SIZE)
    {
        return false;
    }

    StringView firstPart = str.sub(1, firstSeparatorIndex - 1);
    StringView secondPart = str.sub(firstSeparatorIndex + 2, secondSeparatorIndex - firstSeparatorIndex - 2);
    StringView thirdPart = str.sub(secondSeparatorIndex + 2, str.get_size() - secondSeparatorIndex - 3);

    SingleT firstValue;
    SingleT secondValue;
    SingleT thirdValue;

    if (!parseFunc(firstPart, firstValue) || !parseFunc(secondPart, secondValue) || !parseFunc(thirdPart, thirdValue))
    {
        return false;
    }

    value = T(firstValue, secondValue, thirdValue);
    return true;
}

template<typename T, typename SingleT>
static Bool parse_4(StringView const str, T &value, Bool (*parseFunc)(StringView const, SingleT &))
{
    if (str.is_empty())
    {
        return false;
    }

    if (!str.starts_with('(') || !str.ends_with(')'))
    {
        return false;
    }

    Size firstSeparatorIndex = str.find_first(',');
    if (firstSeparatorIndex == INVALID_SIZE)
    {
        return false;
    }

    Size secondSeparatorIndex = str.find_first(',', firstSeparatorIndex + 1);
    if (secondSeparatorIndex == INVALID_SIZE)
    {
        return false;
    }

    Size thirdSeparatorIndex = str.find_first(',', secondSeparatorIndex + 1);
    if (thirdSeparatorIndex == INVALID_SIZE)
    {
        return false;
    }

    StringView firstPart = str.sub(1, firstSeparatorIndex - 1);
    StringView secondPart = str.sub(firstSeparatorIndex + 2, secondSeparatorIndex - firstSeparatorIndex - 2);
    StringView thirdPart = str.sub(secondSeparatorIndex + 2, thirdSeparatorIndex - secondSeparatorIndex - 2);
    StringView fourthPart = str.sub(thirdSeparatorIndex + 2, str.get_size() - thirdSeparatorIndex - 3);

    SingleT firstValue;
    SingleT secondValue;
    SingleT thirdValue;
    SingleT fourthValue;

    if (!parseFunc(firstPart, firstValue) || !parseFunc(secondPart, secondValue) ||
        !parseFunc(thirdPart, thirdValue) || !parseFunc(fourthPart, fourthValue))
    {
        return false;
    }

    value = T(firstValue, secondValue, thirdValue, fourthValue);
    return true;
}

template<typename T>
static String to_string_integer_unsigned(T const &value)
{
    if (value == 0)
    {
        return "0";
    }

    T temp = value;
    StringBuilder builder;

    while (temp > 0)
    {
        Char const digit = static_cast<Char>((temp % 10) + '0');
        builder.append(digit);
        temp /= 10;
    }

    builder.reverse();
    return builder.get_string();
}

template<typename T>
static String to_string_integer_signed(T const &value)
{
    if (value == 0)
    {
        return "0";
    }

    Bool isNegative = value < 0;
    T temp = isNegative ? -value : value;
    StringBuilder builder;

    while (temp > 0)
    {
        Char const digit = static_cast<Char>((temp % 10) + '0');
        builder.append(digit);
        temp /= 10;
    }

    if (isNegative)
    {
        Char minus = '-';
        builder.append(minus);
    }

    builder.reverse();
    return builder.get_string();
}

template<typename T>
static String to_string_floating_point(T const &value)
{
    StringBuilder builder;
    T temp = value;

    if (temp < 0)
    {
        builder.append('-');
        temp = -temp;
    }

    WInt integerPart = static_cast<WInt>(temp);
    T fractionalPart = temp - integerPart;

    builder.append(to_string_integer_unsigned(static_cast<WUInt>(integerPart)));

    if (fractionalPart > 0)
    {
        builder.append('.');

        for (Size i = 0; i < 6; ++i) // Limit to 6 decimal places
        {
            fractionalPart *= 10;
            Char digit = static_cast<Char>(static_cast<Int32>(fractionalPart) + '0');
            builder.append(digit);
            fractionalPart -= static_cast<Int32>(fractionalPart);
            if (fractionalPart == 0)
            {
                break;
            }
        }
    }

    return builder.get_string();
}

template<typename T, typename SingleT>
static String to_string_2(T const &value, String (*toStringFunc)(SingleT const &))
{
    StringBuilder builder;
    builder.append('(');
    builder.append(toStringFunc(value.x));
    builder.append(", ");
    builder.append(toStringFunc(value.y));
    builder.append(')');
    return builder.get_string();
}

template<typename T, typename SingleT>
static String to_string_3(T const &value, String (*toStringFunc)(SingleT const &))
{
    StringBuilder builder;
    builder.append('(');
    builder.append(toStringFunc(value.x));
    builder.append(", ");
    builder.append(toStringFunc(value.y));
    builder.append(", ");
    builder.append(toStringFunc(value.z));
    builder.append(')');
    return builder.get_string();
}

template<typename T, typename SingleT>
static String to_string_4(T const &value, String (*toStringFunc)(SingleT const &))
{
    StringBuilder builder;
    builder.append('(');
    builder.append(toStringFunc(value.x));
    builder.append(", ");
    builder.append(toStringFunc(value.y));
    builder.append(", ");
    builder.append(toStringFunc(value.z));
    builder.append(", ");
    builder.append(toStringFunc(value.w));
    builder.append(')');
    return builder.get_string();
}

Bool Minty::Parser<Bool>::parse(StringView const str, Bool &value)
{
    if (str.is_empty())
    {
        return false;
    }

    Char const c = str.front();
    value = c != 'F' && c != 'f' && c != '0';
    return true;
}

String Minty::Parser<Bool>::to_string(Bool const &value)
{
    return value ? "TRUE" : "FALSE";
}

Bool Minty::Parser<Int8>::parse(StringView const str, Int8 &value)
{
    return parse_integer_signed<Int8>(str, value);
}

String Minty::Parser<Int8>::to_string(Int8 const &value)
{
    return to_string_integer_signed<Int8>(value);
}

Bool Minty::Parser<Int16>::parse(StringView const str, Int16 &value)
{
    return parse_integer_signed<Int16>(str, value);
}

String Minty::Parser<Int16>::to_string(Int16 const &value)
{
    return to_string_integer_signed<Int16>(value);
}

Bool Minty::Parser<Int32>::parse(StringView const str, Int32 &value)
{
    return parse_integer_signed<Int32>(str, value);
}

String Minty::Parser<Int32>::to_string(Int32 const &value)
{
    return to_string_integer_signed<Int32>(value);
}

Bool Minty::Parser<Int64>::parse(StringView const str, Int64 &value)
{
    return parse_integer_signed<Int64>(str, value);
}

String Minty::Parser<Int64>::to_string(Int64 const &value)
{
    return to_string_integer_signed<Int64>(value);
}

Bool Minty::Parser<UInt8>::parse(StringView const str, UInt8 &value)
{
    return parse_integer_unsigned<UInt8>(str, value);
}

String Minty::Parser<UInt8>::to_string(UInt8 const &value)
{
    return to_string_integer_unsigned<UInt8>(value);
}

Bool Minty::Parser<UInt16>::parse(StringView const str, UInt16 &value)
{
    return parse_integer_unsigned<UInt16>(str, value);
}

String Minty::Parser<UInt16>::to_string(UInt16 const &value)
{
    return to_string_integer_unsigned<UInt16>(value);
}

Bool Minty::Parser<UInt32>::parse(StringView const str, UInt32 &value)
{
    return parse_integer_unsigned<UInt32>(str, value);
}

String Minty::Parser<UInt32>::to_string(UInt32 const &value)
{
    return to_string_integer_unsigned<UInt32>(value);
}

Bool Minty::Parser<UInt64>::parse(StringView const str, UInt64 &value)
{
    return parse_integer_unsigned<UInt64>(str, value);
}

String Minty::Parser<UInt64>::to_string(UInt64 const &value)
{
    return to_string_integer_unsigned<UInt64>(value);
}

Bool Minty::Parser<Float32>::parse(StringView const str, Float &value)
{
    return parse_floating_point<Float32>(str, value);
}

String Minty::Parser<Float32>::to_string(Float const &value)
{
    return to_string_floating_point<Float32>(value);
}

Bool Minty::Parser<Float64>::parse(StringView const str, Float64 &value)
{
    return parse_floating_point<Float64>(str, value);
}

String Minty::Parser<Float64>::to_string(Float64 const &value)
{
    return to_string_floating_point<Float64>(value);
}

Bool Minty::Parser<Char>::parse(StringView const str, Char &value)
{
    if (str.is_empty())
    {
        return false;
    }

    value = str.front();
    return true;
}

String Minty::Parser<Char>::to_string(Char const &value)
{
    return String(value, 1);
}

Bool Minty::Parser<Bool2>::parse(StringView const str, Bool2 &value)
{
    return parse_2<Bool2, Bool>(str, value, Minty::Parser<Bool>::parse);
}

String Minty::Parser<Bool2>::to_string(Bool2 const &value)
{
    return to_string_2<Bool2, Bool>(value, Minty::Parser<Bool>::to_string);
}

Bool Minty::Parser<Bool3>::parse(StringView const str, Bool3 &value)
{
    return parse_3<Bool3, Bool>(str, value, Minty::Parser<Bool>::parse);
}

String Minty::Parser<Bool3>::to_string(Bool3 const &value)
{
    return to_string_3<Bool3, Bool>(value, Minty::Parser<Bool>::to_string);
}

Bool Minty::Parser<Bool4>::parse(StringView const str, Bool4 &value)
{
    return parse_4<Bool4, Bool>(str, value, Minty::Parser<Bool>::parse);
}

String Minty::Parser<Bool4>::to_string(Bool4 const &value)
{
    return to_string_4<Bool4, Bool>(value, Minty::Parser<Bool>::to_string);
}

Bool Minty::Parser<Int2>::parse(StringView const str, Int2 &value)
{
    return parse_2<Int2, Int>(str, value, Minty::Parser<Int>::parse);
}

String Minty::Parser<Int2>::to_string(Int2 const &value)
{
    return to_string_2<Int2, Int>(value, Minty::Parser<Int>::to_string);
}

Bool Minty::Parser<Int3>::parse(StringView const str, Int3 &value)
{
    return parse_3<Int3, Int>(str, value, Minty::Parser<Int>::parse);
}

String Minty::Parser<Int3>::to_string(Int3 const &value)
{
    return to_string_3<Int3, Int>(value, Minty::Parser<Int>::to_string);
}

Bool Minty::Parser<Int4>::parse(StringView const str, Int4 &value)
{
    return parse_4<Int4, Int>(str, value, Minty::Parser<Int>::parse);
}

String Minty::Parser<Int4>::to_string(Int4 const &value)
{
    return to_string_4<Int4, Int>(value, Minty::Parser<Int>::to_string);
}

Bool Minty::Parser<UInt2>::parse(StringView const str, UInt2 &value)
{
    return parse_2<UInt2, UInt>(str, value, Minty::Parser<UInt>::parse);
}

String Minty::Parser<UInt2>::to_string(UInt2 const &value)
{
    return to_string_2<UInt2, UInt>(value, Minty::Parser<UInt>::to_string);
}

Bool Minty::Parser<UInt3>::parse(StringView const str, UInt3 &value)
{
    return parse_3<UInt3, UInt>(str, value, Minty::Parser<UInt>::parse);
}

String Minty::Parser<UInt3>::to_string(UInt3 const &value)
{
    return to_string_3<UInt3, UInt>(value, Minty::Parser<UInt>::to_string);
}

Bool Minty::Parser<UInt4>::parse(StringView const str, UInt4 &value)
{
    return parse_4<UInt4, UInt>(str, value, Minty::Parser<UInt>::parse);
}

String Minty::Parser<UInt4>::to_string(UInt4 const &value)
{
    return to_string_4<UInt4, UInt>(value, Minty::Parser<UInt>::to_string);
}

Bool Minty::Parser<Float2>::parse(StringView const str, Float2 &value)
{
    return parse_2<Float2, Float>(str, value, Minty::Parser<Float>::parse);
}

String Minty::Parser<Float2>::to_string(Float2 const &value)
{
    return to_string_2<Float2, Float>(value, Minty::Parser<Float>::to_string);
}

Bool Minty::Parser<Float3>::parse(StringView const str, Float3 &value)
{
    return parse_3<Float3, Float>(str, value, Minty::Parser<Float>::parse);
}

String Minty::Parser<Float3>::to_string(Float3 const &value)
{
    return to_string_3<Float3, Float>(value, Minty::Parser<Float>::to_string);
}

Bool Minty::Parser<Float4>::parse(StringView const str, Float4 &value)
{
    return parse_4<Float4, Float>(str, value, Minty::Parser<Float>::parse);
}

String Minty::Parser<Float4>::to_string(Float4 const &value)
{
    return to_string_4<Float4, Float>(value, Minty::Parser<Float>::to_string);
}

Bool Minty::Parser<WInt2>::parse(StringView const str, WInt2 &value)
{
    return parse_2<WInt2, WInt>(str, value, Minty::Parser<WInt>::parse);
}

String Minty::Parser<WInt2>::to_string(WInt2 const &value)
{
    return to_string_2<WInt2, WInt>(value, Minty::Parser<WInt>::to_string);
}

Bool Minty::Parser<WInt3>::parse(StringView const str, WInt3 &value)
{
    return parse_3<WInt3, WInt>(str, value, Minty::Parser<WInt>::parse);
}

String Minty::Parser<WInt3>::to_string(WInt3 const &value)
{
    return to_string_3<WInt3, WInt>(value, Minty::Parser<WInt>::to_string);
}

Bool Minty::Parser<WInt4>::parse(StringView const str, WInt4 &value)
{
    return parse_4<WInt4, WInt>(str, value, Minty::Parser<WInt>::parse);
}

String Minty::Parser<WInt4>::to_string(WInt4 const &value)
{
    return to_string_4<WInt4, WInt>(value, Minty::Parser<WInt>::to_string);
}

Bool Minty::Parser<WUInt2>::parse(StringView const str, WUInt2 &value)
{
    return parse_2<WUInt2, WUInt>(str, value, Minty::Parser<WUInt>::parse);
}

String Minty::Parser<WUInt2>::to_string(WUInt2 const &value)
{
    return to_string_2<WUInt2, WUInt>(value, Minty::Parser<WUInt>::to_string);
}

Bool Minty::Parser<WUInt3>::parse(StringView const str, WUInt3 &value)
{
    return parse_3<WUInt3, WUInt>(str, value, Minty::Parser<WUInt>::parse);
}

String Minty::Parser<WUInt3>::to_string(WUInt3 const &value)
{
    return to_string_3<WUInt3, WUInt>(value, Minty::Parser<WUInt>::to_string);
}

Bool Minty::Parser<WUInt4>::parse(StringView const str, WUInt4 &value)
{
    return parse_4<WUInt4, WUInt>(str, value, Minty::Parser<WUInt>::parse);
}

String Minty::Parser<WUInt4>::to_string(WUInt4 const &value)
{
    return to_string_4<WUInt4, WUInt>(value, Minty::Parser<WUInt>::to_string);
}

Bool Minty::Parser<WFloat2>::parse(StringView const str, WFloat2 &value)
{
    return parse_2<WFloat2, WFloat>(str, value, Minty::Parser<WFloat>::parse);
}

String Minty::Parser<WFloat2>::to_string(WFloat2 const &value)
{
    return to_string_2<WFloat2, WFloat>(value, Minty::Parser<WFloat>::to_string);
}

Bool Minty::Parser<WFloat3>::parse(StringView const str, WFloat3 &value)
{
    return parse_3<WFloat3, WFloat>(str, value, Minty::Parser<WFloat>::parse);
}

String Minty::Parser<WFloat3>::to_string(WFloat3 const &value)
{
    return to_string_3<WFloat3, WFloat>(value, Minty::Parser<WFloat>::to_string);
}

Bool Minty::Parser<WFloat4>::parse(StringView const str, WFloat4 &value)
{
    return parse_4<WFloat4, WFloat>(str, value, Minty::Parser<WFloat>::parse);
}

String Minty::Parser<WFloat4>::to_string(WFloat4 const &value)
{
    return to_string_4<WFloat4, WFloat>(value, Minty::Parser<WFloat>::to_string);
}

Bool Minty::Parser<Quaternion>::parse(StringView const str, Quaternion &value)
{
    return parse_4<Quaternion, Float>(str, value, Minty::Parser<Float>::parse);
}

String Minty::Parser<Quaternion>::to_string(Quaternion const &value)
{
    return to_string_4<Quaternion, Float>(value, Minty::Parser<Float>::to_string);
}