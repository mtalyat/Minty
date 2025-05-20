#include "pch.h"
#include "Manager.h"
#include "Minty/Debug/Debug.h"

Minty::Manager::~Manager()
{
	MINTY_ASSERT_ERROR(!m_initialized, "Manager was destroyed before it was disposed.");
}

/// <summary>
/// Called when the Manager is created.
/// </summary>
void Minty::Manager::initialize()
{
	MINTY_ASSERT(!m_initialized, "Manager was already initialized.");
	m_initialized = true;
}

/// <summary>
/// Called when the Manager is destroyed.
/// </summary>
void Minty::Manager::dispose()
{
	MINTY_ASSERT(m_initialized, "Manager was not initialized.");
	m_initialized = false;
}
