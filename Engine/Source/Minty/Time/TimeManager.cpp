#include "pch.h"
#include "TimeManager.h"
#include "Minty/Time/TimeManagerInfo.h"

using namespace Minty;

Minty::TimeManager::TimeManager(TimeManagerInfo const& info)
	: m_time(0.0f)
	, m_rawTime(0.0f)
	, m_elapsed(0.0f)
	, m_rawElapsed(0.0f)
	, m_timeScale(1.0f)
	, m_fixedTimeStep(info.fixedTimeStep)
	, m_fixedTimeAccumulator(0.0f)
	, m_maxAllowedTimeStep(info.maxAllowedTimeStep)
	, m_maxFixedUpdatesPerFrame(info.maxFixedUpdatesPerFrame)
{}

Int Minty::TimeManager::update(Float const deltaTime)
{
	// update raw time and elapsed time
	m_rawTime += deltaTime;
	m_rawElapsed = deltaTime;

	// apply time scale
	Float scaledDeltaTime = deltaTime * m_timeScale;

	// clamp to max allowed time step
	if (scaledDeltaTime > m_maxAllowedTimeStep)
	{
		scaledDeltaTime = m_maxAllowedTimeStep;
	}

	// update total time and elapsed time
	m_time += scaledDeltaTime;
	m_elapsed = scaledDeltaTime;

	// accumulate fixed time
	m_fixedTimeAccumulator += scaledDeltaTime;

	// determine number of fixed updates to perform
	Int fixedUpdates = 0;
	while (m_fixedTimeAccumulator >= m_fixedTimeStep && fixedUpdates < m_maxFixedUpdatesPerFrame)
	{
		m_fixedTimeAccumulator -= m_fixedTimeStep;
		fixedUpdates++;
	}

	return fixedUpdates;
}
