#include "pch.h"
#include "Logger.h"
#include "LoggerInfo.h"
#include "Core/Data/Vector.h"
#include "Core/Time/Time.h"
#include <iostream>

using namespace Minty;

static constexpr Size LOG_BATCH_SIZE = 64;

Minty::Logger::Logger(LoggerInfo const &info)
    : m_enabledLevels(info.enabledLevels), m_logQueue(), m_queueMutex(), m_queueCondition(), m_flushCondition(), m_pendingEntries(0), m_isRunning(true), m_workerThread()
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

void Minty::Logger::log(SeverityFlags const level, StringView const message)
{
    if ((m_enabledLevels & level) == SeverityFlagsEnum::None)
    {
        // Ignore. Log level is not enabled.
        return;
    }

    // Create log entry
    Char* messageData = new Char[message.get_size() + 1];
    std::memcpy(messageData, message.get_data(), sizeof(Char) * message.get_size());
    messageData[message.get_size()] = '\0';
    LogEntry entry{level, messageData};

    {
        std::lock_guard<std::mutex> lock(m_queueMutex);
        m_logQueue.push(std::move(entry));
        m_pendingEntries++;
    }

    m_queueCondition.notify_one();
}

void Minty::Logger::flush()
{
    std::unique_lock<std::mutex> lock(m_queueMutex);
    m_flushCondition.wait(lock, [this]()
                          { return m_pendingEntries == 0 || !m_isRunning; });
}

void Minty::Logger::print(SeverityFlags const level, StringView const message)
{
    // todo: combine into one string and print all at once

    // print timestamp
    Char buffer[64] = {0};
    Time::format(Time::get_system_time(), buffer, sizeof(buffer));
    std::cout << "[" << buffer << "] ";

    if (level.has_flag(SeverityFlagsEnum::Critical))
    {
        std::cout << "\033[30;41m CRT \033[0m"; // black and bright red
    }
    else if (level.has_flag(SeverityFlagsEnum::Error))
    {
        std::cout << "\033[30;101m ERR \033[0m"; // black and red
    }
    else if (level.has_flag(SeverityFlagsEnum::Warning))
    {
        std::cout << "\033[30;103m WRN \033[0m"; // black and yellow
    }
    else if (level.has_flag(SeverityFlagsEnum::Message))
    {
        std::cout << "\033[30;107m MSG \033[0m"; // black and bright white
    }
    else if (level.has_flag(SeverityFlagsEnum::Info))
    {
        std::cout << "\033[30;47m INF \033[0m"; // black and white
    }
    else if (level.has_flag(SeverityFlagsEnum::Debug))
    {
        std::cout << "\033[30;44m DBG \033[0m"; // black & blue
    } else
    {
        std::cout << "\033[30;47m ??? \033[0m"; // black and white
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

        // decrement pending entries and notify flush
        {
            std::lock_guard<std::mutex> lock(m_queueMutex);
            m_pendingEntries -= batchSize;
            m_flushCondition.notify_all();
        }
        batchSize = 0;
    }
}

void Minty::Logger::process_log_entry(LogEntry const &entry)
{
    print(entry.level, StringView(entry.message));
    delete[] entry.message;
}
