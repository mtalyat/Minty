#include "pch.h"
#include "Scene.h"
#include "Minty/Asset/AssetManager.h"
#include "Minty/Component/ColliderComponent.h"
#include "Minty/Component/DestroyTag.h"
#include "Minty/Component/RigidbodyComponent.h"
#include "Minty/Component/TransformComponent.h"
#include "Minty/Debug/Trace.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/Writer.h"
#include "Minty/Scene/SceneInfo.h"
#include "Minty/System/SystemManager.h"
#include "Minty/System/SystemManagerInfo.h"
#include "Minty/Entity/EntityManager.h"
#include "Minty/Entity/EntityManagerInfo.h"
#include "Minty/Scene/SceneManager.h"

using namespace Minty;

Minty::Scene::Scene(SceneInfo const& info)
	: m_id(info.id)
	, m_name(info.name)
	, m_loaded(false)
	, m_entityManager(nullptr)
	, m_systemManager(nullptr)
	, m_loadedAssets()
	, m_assets()
	, m_registeredAssets()
{
	// create the entity manager
	EntityManagerInfo entityManagerInfo{};
	m_entityManager = EntityManager::create(create_ref(), entityManagerInfo);

	// create the system manager
	SystemManagerInfo systemManagerInfo{};
	m_systemManager = SystemManager::create(create_ref(), systemManagerInfo);
}

Minty::Scene::Scene(Scene&& other) noexcept
	: m_id(std::move(other.m_id))
	, m_name(std::move(other.m_name))
	, m_loaded(std::move(other.m_loaded))
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
		m_loaded = std::move(other.m_loaded);
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

Ref<Scene> const &Minty::Scene::get_active()
{
	return SceneManager::get_singleton().get_active();
}

void Minty::Scene::load_assets(Vector<Path> const &newAssets)
{
	// MINTY_LOG_DEBUG("Scene start loading assets...");

	// load all of the assets into the Scene
	Set<Path> loaded;
	AssetManager& assetManager = AssetManager::get_singleton();
	Size i = 0;
	for (auto const& assetPath : newAssets)
	{
		MINTY_ASSERT(!assetPath.is_empty(), ErrorCode::Argument_ExpectedNonEmpty);

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
		Shared<Asset> asset = assetManager.load_asset(assetPath);
		MINTY_ASSERT_F(asset != nullptr, ErrorCode::Asset_LoadFailed, assetPath);
		assetData.id = asset->get_id();

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
		if (assetData.id.is_valid())
		{
			assetManager.unload(assetData.id);
		}

		// remove from registered assets
		m_loadedAssets.remove(path);
	}

	// update assets list
	m_assets = newAssets;
	
	// MINTY_LOG_DEBUG("Scene done loading assets.");
}

void Minty::Scene::unload_assets()
{
	// MINTY_LOG_DEBUG("Scene start unloading assets...");

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
		if (assetData.id.is_valid())
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

	// MINTY_LOG_DEBUG("Scene done unloading assets.");
}

void Minty::Scene::on_load()
{
	MINTY_TRACE_SCOPE();

	m_systemManager->on_scene_load();
	m_entityManager->on_scene_load();
	
	load_assets(m_assets);

	m_loaded = true;
}

void Minty::Scene::on_unload()
{
	MINTY_TRACE_SCOPE();

	unload_assets();

	m_systemManager->on_scene_unload();
	m_entityManager->on_scene_unload();

	m_loaded = false;
}

void Minty::Scene::on_frame_update(Timestep const time)
{
	MINTY_TRACE_SCOPE();

	m_systemManager->frame_update(time);
	m_entityManager->frame_update(time);
}

void Minty::Scene::on_fixed_update(Timestep const time)
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

Shared<Scene> Minty::Scene::create(SceneInfo const& info)
{
	return Shared<Scene>::create(info);
}

Shared<Scene> Minty::Scene::create()
{
	SceneInfo info{};
	return create(info);
}

void Minty::Serializer<Scene>::serialize(Writer &writer, Scene const &value)
{
	MINTY_NOT_IMPLEMENTED();
}

Bool Minty::Serializer<Scene>::deserialize(Reader &reader, Scene &value)
{
	// load new assets, unload old assets
	Vector<Path> assetPaths;
	reader.read("Assets", assetPaths);
    value.load_assets(assetPaths);

	// read the systems
	if (reader.indent("Systems"))
	{
		Serializer<SystemManager>::deserialize(reader, *value.m_systemManager);
		reader.outdent();
	}

	// read the entities
	if (reader.indent("Entities"))
	{
		Serializer<EntityManager>::deserialize(reader, *value.m_entityManager);
		reader.outdent();
	}

	return true;
}