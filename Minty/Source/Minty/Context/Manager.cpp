#include "pch.h"
#include "Manager.h"
#include "Minty/Debug/Debug.h"

inline Minty::Manager::~Manager()
{
#ifdef MINTY_DEBUG
	if (!m_initialized)
	{
		MINTY_ERROR("Manager was not initialized, but was destroyed.");
	}
#endif // MINTY_DEBUG
}

/// <summary>
/// Called when the Manager is created.
/// </summary>
inline void Minty::Manager::initialize()
{
	MINTY_ASSERT(!m_initialized, "Manager was already initialized.");
	m_initialized = true;
}

/// <summary>
/// Called when the Manager is destroyed.
/// </summary>
inline void Minty::Manager::dispose()
{
	MINTY_ASSERT(m_initialized, "Manager was not initialized.");
	m_initialized = false;
}
