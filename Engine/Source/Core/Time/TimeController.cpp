#include "pch.h"
#include "Time.h"
#include "TimeController.h"
#include "TimeControllerInfo.h"
#include "Core/Debug/DebugF.h"
#include "Core/Constant/Convert.h"

using namespace Minty;

TimeController* TimeController::sp_singleton = nullptr;

Minty::TimeController::TimeController(TimeControllerInfo const &info)
    : m_running(false)
    , m_time(0)
    , m_unscaledTime(0.0f)
    , m_scaledTime(0.0f)
    , m_unscaledDelta(0.0f)
    , m_scaledDelta(0.0f)
    , m_timeScale(1.0f)
    , m_fixedTimeStep(info.fixedTimestep)
    , m_fixedTimeAccumulator(0.0f)
    , m_maxAllowedTimeStep(info.maxAllowedTimestep)
    , m_maxFixedUpdatesPerFrame(info.maxFixedUpdatesPerFrame)
{}

void Minty::TimeController::start()
{
    // MINTY_ASSERT(m_running == false, ErrorCodeEnum::Object_AlreadyRunning);
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
    // MINTY_ASSERT(m_running == true, ErrorCodeEnum::Object_NotRunning);
    m_running = false;
}

Int Minty::TimeController::update()
{
    // MINTY_ASSERT(m_running == true, ErrorCodeEnum::Object_NotRunning);

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
    m_fixedTimeAccumulator += m_scaledDelta;

    // Calculate number of fixed updates to perform
    Int fixedUpdates = 0;
    while (m_fixedTimeAccumulator >= m_fixedTimeStep && fixedUpdates < m_maxFixedUpdatesPerFrame)
    {
        m_fixedTimeAccumulator -= m_fixedTimeStep;
        fixedUpdates++;
    }

    if (fixedUpdates == m_maxFixedUpdatesPerFrame)
    {
        // Prevent spiral of death by resetting accumulator
        MINTY_LOG_WARNING(F("Maximum fixed updates per frame reached ({}). Remaining time discarded ({}).", m_maxFixedUpdatesPerFrame, m_fixedTimeAccumulator).get_data());
        m_fixedTimeAccumulator = 0.0f;
    }

    return fixedUpdates;
}

Unique<TimeController> Minty::TimeController::create(TimeControllerInfo const &info)
{
    return Unique<TimeController>::create(info);
}

Unique<TimeController> Minty::TimeController::create()
{
    TimeControllerInfo info{};
    return create(info);
}

TimeController& Minty::TimeController::get_instance()
{
    MINTY_ASSERT(sp_singleton != nullptr, ErrorCodeEnum::Singleton_DoesNotExist);
    return *sp_singleton;
}
