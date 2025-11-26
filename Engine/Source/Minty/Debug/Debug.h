#pragma once
#include "Minty/Core/Macro.h"
#include "Minty/Core/Types.h"
#include "Minty/Debug/DebugFlags.h"
#include "Minty/Debug/Error.h"
#include "Minty/Log/LogLevel.h"
#include <iostream>

namespace Minty
{
	class String;

	/// <summary>
	/// A static class for writing output.
	/// </summary>
	class Debug
	{
#pragma region Classes

	public:
		/// <summary>
		/// A color that can be used to write in the terminal.
		/// </summary>
		enum class Color
		{
			Black = 30,
			Red = 31,
			Green = 32,
			Yellow = 33,
			Blue = 34,
			Magenta = 35,
			Cyan = 36,
			White = 37,
			BrightBlack = 90,
			Gray = BrightBlack,
			BrightRed = 91,
			BrightGreen = 92,
			BrightYellow = 93,
			BrightBlue = 94,
			BrightMagenta = 95,
			BrightCyan = 96,
			BrightWhite = 97
		};

#pragma endregion

#pragma region Variables

	private:
		static DebugFlags s_flags;

#pragma endregion

#pragma region Constructors

	private:
		Debug() = delete;
		~Debug() = delete;

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Sets the debug flags.
		/// </summary>
		/// <param name="flags">The DebugFlags.</param>
		static void set_flags(DebugFlags const flags);

		/// <summary>
		/// Gets the debug flags.
		/// </summary>
		/// <returns>The DebugFlags.</returns>
		inline static DebugFlags get_flags() { return s_flags; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Logs a message with the specified log level.
		 * @param level The log level.
		 * @param message The message to log.
		 */
		static void log(LogLevel const level, String const& message);

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
#define MINTY_LOG(level, msg, ...) \
    do { \
        Minty::Debug::log(level, F(msg, ##__VA_ARGS__)); \
    } while(0)

/**
 * @brief Macro to log a message with a specified log level. Includes file, function and line number.
 * @note Always active.
 */
#define MINTY_LOG_TRACE(level, msg, ...) \
    do { \
        Minty::Debug::log(level, F("{{ {}, {}(), {} }} {}", __FILE__, __func__, __LINE__, F(msg, ##__VA_ARGS__))); \
    } while(0)


/**
 * @brief Macro to log a debug message.
 * @note Only active in debug builds.
 */
#ifdef MINTY_DEBUG
    #define MINTY_LOG_DEBUG(msg, ...) \
        do { \
            MINTY_LOG(LogLevel::Debug, msg, ##__VA_ARGS__); \
        } while(0)
#else
    #define MINTY_LOG_DEBUG(msg, ...)
#endif

/**
 * @brief Macro to log an info message.
 * @note Only active in debug builds.
 */
#ifdef MINTY_DEBUG
    #define MINTY_LOG_INFO(msg, ...) \
        do { \
            MINTY_LOG(LogLevel::Info, msg, ##__VA_ARGS__); \
        } while(0)
#else
    #define MINTY_LOG_INFO(msg, ...)
#endif

/**
 * @brief Macro to log a message.
 * @note Always active.
 */
#define MINTY_LOG_MESSAGE(msg, ...) \
    do { \
        MINTY_LOG(LogLevel::Message, msg, ##__VA_ARGS__); \
    } while(0)

/**
 * @brief Macro to log a warning message.
 * @note Only active in debug builds.
 */
#ifdef MINTY_DEBUG
    #define MINTY_LOG_WARNING(msg, ...) \
        do { \
            MINTY_LOG(LogLevel::Warning, msg, ##__VA_ARGS__); \
        } while(0)
#else
    #define MINTY_LOG_WARNING(msg, ...)
#endif

/**
 * @brief Macro to log an error message.
 * @note Always active.
 */
#define MINTY_LOG_ERROR(msg, ...) \
    do { \
        MINTY_LOG_TRACE(LogLevel::Error, msg, ##__VA_ARGS__); \
    } while(0)

/**
 * @brief Macro to log a fatal message.
 * @note Always active.
 */
#define MINTY_LOG_CRITICAL(msg, ...) \
    do { \
        MINTY_LOG_TRACE(LogLevel::Critical, msg, ##__VA_ARGS__); \
		Minty::Debug::flush(); \
        MINTY_BREAK(); \
    } while(0)

/**
 * @brief Macro to assert a condition.
 * @note Only active in debug builds.
 */
#ifdef MINTY_DEBUG
    #define MINTY_ASSERT(condition, errorCode, ...) \
        do { \
            if (!(condition)) { \
                Minty::set_error(errorCode); \
                MINTY_LOG_CRITICAL(Minty::get_error_message(errorCode), ##__VA_ARGS__); \
            } \
        } while(0)
#else
    #define MINTY_ASSERT(condition, errorCode, ...)
#endif

/**
 * @brief Macro to indicate a not implemented code path.
 * @note Only active in debug builds.
 */
#ifdef MINTY_DEBUG
        #define MINTY_NOT_IMPLEMENTED(...) \
            do { \
                Minty::set_error(Minty::ErrorCode::NotImplemented); \
                MINTY_LOG_CRITICAL(Minty::get_error_message(Minty::ErrorCode::NotImplemented), ##__VA_ARGS__); \
                MINTY_BREAK(); \
            } while(0)
#else
        #define MINTY_NOT_IMPLEMENTED(...)
#endif

/**
 * @brief Macro to abort execution with a message.
 * @note Only active in debug builds.
 */
#ifdef MINTY_DEBUG
    #define MINTY_ABORT(errorCode, ...) \
        do { \
            Minty::set_error(errorCode); \
            MINTY_LOG_CRITICAL(Minty::get_error_message(errorCode), ##__VA_ARGS__); \
            std::abort(); \
        } while(0)
#else
    #define MINTY_ABORT(errorCode, ...) \
		do { \
			std::abort(); \
		} while(0)
#endif