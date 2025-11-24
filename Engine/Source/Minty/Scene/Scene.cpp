#include "pch.h"
#include "Scene.h"
#include "Minty/Asset/AssetManager.h"
#include "Minty/Component/ColliderComponent.h"
#include "Minty/Component/DestroyComponent.h"
#include "Minty/Component/RigidBodyComponent.h"
#include "Minty/Component/SimulateComponent.h"
#include "Minty/Component/TransformComponent.h"
#include "Minty/Debug/Trace.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"

using namespace Minty;

Minty::Scene::Scene(SceneBuilder const& builder)
	: m_id(builder.id)
	, m_name(builder.name)
	, m_entityManager(nullptr)
	, m_systemManager(nullptr)
	, m_loadedAssets()
	, m_assets()
	, m_registeredAssets()
{
	// create the entity manager
	EntityManagerBuilder entityManagerBuilder{};
	m_entityManager = EntityManager::create(this, entityManagerBuilder);

	// create the system manager
	SystemManagerBuilder systemManagerBuilder{};
	systemManagerBuilder.scene = create_ref();
	m_systemManager = SystemManager::create(this, systemManagerBuilder);
}

Minty::Scene::Scene(Scene&& other) noexcept
	: m_id(std::move(other.m_id))
	, m_name(std::move(other.m_name))
	, m_entityManager(std::move(other.m_entityManager))
	, m_systemManager(std::move(other.m_systemManager))
	, m_loadedAssets()
	, m_assets()
	, m_registeredAssets()
{
	// the target scene now owns the registered assets from the other scene
	// in ADDITION to this Scene's assets
	for (auto const& [path, assetData] : other.m_loadedAssets)
	{
		m_loadedAssets.add(path, assetData);
	}
	other.m_loadedAssets.clear();
	for (auto const& assetPath : other.m_assets)
	{
		m_assets.add(assetPath);
	}
	other.m_assets.clear();
	for (auto const& assetId : other.m_registeredAssets)
	{
		m_registeredAssets.add(assetId);
	}
	other.m_assets.clear();
}

Minty::Scene::~Scene()
{
}

Scene& Minty::Scene::operator=(Scene&& other) noexcept
{
	if (this != &other)
	{
		m_id = std::move(other.m_id);
		m_name = std::move(other.m_name);
		m_entityManager = std::move(other.m_entityManager);
		m_systemManager = std::move(other.m_systemManager);
		// the target scene now owns the registered assets from the other scene
		// in ADDITION to this Scene's assets
		for (auto const& [path, assetData] : other.m_loadedAssets)
		{
			m_loadedAssets.add(path, assetData);
		}
		other.m_loadedAssets.clear();
		for (auto const& assetPath : other.m_assets)
		{
			m_assets.add(assetPath);
		}
		other.m_assets.clear();
		for (auto const& assetId : other.m_registeredAssets)
		{
			m_registeredAssets.add(assetId);
		}
		other.m_assets.clear();
	}

	return *this;
}

void Minty::Scene::load_assets(Vector<Path> const& newAssets)
{
	// load all of the assets into the Scene
	Set<Path> loaded;
	AssetManager& assetManager = AssetManager::get_singleton();
	Size i = 0;
	for (auto const& assetPath : newAssets)
	{
		MINTY_ASSERT(!assetPath.is_empty(), "Asset path is empty");

		// add to loaded
		loaded.add(assetPath);

		// update if already loaded
		if (m_loadedAssets.contains(assetPath))
		{
			AssetData& assetData = m_loadedAssets.at(assetPath);
			assetData.index = i;
			continue;
		}

		// skip if already loaded
		if (assetManager.contains(assetManager.read_id(assetPath)))
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
		m_loadedAssets.add(assetPath, std::move(assetData));

		i++;
	}

	// unload assets that are not in the loaded set
	Vector<Path> toUnload;
	for (auto const& [path, assetData] : m_loadedAssets)
	{
		if (!loaded.contains(path))
		{
			toUnload.add(path);
		}
	}
	for (auto const& path : toUnload)
	{
		// unload the asset
		AssetData& assetData = m_loadedAssets.at(path);
		if (assetData.id != INVALID_ID)
		{
			assetManager.unload(assetData.id);
		}

		// remove from registered assets
		m_loadedAssets.remove(path);
	}

	// update assets list
	m_assets = newAssets;
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
		auto registeredIt = m_loadedAssets.find(assetPath);
		if (registeredIt == m_loadedAssets.end())
		{
			// asset not registered, skip
			continue;
		}

		// get the data
		AssetData& assetData = m_loadedAssets.at(assetPath);

		// unload the asset
		if (assetData.id != INVALID_ID)
		{
			assetManager.unload(assetData.id);
		}
	}

	// Unload any remaining registered assets
	for(UUID const id : m_registeredAssets)
	{
		assetManager.unload(id);
	}

	// clear the registered assets
	m_loadedAssets.clear();
	m_registeredAssets.clear();
}

void Minty::Scene::on_load()
{
	MINTY_TRACE_SCOPE();

	m_systemManager->initialize();
	m_entityManager->initialize();
	
	load_assets(m_assets);
}

void Minty::Scene::on_unload()
{
	MINTY_TRACE_SCOPE();

	unload_assets();

	m_systemManager->dispose();
	m_entityManager->dispose();
}

void Minty::Scene::on_frame_update(Time const& time)
{
	MINTY_TRACE_SCOPE();

	m_systemManager->frame_update(time);
	m_entityManager->frame_update(time);
}

void Minty::Scene::on_fixed_update(Time const& time)
{
	MINTY_TRACE_SCOPE();

	m_systemManager->fixed_update(time);
	m_entityManager->fixed_update(time);
}

void Minty::Scene::on_finalize()
{
	MINTY_TRACE_SCOPE();

	m_systemManager->finalize();
	m_entityManager->finalize();
}

void Minty::Scene::on_render()
{
	MINTY_TRACE_SCOPE();

	m_systemManager->render();
}

void Minty::Scene::on_event(Event& event)
{
	MINTY_TRACE_SCOPE();

	// pass event on to the systems
	m_systemManager->handle_event(event);
}

void Minty::Scene::register_asset(UUID const assetId)
{
	m_registeredAssets.add(assetId);
}

void Minty::Scene::unregister_asset(UUID const assetId)
{
	m_registeredAssets.remove(assetId);
}

void Minty::Scene::serialize(Writer& writer) const
{
	MINTY_ABORT("Not implemented.");
}

Bool Minty::Scene::deserialize(Reader& reader)
{
	// load new assets, unload old assets
	Vector<Path> assetPaths;
	reader.read("Assets", assetPaths);
	load_assets(assetPaths);

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
