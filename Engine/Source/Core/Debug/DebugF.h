#pragma once

/**
 * @file DebugF.h
 * @brief Header file for debug utilities and formatted logging.
 * @author Mitchell Talyat
 */

#include "Debug.h"
#include "Core/Tool/Format.h"

/**
 * @brief Macro to log a formatted message with a specified log level.
 * @note Always active.
 */
#define MINTY_LOG_F(level, fmt, ...) MINTY_LOG(level, F(fmt, ##__VA_ARGS__).get_data())

/**
 * @brief Macro to log a formatted debug message.
 * @note Only active in debug builds.
 */
#define MINTY_LOG_DEBUG_F(fmt, ...) MINTY_LOG_DEBUG(F(fmt, ##__VA_ARGS__).get_data())

/**
 * @brief Macro to log a formatted info message.
 * @note Only active in debug builds.
 */
#define MINTY_LOG_INFO_F(fmt, ...) MINTY_LOG_INFO(F(fmt, ##__VA_ARGS__).get_data())

/**
 * @brief Macro to log a formatted message.
 * @note Always active.
 */
#define MINTY_LOG_MESSAGE_F(fmt, ...) MINTY_LOG_MESSAGE(F(fmt, ##__VA_ARGS__).get_data())

/**
 * @brief Macro to log a formatted warning message.
 * @note Always active.
 */
#define MINTY_LOG_WARNING_F(fmt, ...) MINTY_LOG_WARNING(F(fmt, ##__VA_ARGS__).get_data())

/**
 * @brief Macro to log a formatted error message.
 * @note Always active.
 */
#define MINTY_LOG_ERROR_F(fmt, ...) MINTY_LOG_ERROR(F(fmt, ##__VA_ARGS__).get_data())

/**
 * @brief Macro to log a formatted fatal message.
 * @note Always active.
 */
#define MINTY_LOG_CRITICAL_F(fmt, ...) MINTY_LOG_CRITICAL(F(fmt, ##__VA_ARGS__).get_data())

/**
 * @brief Macro to abort execution with a formatted message.
 * @note Always active.
 */
#define MINTY_ABORT_F(errorCode, fmt, ...) MINTY_ABORT_A(errorCode, F(fmt, ##__VA_ARGS__).get_data())
#define MINTY_ABORT_B(errorCode, ...) MINTY_ABORT_A(errorCode, F("", ##__VA_ARGS__).get_data())

/**
 * @brief Macro to assert a condition with a formatted message.
 * @note Only active in debug builds.
 */
#define MINTY_ASSERT_F(condition, errorCode, fmt, ...) MINTY_ASSERT_A(condition, errorCode, F(fmt, ##__VA_ARGS__).get_data())
#define MINTY_ASSERT_B(condition, errorCode, ...) MINTY_ASSERT_A(condition, errorCode, F("", ##__VA_ARGS__).get_data())

/**
 * @brief Macro to log a formatted warning.
 * @note Always active.
 */
#define MINTY_WARNING_F(errorCode, fmt, ...) MINTY_WARNING_A(errorCode, F(fmt, ##__VA_ARGS__).get_data())
#define MINTY_WARNING_B(errorCode, ...) MINTY_WARNING_A(errorCode, F("", ##__VA_ARGS__).get_data())

/**
 * @brief Macro to log and set a formatted error.
 * @note Always active.
 */
#define MINTY_ERROR_F(errorCode, fmt, ...) MINTY_ERROR_A(errorCode, F(fmt, ##__VA_ARGS__).get_data())
#define MINTY_ERROR_B(errorCode, ...) MINTY_ERROR_A(errorCode, F("", ##__VA_ARGS__).get_data())

/**
 * @brief Macro to check a condition and log an error if it fails.
 * @note Always active.
 */
#define MINTY_CHECK_F(condition, errorCode, fmt, ...) MINTY_CHECK_A(condition, errorCode, F(fmt, ##__VA_ARGS__).get_data())
#define MINTY_CHECK_B(condition, errorCode, ...) MINTY_CHECK_A(condition, errorCode, F("", ##__VA_ARGS__).get_data())
