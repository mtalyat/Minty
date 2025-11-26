#include "pch.h"
#include "System.h"
#include "Minty/Scene/Scene.h"

using namespace Minty;

Ref<Scene> const &Minty::System::get_scene() const
{
	MINTY_ASSERT(m_scene != nullptr, ErrorCode::Object_InvalidState);
	return m_scene;
}

EntityManager &Minty::System::get_entity_manager() const
{
	MINTY_ASSERT(m_scene != nullptr, ErrorCode::Object_InvalidState);
	return m_scene->get_entity_manager();
}

SystemManager &Minty::System::get_system_manager() const
{
	MINTY_ASSERT(m_scene != nullptr, ErrorCode::Object_InvalidState);
	return m_scene->get_system_manager();
}
