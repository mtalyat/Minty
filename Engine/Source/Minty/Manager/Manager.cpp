#include "pch.h"
#include "Manager.h"
#include "Minty/Debug/Assert.h"

Minty::Manager::~Manager()
{
	MINTY_ASSERT(!m_initialized, ErrorCode::Object_NeverDisposed);
}

/// <summary>
/// Called when the Manager is created.
/// </summary>
void Minty::Manager::initialize()
{
	MINTY_ASSERT(!m_initialized, ErrorCode::Object_AlreadyInitialized);
	m_initialized = true;
}

/// <summary>
/// Called when the Manager is destroyed.
/// </summary>
void Minty::Manager::dispose()
{
	MINTY_ASSERT(m_initialized, ErrorCode::Object_NotInitialized);
	m_initialized = false;
}
