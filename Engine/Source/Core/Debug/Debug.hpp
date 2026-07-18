#pragma once

/**
 * @file Debug.h
 * @brief Header file for debug utilities.
 * @author Mitchell Talyat
 */

#include "Platform/Macro/Keyword.hpp"
#include "Platform/Macro/Build.hpp"
#include "Platform/Type/Primitive.hpp"
#include "Core/Type/Severity.hpp"
#include "Error.hpp"

namespace Minty
{
    class Logger;
    struct DebugInfo;

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

#pragma region Methods

    public:
        /**
         * @brief Initializes the debug system with the specified debug info.
         * @param info The DebugInfo to initialize with.
         */
        static void initialize(DebugInfo const& info);

        /**
         * @brief Disposes of the debug system.
         */
        static void dispose();

        /**
         * @brief Logs a message with the specified log level.
         * @param level The log level.
         * @param message The message to log.
         */
        static void log(SeverityFlagsEnum const level, Char const *const value);

        /**
         * @brief Logs an error code with the specified log level.
         * @param level The log level.
         */
        static void log(SeverityFlagsEnum const level, ErrorCodeEnum const errorCode);

        /**
         * @brief Logs an error code with a message and the specified log level.
         * @param level The log level.
         * @param errorCode The error code.
         * @param value The extra value to log.
         */
        static void log(SeverityFlagsEnum const level, ErrorCodeEnum const errorCode, Char const *const value);

        /**
         * @brief Logs an error code with a message and the specified log level.
         * @param level The log level.
         * @param errorCode The error code.
         * @param value The extra value to log.
         */
        static void log(SeverityFlagsEnum const level, ErrorCodeEnum const errorCode, WInt const value);

        /**
         * @brief Logs an error code with a message and the specified log level.
         * @param level The log level.
         * @param errorCode The error code.
         * @param value The extra value to log.
         */
        static void log(SeverityFlagsEnum const level, ErrorCodeEnum const errorCode, WUInt const value);

        /**
         * @brief Logs an error code with a message and the specified log level.
         * @param level The log level.
         * @param errorCode The error code.
         * @param value The extra value to log.
         */
        static void log(SeverityFlagsEnum const level, ErrorCodeEnum const errorCode, WFloat const value);

        /**
         * @brief Logs the current stack trace to the debug output.
         * @note This function is only available in debug builds when SeverityFlags::StackTrace is enabled.
         */
        static void log_stack_trace();

        /**
         * @brief Sets the foreground color for terminal output.
         * @param color The color to set.
         */
        static void flush();

#pragma endregion

#pragma region Variables

    private:
        static SeverityFlagsEnum s_flags;
        static Logger *sp_logger;
        static Bool s_initialized;

#pragma endregion
    };
}

#ifdef MINTY_DEBUG
// if debugging and using Visual Studio, insert debug break
#ifdef _MSC_VER
#define MINTY_BREAK()      \
    do                     \
    {                      \
        MINTY_LOG_FLUSH(); \
        __debugbreak();    \
    } while (0)
#else
#error "Debug break not implemented for this compiler."
#endif // _MSC_VER
#else
#define MINTY_BREAK()
#endif // MINTY_DEBUG

#ifdef MINTY_DEBUG
/**
 * @brief Macro to flush the debug output.
 * @note Only active in debug builds.
 */
#define MINTY_LOG_FLUSH() Minty::Debug::flush()
#else
/**
 * @brief Macro to flush the debug output.
 * @note Only active in debug builds.
 * @warning This macro does nothing in release builds.
 */
#define MINTY_LOG_FLUSH()
#endif

/**
 * @brief Macro to log a message with a specified log level.
 * @note Always active.
 */
#define MINTY_LOG(level, msg) Minty::Debug::log((level), (msg))

/**
 * @brief Macro to log an error code with a specified log level.
 * @note Always active.
 * @param level The log level.
 * @param errorCode The error code to log.
 */
#define MINTY_LOG_CODE(level, errorCode)         \
    do                                           \
    {                                            \
        Minty::set_error((errorCode));           \
        Minty::Debug::log((level), (errorCode)); \
        MINTY_LOG_FLUSH();                       \
        MINTY_BREAK();                           \
    } while (0)

/**
 * @brief Macro to log an error code with a message and a specified log level.
 * @note Always active.
 * @param level The log level.
 * @param errorCode The error code to log.
 * @param a The extra value to log.
 */
#define MINTY_LOG_CODE_A(level, errorCode, a)         \
    do                                                \
    {                                                 \
        Minty::set_error((errorCode));                \
        Minty::Debug::log((level), (errorCode), (a)); \
        MINTY_LOG_FLUSH();                            \
        MINTY_BREAK();                                \
    } while (0)

#ifdef MINTY_DEBUG
/**
 * @brief Macro to log a debug message.
 * @note Only active in debug builds.
 */
#define MINTY_LOG_DEBUG(msg) MINTY_LOG(Minty::SeverityFlagsEnum::Debug, (msg))
#else
#define MINTY_LOG_DEBUG(msg)
#endif

#ifdef MINTY_DEBUG
/**
 * @brief Macro to log an info message.
 * @note Only active in debug builds.
 */
#define MINTY_LOG_INFO(msg) MINTY_LOG(Minty::SeverityFlagsEnum::Info, (msg))
#else
#define MINTY_LOG_INFO(msg)
#endif

/**
 * @brief Macro to log a message.
 * @note Always active.
 */
#define MINTY_LOG_MESSAGE(msg) MINTY_LOG(Minty::SeverityFlagsEnum::Message, (msg))

#ifdef MINTY_DEBUG
/**
 * @brief Macro to log a warning message.
 * @note Always active.
 */
#define MINTY_LOG_WARNING(msg)                      \
    do                                              \
    {                                               \
        MINTY_LOG(Minty::SeverityFlagsEnum::Warning, msg); \
        MINTY_LOG_FLUSH();                          \
    } while (0)
#else
/**
 * @brief Macro to log a warning message.
 * @note Always active.
 */
#define MINTY_LOG_WARNING(msg) MINTY_LOG(Minty::SeverityFlags::Warning, msg)
#endif

#ifdef MINTY_DEBUG
/**
 * @brief Macro to log an error message.
 * @note Always active.
 */
#define MINTY_LOG_ERROR(msg)                      \
    do                                            \
    {                                             \
        MINTY_LOG(Minty::SeverityFlagsEnum::Error, msg); \
        MINTY_LOG_FLUSH();                        \
    } while (0)
#else
/**
 * @brief Macro to log an error message.
 * @note Always active.
 */
#define MINTY_LOG_ERROR(msg) MINTY_LOG(Minty::SeverityFlags::Error, msg)
#endif

/**
 * @brief Macro to log a fatal message.
 * @note Always active.
 */
#define MINTY_LOG_CRITICAL(msg)                      \
    do                                               \
    {                                                \
        MINTY_LOG(Minty::SeverityFlagsEnum::Critical, msg); \
        MINTY_LOG_FLUSH();                           \
        MINTY_BREAK();                               \
    } while (0)

#ifdef MINTY_DEBUG
/**
 * @brief Macro to abort execution with a message.
 * @note Always active.
 */
#define MINTY_ABORT(errorCode)                                    \
    do                                                            \
    {                                                             \
        MINTY_LOG_CODE(Minty::SeverityFlagsEnum::Critical, (errorCode)); \
        MINTY_LOG_FLUSH();                                        \
        MINTY_BREAK();                                            \
        std::abort();                                             \
    } while (0)
/**
 * @brief Macro to abort execution with a formatted message.
 * @note Always active.
 */
#define MINTY_ABORT_A(errorCode, a)                                      \
    do                                                                   \
    {                                                                    \
        MINTY_LOG_CODE_A(Minty::SeverityFlagsEnum::Critical, (errorCode), (a)); \
        MINTY_LOG_FLUSH();                                               \
        MINTY_BREAK();                                                   \
        std::abort();                                                    \
    } while (0)
#else
/**
 * @brief Macro to abort execution with a message.
 * @note Always active.
 */
#define MINTY_ABORT(errorCode)                                    \
    do                                                            \
    {                                                             \
        MINTY_LOG_CODE(Minty::SeverityFlags::Critical, (errorCode)); \
        std::abort();                                             \
    } while (0)
/**
 * @brief Macro to abort execution with a formatted message.
 * @note Always active.
 */
#define MINTY_ABORT_A(errorCode, a)                                      \
    do                                                                   \
    {                                                                    \
        MINTY_LOG_CODE_A(Minty::SeverityFlags::Critical, (errorCode), (a)); \
        std::abort();                                                    \
    } while (0)
#endif // MINTY_DEBUG

#ifdef MINTY_DEBUG
/**
 * @brief Macro to assert a condition.
 * @note Only active in debug builds.
 */
#define MINTY_ASSERT(condition, errorCode) \
    do                                     \
    {                                      \
        if (!(condition))                  \
        {                                  \
            MINTY_ABORT(errorCode);        \
        }                                  \
    } while (0)
/**
 * @brief Macro to assert a condition with a formatted message.
 * @note Only active in debug builds.
 */
#define MINTY_ASSERT_A(condition, errorCode, a) \
    do                                          \
    {                                           \
        if (!(condition))                       \
        {                                       \
            MINTY_ABORT_A(errorCode, (a));      \
        }                                       \
    } while (0)
#else
#define MINTY_ASSERT(condition, errorCode)
#define MINTY_ASSERT_A(condition, errorCode, a)
#endif

/**
 * @brief Macro to indicate a not implemented code path.
 * @note Always active.
 */
#define MINTY_NOT_IMPLEMENTED() MINTY_ABORT(Minty::ErrorCodeEnum::NotImplemented)

/**
 * @brief Macro to indicate a code path that is not supported.
 * @note Always active.
 */
#define MINTY_NOT_SUPPORTED() MINTY_ABORT(Minty::ErrorCodeEnum::NotSupported)

/**
 * @brief Macro to log a warning.
 * @note Always active.
 */
#define MINTY_WARNING(errorCode) MINTY_LOG_CODE(Minty::SeverityFlagsEnum::Warning, (errorCode))
/**
 * @brief Macro to log a formatted warning.
 * @note Always active.
 */
#define MINTY_WARNING_A(errorCode, a) MINTY_LOG_CODE_A(Minty::SeverityFlagsEnum::Warning, (errorCode), (a))

/**
 * @brief Macro to log and set an error.
 * @note Always active.
 */
#define MINTY_ERROR(errorCode) MINTY_LOG_CODE(Minty::SeverityFlagsEnum::Error, (errorCode))
/**
 * @brief Macro to log and set a formatted error.
 * @note Always active.
 */
#define MINTY_ERROR_A(errorCode, a) MINTY_LOG_CODE_A(Minty::SeverityFlagsEnum::Error, (errorCode), (a))

/**
 * @brief Macro to check a condition and log an error if it fails.
 * @note Always active.
 */
#define MINTY_CHECK(condition, errorCode) \
    do                                    \
    {                                     \
        if (!(condition))                 \
        {                                 \
            MINTY_ERROR((errorCode));     \
        }                                 \
    } while (0)

/**
 * @brief Macro to check a condition and log an error if it fails.
 * @note Always active.
 */
#define MINTY_CHECK_A(condition, errorCode, a) \
    do                                         \
    {                                          \
        if (!(condition))                      \
        {                                      \
            MINTY_ERROR_A((errorCode), (a));   \
        }                                      \
    } while (0)