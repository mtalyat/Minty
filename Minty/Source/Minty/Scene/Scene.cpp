#include "pch.h"
#include "Scene.h"
#include "Minty/Asset/AssetManager.h"
#include "Minty/Component/ColliderComponent.h"
#include "Minty/Component/DestroyComponent.h"
#include "Minty/Component/RigidBodyComponent.h"
#include "Minty/Component/SimulateComponent.h"
#include "Minty/Component/TransformComponent.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

Minty::Scene::Scene(SceneBuilder const& builder)
	: Asset(builder.id)
	, m_name(builder.name)
	, m_entityManager(nullptr)
	, m_systemManager(nullptr)
	, m_registeredAssets()
	, m_assets()
	, m_loadedAssets()
{
	// create the entity manager
	EntityManagerBuilder entityManagerBuilder{};
	m_entityManager = EntityManager::create(this, entityManagerBuilder);

	// create the system manager
	SystemManagerBuilder systemManagerBuilder{};
	systemManagerBuilder.scene = create_ref();
	m_systemManager = SystemManager::create(this, systemManagerBuilder);
}

Minty::Scene::~Scene()
{
}

void Minty::Scene::load_assets()
{
	// load all of the assets into the Scene
	// load all of the assets into the Scene
	AssetManager& assetManager = AssetManager::get_singleton();
	Size i = 0;
	for (auto const& assetPath : m_assets)
	{
		MINTY_ASSERT(!assetPath.is_empty(), "Asset path is empty");

		// skip if already loaded
		if (m_registeredAssets.contains(assetPath))
		{
			continue;
		}

		// get the data
		AssetData assetData{};
		assetData.index = i;

		// load the asset
		Ref<Asset> asset = assetManager.load_asset(assetPath);
		if (asset == nullptr)
		{
			MINTY_ERROR(F("Failed to load asset: {}", assetPath));
			continue;
		}
		else
		{
			assetData.id = asset->get_id();
		}

		// add the path to registered assets
		m_registeredAssets.add(assetPath, std::move(assetData));

		i++;
	}
}

void Minty::Scene::unload_assets()
{
	// unload all of the assets from the Scene
	AssetManager& assetManager = AssetManager::get_singleton();

	// unload backwards in case of dependencies
	for (auto it = m_assets.rbegin(); it != m_assets.rend(); ++it)
	{
		Path const& assetPath = *it;

		// find the asset in the registered assets
		auto registeredIt = m_registeredAssets.find(assetPath);
		if (registeredIt == m_registeredAssets.end())
		{
			// asset not registered, skip
			continue;
		}

		// get the data
		AssetData& assetData = m_registeredAssets.at(assetPath);

		// unload the asset
		if (assetData.id != INVALID_ID)
		{
			assetManager.unload(assetData.id);
		}
	}

	// clear the registered assets
	m_registeredAssets.clear();
}

void Minty::Scene::on_load()
{
	m_systemManager->initialize();
	m_entityManager->initialize();
	
	load_assets();
}

void Minty::Scene::on_unload()
{
	unload_assets();

	m_systemManager->dispose();
	m_entityManager->dispose();
}

void Minty::Scene::on_update(Time const& time)
{
	m_systemManager->update(time);
	m_entityManager->update(time);
}

void Minty::Scene::on_finalize()
{
	m_systemManager->finalize();
	m_entityManager->finalize();
}

void Minty::Scene::on_render()
{
	m_systemManager->render();
}

void Minty::Scene::on_event(Event& event)
{
	// pass event on to the systems
	m_systemManager->handle_event(event);
}

void Minty::Scene::serialize(Writer& writer) const
{
	MINTY_ABORT("Not implemented.");
}

Bool Minty::Scene::deserialize(Reader& reader)
{
	// unload assets before loading new ones
	unload_assets();

	// read assets
	reader.read("Assets", m_assets);

	// load the assets read
	load_assets();

	// read the systems
	if (reader.indent("Systems"))
	{
		m_systemManager->deserialize(reader);
		reader.outdent();
	}

	// read the entities
	if (reader.indent("Entities"))
	{
		m_entityManager->deserialize(reader);
		reader.outdent();
	}

	return true;
}

Owner<Scene> Minty::Scene::create(SceneBuilder const& builder)
{
	return Owner<Scene>(builder);
}
