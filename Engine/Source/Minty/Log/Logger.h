#ifndef MINTY_LOG_LOGGER_H
#define MINTY_LOG_LOGGER_H

#include "Minty/Data/String.h"
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

#pragma region Methods

    public:
        /**
         * @brief Log a message with the specified log level.
         * @param level The log level.
         * @param message The message to log.
         */
        void Log(LogLevel const level, String const& message);

        /**
         * @brief Flush the log queue, ensuring all log entries are processed.
         */
        void Flush();

    private:
        void WorkerThread();
        void ProcessLogEntry(LogEntry const& entry);

#pragma endregion

#pragma region Variables

    private:
        LogLevel m_enabledLevels;
        Queue<LogEntry> m_logQueue;
        std::mutex m_queueMutex;
        std::condition_variable m_queueCondition;
        std::atomic<bool> m_isRunning;
        std::thread m_workerThread;

#pragma endregion
    };
}

#endif // MINTY_LOG_LOGGER_H