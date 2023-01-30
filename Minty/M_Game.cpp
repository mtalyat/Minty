#include "pch.h"
#include "M_Game.h"

#include "M_Engine.h"
#include "M_SceneManager.h"
#include "M_Scene.h"

namespace minty
{
	Game::Game(std::string const& name, Engine* const engine)
		: m_name(name)
		, mp_engine(engine)
		, mp_registry(new entt::registry())
		, mp_sceneManager(new SceneManager())
	{}

	Game::~Game()
	{
		delete mp_registry;
		delete mp_sceneManager;
	}
}
