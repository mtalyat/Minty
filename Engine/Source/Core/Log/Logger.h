#pragma once

/**
 * @file Logger.h
 * @brief Header file for the Logger class, which provides thread-safe logging functionality.
 * @author Mitchell Talyat
 */

#include "Core/Data/StringView.h"
#include "Core/Data/Queue.h"
#include "Core/Type/Severity.h"
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
            SeverityFlags level;
            Char* message;
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
         * @return The enabled Severity.
         */
        inline SeverityFlags get_enabled_levels() const { return m_enabledLevels; }

        /**
         * @brief Sets the enabled log levels.
         * @param levels The Severity to enable.
         */
        inline void set_enabled_levels(SeverityFlags const levels) { m_enabledLevels = levels; }

#pragma endregion

#pragma region Methods

    public:
        /**
         * @brief Log a message with the specified log level.
         * @param level The log level.
         * @param message The message to log.
         */
        void log(SeverityFlags const level, StringView const message);

        /**
         * @brief Flush the log queue, ensuring all log entries are processed.
         */
        void flush();

        /**
         * @brief Prints a log message directly without queuing.
         * @param level The log level.
         * @param message The message to print.
         */
        static void print(SeverityFlags const level, StringView const message);

    private:
        void worker_thread();
        void process_log_entry(LogEntry const& entry);

#pragma endregion

#pragma region Variables

    private:
        SeverityFlags m_enabledLevels;
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