#ifndef MINTY_FORMAT_H
#define MINTY_FORMAT_H

/**
 * @file Format.h
 * @brief Header file for string formatting utilities.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/String.h"
#include "Minty/Data/StringBuilder.h"
#include "Minty/Serialization/Parser.h"

namespace Minty
{
    namespace Internal
    {
        template <typename T>
        void append_value(StringBuilder &builder, T const &value)
        {
            builder.append(Parser<T>::to_string(value));
        }

        template <typename T, typename... Args>
        void append_value(StringBuilder &builder, T const &value, Args const &...args)
        {
            builder.append(Parser<T>::to_string(value));
            if constexpr (sizeof...(args) > 0)
            {
                append_value(builder, args...);
            }
        }

        template <typename T>
        void append_value_with_spacing(StringBuilder &builder, T const &value)
        {
            builder.append(' ');
            builder.append(Parser<T>::to_string(value));
        }

        template <typename T, typename... Args>
        void append_value_with_spacing(StringBuilder &builder, T const &value, Args const &...args)
        {
            builder.append(Parser<T>::to_string(value));
            if constexpr (sizeof...(args) > 0)
            {
                append_value(builder, args...);
            }
        }
    }

    /**
     * @brief Format a string using the specified format and arguments.
     * @tparam Args The types of the arguments to format.
     * @param allocator The allocator to use for the resulting string.
     * @param format The format string.
     * @param args The arguments to format into the string.
     * @return The formatted string.
     */
    template <typename... Args>
    String format(String const formatStr, Args const &...args)
    {
        Size formatSize = formatStr.get_size();
        StringBuilder builder(formatStr.get_size() * 2);
        Size argIndex = 0;
        constexpr Size argCount = sizeof...(args);

        // Parse the formatStr string
        for (Size i = 0; i < formatSize; i++)
        {
            if (i + 1 < formatSize)
            {
                if (formatStr[i] == '{')
                {
                    if (formatStr[i + 1] == '{')
                    {
                        // Escaped '{'
                        builder.append('{');
                        ++i; // Skip the next '{'
                        continue;
                    }
                    else if (formatStr[i + 1] == '}')
                    {
                        // Append argument
                        if (argIndex < argCount)
                        {
                            // Use fold expression to get the correct argument
                            Size currentIndex = 0;
                            ((currentIndex++ == argIndex ? Internal::append_value(builder, args) : void(0)), ...);
                            ++argIndex;
                        }

                        // Skip the next '}'
                        ++i;
                        continue;
                    }
                    else
                    {
                        // Ignore malformed '{', for now just append it
                        // TODO: add additional formatting options
                        builder.append(formatStr[i]);
                        continue;
                    }
                } else if (formatStr[i] == '}')
                {
                    if (formatStr[i + 1] == '}')
                    {
                        // Escaped '}'
                        builder.append('}');
                        ++i; // Skip the next '}'
                        continue;
                    }
                }
            }
            
            // Append regular character
            builder.append(formatStr[i]);
        }

        // Append the remaining arguments (if any)
        while (argIndex < argCount)
        {
            Size currentIndex = 0;
            ((currentIndex++ == argIndex ? Internal::append_value_with_spacing(builder, args) : void(0)), ...);
            ++argIndex;
        }

        return builder.get_string();
    }
}

/**
 * @brief Macro for formatting strings using the default allocator.
 * @param msg The format string.
 */
#define F(msg, ...) Minty::format(msg, ##__VA_ARGS__)

#endif // MINTY_FORMAT_H