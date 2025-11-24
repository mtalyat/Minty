#include "Logger.h"
#include "Minty/Log/LoggerInfo.h"
#include "Minty/Core/Enum.h"
#include "Minty/Time/Time.h"
#include <iostream>

using namespace Minty;

Minty::Logger::Logger(LoggerInfo const &info)
    : m_enabledLevels(info.enabledLevels), m_logQueue(), m_queueMutex(), m_queueCondition(), m_isRunning(true), m_workerThread(&Logger::WorkerThread, this)
{
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

void Minty::Logger::Log(LogLevel const level, String const &message)
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

void Minty::Logger::Flush()
{
    std::unique_lock<std::mutex> lock(m_queueMutex);
    m_queueCondition.wait(lock, [this]() { return m_logQueue.is_empty() || !m_isRunning; });
}

void Minty::Logger::WorkerThread()
{
    while(m_isRunning || !m_logQueue.is_empty())
    {
        std::unique_lock<std::mutex> lock(m_queueMutex);

        m_queueCondition.wait(lock, [this]() { return !m_isRunning || !m_logQueue.is_empty(); });
        while(!m_logQueue.is_empty())
        {
            LogEntry entry = std::move(m_logQueue.pop());
            lock.unlock();

            ProcessLogEntry(entry);

            lock.lock();
        }

        m_queueCondition.notify_all();
    }
}

void Minty::Logger::ProcessLogEntry(LogEntry const &entry)
{
    // todo: combine into one string and print all at once

    // print timestamp
    std::cout << "[" << Time::get_timestamp().get_data() << "] ";

    // print level
    switch(entry.level)
    {
        case LogLevel::Debug:
            std::cout << "\033[30;44m DBG \033[0m";  // black & blue
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
    std::cout << " " << entry.message.get_data() << std::endl;
}
