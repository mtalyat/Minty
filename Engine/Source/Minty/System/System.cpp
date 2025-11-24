#include "pch.h"
#include "System.h"
#include "Minty/Scene/Scene.h"

using namespace Minty;

EntityManager& Minty::System::get_entity_manager() const
{
	MINTY_ASSERT(m_scene != nullptr, "System does not belong to a Scene.");
	return m_scene->get_entity_manager();
}

SystemManager& Minty::System::get_system_manager() const
{
	MINTY_ASSERT(m_scene != nullptr, "System does not belong to a Scene.");
	return m_scene->get_system_manager();
}
