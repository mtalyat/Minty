#include "Logger.h"
#include "Minty/Log/LoggerInfo.h"
#include "Minty/Core/Enum.h"
#include "Minty/Time/Time.h"
#include "Minty/Data/Vector.h"
#include <iostream>

using namespace Minty;

static constexpr Size LOG_BATCH_SIZE = 64;

Minty::Logger::Logger(LoggerInfo const &info)
    : m_enabledLevels(info.enabledLevels), m_logQueue(), m_queueMutex(), m_queueCondition(), m_isRunning(true), m_workerThread()
{
    // initialize worker thread after all members are initialized
    m_workerThread = std::thread(&Logger::worker_thread, this);
}

Minty::Logger::~Logger()
{
    m_isRunning = false;
    m_queueCondition.notify_all();

    if (m_workerThread.joinable())
    {
        m_workerThread.join();
    }
}

void Minty::Logger::log(LogLevel const level, StringView const message)
{
    if ((m_enabledLevels & level) == LogLevel::None)
    {
        // Ignore. Log level is not enabled.
        return;
    }

    // Create log entry
    String messageCopy(message);
    LogEntry entry{level, std::move(messageCopy)};

    {
        std::lock_guard<std::mutex> lock(m_queueMutex);
        m_logQueue.push(std::move(entry));
    }

    m_queueCondition.notify_one();
}

void Minty::Logger::flush()
{
    std::unique_lock<std::mutex> lock(m_queueMutex);
    m_queueCondition.wait(lock, [this]()
                          { return m_logQueue.is_empty() || !m_isRunning; });
}

void Minty::Logger::print(LogLevel const level, StringView const message)
{
    // todo: combine into one string and print all at once

    // print timestamp
    std::cout << "[" << Time::get_timestamp().get_data() << "] ";

    // print level
    switch (level)
    {
    case LogLevel::Debug:
        std::cout << "\033[30;44m DBG \033[0m"; // black & blue
        break;
    case LogLevel::Info:
        std::cout << "\033[30;47m INF \033[0m"; // black and white
        break;
    case LogLevel::Message:
        std::cout << "\033[30;107m MSG \033[0m"; // black and bright white
        break;
    case LogLevel::Warning:
        std::cout << "\033[30;103m WRN \033[0m"; // black and yellow
        break;
    case LogLevel::Error:
        std::cout << "\033[30;101m ERR \033[0m"; // black and red
        break;
    case LogLevel::Critical:
        std::cout << "\033[30;41m CRT \033[0m"; // black and bright red
        break;
    default: // should not happen
        break;
    }

    // print message
    std::cout << " " << message.get_data() << std::endl;
}

void Minty::Logger::worker_thread()
{
    LogEntry logBatch[LOG_BATCH_SIZE];
    Size batchSize = 0;

    while (m_isRunning || !m_logQueue.is_empty())
    {
        {
            std::unique_lock<std::mutex> lock(m_queueMutex);
            m_queueCondition.wait(lock, [this]()
                                  { return !m_isRunning || !m_logQueue.is_empty(); });

            // extract all log entries in a batch
            while (!m_logQueue.is_empty() && batchSize < LOG_BATCH_SIZE)
            {
                logBatch[batchSize++] = std::move(m_logQueue.pop());
            }

            // notify any waiting threads that the queue is empty
            m_queueCondition.notify_all();
        }

        // process log entries outside of the lock
        for (Size i = 0; i < batchSize; ++i)
        {
            process_log_entry(logBatch[i]);
        }
        batchSize = 0;
    }
}

void Minty::Logger::process_log_entry(LogEntry const &entry)
{
    print(entry.level, entry.message.get_view());
}
