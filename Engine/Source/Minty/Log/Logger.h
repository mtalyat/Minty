#ifndef MINTY_LOG_LOGGER_H
#define MINTY_LOG_LOGGER_H

#include "Minty/Data/String.h"
#include "Minty/Data/StringView.h"
#include "Minty/Log/LogLevel.h"
#include "Minty/Data/Queue.h"
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

namespace Minty
{
    struct LoggerInfo;

    /**
     * @class Logger
     * @brief A thread-safe logger that handles logging messages with different severity levels.
     */
    class Logger
    {
#pragma region Types

    private:
        struct LogEntry
        {
            LogLevel level;
            String message;
        };

#pragma endregion

#pragma region Constructors

    public:
        /**
         * @brief Constructor for Logger.
         * @param info The logger configuration information.
         */
        Logger(LoggerInfo const& info);

        ~Logger();

#pragma endregion

#pragma region Accessors

    public:
        /**
         * @brief Gets the enabled log levels.
         * @return The enabled LogLevel.
         */
        inline LogLevel get_enabled_levels() const { return m_enabledLevels; }

        /**
         * @brief Sets the enabled log levels.
         * @param levels The LogLevel to enable.
         */
        inline void set_enabled_levels(LogLevel const levels) { m_enabledLevels = levels; }

#pragma endregion

#pragma region Methods

    public:
        /**
         * @brief Log a message with the specified log level.
         * @param level The log level.
         * @param message The message to log.
         */
        void log(LogLevel const level, StringView const message);

        /**
         * @brief Flush the log queue, ensuring all log entries are processed.
         */
        void flush();

        /**
         * @brief Prints a log message directly without queuing.
         * @param level The log level.
         * @param message The message to print.
         */
        static void print(LogLevel const level, StringView const message);

    private:
        void worker_thread();
        void process_log_entry(LogEntry const& entry);

#pragma endregion

#pragma region Variables

    private:
        LogLevel m_enabledLevels;
        Queue<LogEntry> m_logQueue;
        std::mutex m_queueMutex;
        std::condition_variable m_queueCondition;
        std::condition_variable m_flushCondition;
        Size m_pendingEntries;
        std::atomic<Bool> m_isRunning;
        std::thread m_workerThread;

#pragma endregion
    };
}

#endif // MINTY_LOG_LOGGER_H