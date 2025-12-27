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

Bool Minty::Parser<Float32>::parse(StringView const str, Float32 &value)
{
    return parse_floating_point<Float32>(str, value);
}

String Minty::Parser<Float32>::to_string(Float32 const &value)
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