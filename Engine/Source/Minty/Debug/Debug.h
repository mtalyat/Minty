#ifndef MINTY_DEBUG_DEBUG_H
#define MINTY_DEBUG_DEBUG_H

/**
 * @file Debug.h
 * @brief Header file for debug utilities.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Macro.h"
#include "Minty/Core/Types.h"
#include "Minty/Debug/DebugFlags.h"
#include "Minty/Debug/Error.h"
#include "Minty/Log/LogLevel.h"
#include "Minty/Data/StringView.h"

namespace Minty
{
    /**
     * @class Debug
     * @brief Class providing debug utilities such as logging and error handling.
     */
    class Debug
    {
#pragma region Constructors

    private:
        Debug() = delete;
        ~Debug() = delete;

#pragma endregion

#pragma region Accessors

    public:
        /**
         * @brief Sets the debug flags.
         * @param flags The DebugFlags to set.
         */
        static void set_flags(DebugFlags const flags);

        /**
         * @brief Gets the current debug flags.
         * @return The current DebugFlags.
         */
        inline static DebugFlags get_flags() { return s_flags; }

#pragma endregion

#pragma region Methods

    public:
        /**
         * @brief Logs a message with the specified log level.
         * @param level The log level.
         * @param message The message to log.
         */
        static void log(LogLevel const level, StringView const message);

        /**
         * @brief Logs an error code with the specified log level.
         * @param level The log level.
         */
        static void log(LogLevel const level, ErrorCode const errorCode);

        /**
         * @brief Logs an error code with a message and the specified log level.
         * @param level The log level.
         * @param errorCode The error code.
         * @param message The message to log.
         */
        static void log(LogLevel const level, ErrorCode const errorCode, StringView const message);

        /**
         * @brief Sets the foreground color for terminal output.
         * @param color The color to set.
         */
        static void flush();

        /**
         * @brief Logs the current stack trace to the debug output.
         * @note This function is only available in debug builds when DebugFlags::StackTrace is enabled.
         */
        static void log_stack_trace();

#pragma endregion

#pragma region Variables

    private:
        static DebugFlags s_flags;

#pragma endregion
    };
}

#ifdef MINTY_DEBUG
// if debugging and using Visual Studio, insert debug break
#ifdef _MSC_VER
#define MINTY_BREAK() __debugbreak()
#else
#error "Debug break not implemented for this compiler."
#endif // _MSC_VER
#else
#define MINTY_BREAK()
#endif // MINTY_DEBUG

/**
 * @brief Macro to log a message with a specified log level.
 * @note Always active.
 */
#define MINTY_LOG(level, msg)             \
    do                                    \
    {                                     \
        Minty::Debug::log(level, F(msg)); \
    } while (0)
/**
 * @brief Macro to log a formatted message with a specified log level.
 * @note Always active.
 */
#define MINTY_LOG_F(level, fmt, ...)                     \
    do                                                   \
    {                                                    \
        Minty::Debug::log(level, F(fmt, ##__VA_ARGS__)); \
    } while (0)

/**
 * @brief Macro to log a message with a specified log level. Includes file, function and line number.
 * @note Always active.
 */
#define MINTY_LOG_TRACE(level, msg)                 \
    do                                              \
    {                                               \
        Minty::Debug::log(level, "{" __FILE__ "}"); \
        Minty::Debug::log(level, msg);              \
    } while (0)
/**
 * @brief Macro to log a formatted message with a specified log level. Includes file, function and line number.
 * @note Always active.
 */
#define MINTY_LOG_TRACE_F(level, fmt, ...)                                                                           \
    do                                                                                                               \
    {                                                                                                                \
        Minty::Debug::log(level, F("{{ {} -> {}(): {} }} {}", __FILE__, __func__, __LINE__, F(fmt, ##__VA_ARGS__))); \
    } while (0)

#ifdef MINTY_DEBUG
/**
 * @brief Macro to log a debug message.
 * @note Only active in debug builds.
 */
#define MINTY_LOG_DEBUG(msg)                    \
    do                                          \
    {                                           \
        MINTY_LOG(Minty::LogLevel::Debug, msg); \
    } while (0)
/**
 * @brief Macro to log a formatted debug message.
 * @note Only active in debug builds.
 */
#define MINTY_LOG_DEBUG_F(fmt, ...)                               \
    do                                                            \
    {                                                             \
        MINTY_LOG(Minty::LogLevel::Debug, F(fmt, ##__VA_ARGS__)); \
    } while (0)
#else
#define MINTY_LOG_DEBUG(msg, ...)
#define MINTY_LOG_DEBUG_F(fmt, ...)
#endif

#ifdef MINTY_DEBUG
/**
 * @brief Macro to log an info message.
 * @note Only active in debug builds.
 */
#define MINTY_LOG_INFO(msg)                    \
    do                                         \
    {                                          \
        MINTY_LOG(Minty::LogLevel::Info, msg); \
    } while (0)
/**
 * @brief Macro to log a formatted info message.
 * @note Only active in debug builds.
 */
#define MINTY_LOG_INFO_F(fmt, ...)                               \
    do                                                           \
    {                                                            \
        MINTY_LOG(Minty::LogLevel::Info, F(fmt, ##__VA_ARGS__)); \
    } while (0)
#else
#define MINTY_LOG_INFO(msg, ...)
#define MINTY_LOG_INFO_F(fmt, ...)
#endif

/**
 * @brief Macro to log a message.
 * @note Always active.
 */
#define MINTY_LOG_MESSAGE(msg)                    \
    do                                            \
    {                                             \
        MINTY_LOG(Minty::LogLevel::Message, msg); \
    } while (0)
/**
 * @brief Macro to log a formatted message.
 * @note Always active.
 */
#define MINTY_LOG_MESSAGE_F(fmt, ...)                               \
    do                                                              \
    {                                                               \
        MINTY_LOG(Minty::LogLevel::Message, F(fmt, ##__VA_ARGS__)); \
    } while (0)

#ifdef MINTY_DEBUG
/**
 * @brief Macro to log a warning message.
 * @note Only active in debug builds.
 */
#define MINTY_LOG_WARNING(msg)                    \
    do                                            \
    {                                             \
        MINTY_LOG(Minty::LogLevel::Warning, msg); \
    } while (0)
/**
 * @brief Macro to log a formatted warning message.
 * @note Only active in debug builds.
 */
#define MINTY_LOG_WARNING_F(fmt, ...)                               \
    do                                                              \
    {                                                               \
        MINTY_LOG(Minty::LogLevel::Warning, F(fmt, ##__VA_ARGS__)); \
    } while (0)
#else
#define MINTY_LOG_WARNING(msg, ...)
#define MINTY_LOG_WARNING_F(fmt, ...)
#endif

/**
 * @brief Macro to log an error message.
 * @note Always active.
 */
#define MINTY_LOG_ERROR(msg)                          \
    do                                                \
    {                                                 \
        MINTY_LOG_TRACE(Minty::LogLevel::Error, msg); \
    } while (0)
/**
 * @brief Macro to log a formatted error message.
 * @note Always active.
 */
#define MINTY_LOG_ERROR_F(fmt, ...)                                     \
    do                                                                  \
    {                                                                   \
        MINTY_LOG_TRACE(Minty::LogLevel::Error, F(fmt, ##__VA_ARGS__)); \
    } while (0)

/**
 * @brief Macro to log a fatal message.
 * @note Always active.
 */
#define MINTY_LOG_CRITICAL(msg)                          \
    do                                                   \
    {                                                    \
        MINTY_LOG_TRACE(Minty::LogLevel::Critical, msg); \
        Minty::Debug::flush();                           \
        MINTY_BREAK();                                   \
    } while (0)
/**
 * @brief Macro to log a formatted fatal message.
 * @note Always active.
 */
#define MINTY_LOG_CRITICAL_F(fmt, ...)                                     \
    do                                                                     \
    {                                                                      \
        MINTY_LOG_TRACE(Minty::LogLevel::Critical, F(fmt, ##__VA_ARGS__)); \
        Minty::Debug::flush();                                             \
        MINTY_BREAK();                                                     \
    } while (0)

/**
 * @brief Macro to abort execution with a message.
 * @note Always active.
 */
#define MINTY_ABORT(errorCode)                                   \
    do                                                           \
    {                                                            \
        Minty::set_error(errorCode);                             \
        MINTY_LOG_CRITICAL(Minty::get_error_message(errorCode)); \
        std::abort();                                            \
    } while (0)
/**
 * @brief Macro to abort execution with a formatted message.
 * @note Always active.
 */
#define MINTY_ABORT_F(errorCode, ...)                                                \
    do                                                                               \
    {                                                                                \
        Minty::set_error(errorCode);                                                 \
        MINTY_LOG_CRITICAL_F(F(Minty::get_error_message(errorCode), ##__VA_ARGS__)); \
        std::abort();                                                                \
    } while (0)

#ifdef MINTY_DEBUG
/**
 * @brief Macro to assert a condition.
 * @note Only active in debug builds.
 */
#define MINTY_ASSERT(condition, errorCode)                           \
    do                                                               \
    {                                                                \
        if (!(condition))                                            \
        {                                                            \
            Minty::set_error(errorCode);                             \
            MINTY_LOG_CRITICAL(Minty::get_error_message(errorCode)); \
        }                                                            \
    } while (0)
/**
 * @brief Macro to assert a condition with a formatted message.
 * @note Only active in debug builds.
 */
#define MINTY_ASSERT_F(condition, errorCode, ...)                                     \
    do                                                                                \
    {                                                                                 \
        if (!(condition))                                                             \
        {                                                                             \
            Minty::set_error(errorCode);                                              \
            MINTY_LOG_CRITICAL_F(Minty::get_error_message(errorCode), ##__VA_ARGS__); \
        }                                                                             \
    } while (0)
#else
#define MINTY_ASSERT_F(condition, errorCode)
#define MINTY_ASSERT_F(condition, errorCode, ...)
#endif

#ifdef MINTY_DEBUG
/**
 * @brief Macro to indicate a not implemented code path.
 * @note Only active in debug builds.
 */
#define MINTY_NOT_IMPLEMENTED()                                                         \
    do                                                                                  \
    {                                                                                   \
        Minty::set_error(Minty::ErrorCode::NotImplemented);                             \
        MINTY_LOG_CRITICAL(Minty::get_error_message(Minty::ErrorCode::NotImplemented)); \
        MINTY_BREAK();                                                                  \
        std::abort();                                                                   \
    } while (0)
#else
#define MINTY_NOT_IMPLEMENTED()
#endif

/**
 * @brief Macro to log and set an error.
 * @note Always active.
 */
#define MINTY_ERROR(errorCode)                                \
    do                                                        \
    {                                                         \
        Minty::set_error(errorCode);                          \
        MINTY_LOG_ERROR(Minty::get_error_message(errorCode)); \
    } while (0)
/**
 * @brief Macro to log and set a formatted error.
 * @note Always active.
 */
#define MINTY_ERROR_F(errorCode, ...)                                             \
    do                                                                            \
    {                                                                             \
        Minty::set_error(errorCode);                                              \
        MINTY_LOG_ERROR_F(F(Minty::get_error_message(errorCode), ##__VA_ARGS__)); \
    } while (0)

#endif // MINTY_DEBUG_DEBUG_H