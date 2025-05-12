#include "pch.h"
#include "RenderSystem.h"
#include "Minty/Entity/EntityManager.h"
#include "Minty/Scene/Scene.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

void Minty::RenderSystem::serialize(Writer& writer) const
{
	EntityManager& entityManager = m_scene->get_entity_manager();
	UUID id = entityManager.get_id(m_mainCameraEntity);
	writer.write("MainCamera", id);
}

Bool Minty::RenderSystem::deserialize(Reader& reader)
{
	UUID id;
	if (reader.read("MainCamera", id))
	{
		EntityManager& entityManager = m_scene->get_entity_manager();
		m_mainCameraEntity = entityManager.get_entity(id);
	}
	else
	{
		m_mainCameraEntity = INVALID_ENTITY;
	}

	return true;
}

void Minty::RenderSystem::on_load()
{
}

void Minty::RenderSystem::on_unload()
{
}

void Minty::RenderSystem::on_update(Time const& time)
{
}

void Minty::RenderSystem::on_finalize()
{
}

void Minty::RenderSystem::on_render()
{
}
