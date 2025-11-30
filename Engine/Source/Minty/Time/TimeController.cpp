#include "pch.h"
#include "TimeController.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Core/Constant.h"
#include "Minty/Time/TimeControllerInfo.h"
#include "Minty/Time/Time.h"
#include "Minty/Application/Application.h"

using namespace Minty;

Minty::TimeController::TimeController(TimeControllerInfo const &info)
    : m_running(false)
    , m_time(0)
    , m_unscaledTime(0.0f)
    , m_scaledTime(0.0f)
    , m_unscaledDelta(0.0f)
    , m_scaledDelta(0.0f)
    , m_timeScale(1.0f)
    , m_fixedTimeStep(info.fixedTimeStep)
    , m_fixedTimeAccumulator(0.0f)
    , m_maxAllowedTimeStep(info.maxAllowedTimeStep)
    , m_maxFixedUpdatesPerFrame(info.maxFixedUpdatesPerFrame)
{}

void Minty::TimeController::start()
{
    // MINTY_ASSERT(m_running == false, ErrorCode::Object_AlreadyRunning);
    m_running = true;

    m_time = Time::get_time();
    m_unscaledTime = 0.0f;
    m_scaledTime = 0.0f;
    m_unscaledDelta = 0.0f;
    m_scaledDelta = 0.0f;
    m_fixedTimeAccumulator = 0.0f;
}

void Minty::TimeController::stop()
{
    // MINTY_ASSERT(m_running == true, ErrorCode::Object_NotRunning);
    m_running = false;
}

Int Minty::TimeController::update()
{
    // MINTY_ASSERT(m_running == true, ErrorCode::Object_NotRunning);

    TimePoint const currentTime = Time::get_time();
    Float deltaTime = static_cast<Float>(currentTime - m_time) / static_cast<Float>(ONE_SECOND); // Convert nanoseconds to seconds
    m_time = currentTime;

    // Clamp delta time to max allowed time step
    if (deltaTime > m_maxAllowedTimeStep)
    {
        deltaTime = m_maxAllowedTimeStep;
    }

    m_unscaledDelta = deltaTime;
    m_scaledDelta = deltaTime * m_timeScale;

    m_unscaledTime += m_unscaledDelta;
    m_scaledTime += m_scaledDelta;

    // Update fixed time accumulator
    m_fixedTimeAccumulator += m_unscaledDelta;

    // Calculate number of fixed updates to perform
    Int fixedUpdates = 0;
    while (m_fixedTimeAccumulator >= m_fixedTimeStep && fixedUpdates < m_maxFixedUpdatesPerFrame)
    {
        m_fixedTimeAccumulator -= m_fixedTimeStep;
        fixedUpdates++;
    }

    return fixedUpdates;
}

Unique<TimeController> Minty::TimeController::create(TimeControllerInfo const &info)
{
    return Unique<TimeController>::create(info);
}

TimeController &Minty::TimeController::get_singleton()
{
    return Application::get_singleton().get_time_manager();
}
