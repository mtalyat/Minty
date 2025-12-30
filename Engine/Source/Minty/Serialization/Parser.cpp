#include "pch.h"
#include "Reader.h"
#include "Parser.h"

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

    Bool decimalFound = false;
    T decimalFactor = 0.1;
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
            decimalFactor *= 0.1;
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

    Size separatorIndex = str.find(',');
    if (separatorIndex == String::npos)
    {
        return false;
    }

    StringView firstPart = str.sub(1, separatorIndex - 1).trim();
    StringView secondPart = str.sub(separatorIndex + 1, str.get_size() - separatorIndex - 2).trim();

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

    Size firstSeparatorIndex = str.find(',');
    if (firstSeparatorIndex == String::npos)
    {
        return false;
    }

    Size secondSeparatorIndex = str.find(',', firstSeparatorIndex + 1);
    if (secondSeparatorIndex == String::npos)
    {
        return false;
    }

    StringView firstPart = str.sub(1, firstSeparatorIndex - 1).trim();
    StringView secondPart = str.sub(firstSeparatorIndex + 1, secondSeparatorIndex - firstSeparatorIndex - 1).trim();
    StringView thirdPart = str.sub(secondSeparatorIndex + 1, str.get_size() - secondSeparatorIndex - 2).trim();

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

    Size firstSeparatorIndex = str.find(',');
    if (firstSeparatorIndex == String::npos)
    {
        return false;
    }

    Size secondSeparatorIndex = str.find(',', firstSeparatorIndex + 1);
    if (secondSeparatorIndex == String::npos)
    {
        return false;
    }

    Size thirdSeparatorIndex = str.find(',', secondSeparatorIndex + 1);
    if (thirdSeparatorIndex == String::npos)
    {
        return false;
    }

    StringView firstPart = str.sub(1, firstSeparatorIndex - 1).trim();
    StringView secondPart = str.sub(firstSeparatorIndex + 1, secondSeparatorIndex - firstSeparatorIndex - 1).trim();
    StringView thirdPart = str.sub(secondSeparatorIndex + 1, thirdSeparatorIndex - secondSeparatorIndex - 1).trim();
    StringView fourthPart = str.sub(thirdSeparatorIndex + 1, str.get_size() - thirdSeparatorIndex - 2).trim();

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
    String result;

    while (temp > 0)
    {
        Char digit = static_cast<Char>((temp % 10) + '0');
        result.insert(0, &digit, 1);
        temp /= 10;
    }

    return result;
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
    String result;

    while (temp > 0)
    {
        Char digit = static_cast<Char>((temp % 10) + '0');
        result.insert(0, &digit, 1);
        temp /= 10;
    }

    if (isNegative)
    {
        Char minus = '-';
        result.insert(0, &minus, 1);
    }

    return result;
}

template<typename T>
static String to_string_floating_point(T const &value)
{
    String result;
    T temp = value;

    if (temp < 0)
    {
        result.append('-');
        temp = -temp;
    }

    T integerPart = static_cast<T>(temp);
    T fractionalPart = temp - integerPart;

    result.append(to_string_integer_unsigned(static_cast<std::make_unsigned_t<T>>(integerPart)));

    if (fractionalPart > 0)
    {
        result.append('.');

        for (Size i = 0; i < 6; ++i) // Limit to 6 decimal places
        {
            fractionalPart *= 10;
            Char digit = static_cast<Char>(static_cast<Int32>(fractionalPart) + '0');
            result.append(digit);
            fractionalPart -= static_cast<Int32>(fractionalPart);
            if (fractionalPart == 0)
            {
                break;
            }
        }
    }

    return result;
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
    return builder.to_string();
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
    return builder.to_string();
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
    return builder.to_string();
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

Bool Minty::Parser<Float>::parse(StringView const str, Float &value)
{
    return parse_floating_point<Float>(str, value);
}

String Minty::Parser<Float>::to_string(Float const &value)
{
    return to_string_floating_point<Float>(value);
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

Bool Minty::Parser<UWInt2>::parse(StringView const str, UWInt2 &value)
{
    return parse_2<UWInt2, UWInt>(str, value, Minty::Parser<UWInt>::parse);
}

String Minty::Parser<UWInt2>::to_string(UWInt2 const &value)
{
    return to_string_2<UWInt2, UWInt>(value, Minty::Parser<UWInt>::to_string);
}

Bool Minty::Parser<UWInt3>::parse(StringView const str, UWInt3 &value)
{
    return parse_3<UWInt3, UWInt>(str, value, Minty::Parser<UWInt>::parse);
}

String Minty::Parser<UWInt3>::to_string(UWInt3 const &value)
{
    return to_string_3<UWInt3, UWInt>(value, Minty::Parser<UWInt>::to_string);
}

Bool Minty::Parser<UWInt4>::parse(StringView const str, UWInt4 &value)
{
    return parse_4<UWInt4, UWInt>(str, value, Minty::Parser<UWInt>::parse);
}

String Minty::Parser<UWInt4>::to_string(UWInt4 const &value)
{
    return to_string_4<UWInt4, UWInt>(value, Minty::Parser<UWInt>::to_string);
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