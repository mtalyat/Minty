#include "pch.h"
#include "Scene.h"
#include "Minty/Asset/AssetManager.h"

Minty::Scene::Scene(SceneBuilder const& builder)
	: Asset(builder.id)
	, mp_entityManager(nullptr)
	, mp_systemManager(nullptr)
	, m_registeredAssets()
	, m_assets(builder.assets)
	, m_loadedAssets()
{
	// create the entity manager
	EntityManagerBuilder entityManagerBuilder{};
	mp_entityManager = new EntityManager(entityManagerBuilder);

	// create the system manager
	SystemManagerBuilder systemManagerBuilder{};
	systemManagerBuilder.scene = create_ref();
	mp_systemManager = new SystemManager(systemManagerBuilder);
}

void Minty::Scene::on_load()
{
	// load all of the assets into the Scene
	AssetManager& assetManager = AssetManager::get_singleton();
	Size i = 0;
	for (auto const& assetPath : m_assets)
	{
		MINTY_ASSERT(!assetPath.is_empty(), "Asset path is empty");
		MINTY_ASSERT(!m_registeredAssets.contains(assetPath), F("Scene already contains an Asset with the Path: {}", assetPath));

		m_registeredAssets.add(assetPath, { 0, INVALID_ID });

		// get the data
		AssetData& assetData = m_registeredAssets.at(assetPath);
		assetData.index = i;

		// load the asset
		Ref<Asset> asset = assetManager.load_asset(assetPath);
		if (asset == nullptr)
		{
			MINTY_ERROR(F("Failed to load asset: {}", assetPath));
		}
		else
		{
			assetData.id = asset->get_id();
		}

		i++;
	}

	mp_systemManager->initialize();
	mp_entityManager->initialize();
}

void Minty::Scene::on_unload()
{
	mp_systemManager->dispose();
	mp_entityManager->dispose();

	// unload all of the assets from the Scene
	AssetManager& assetManager = AssetManager::get_singleton();

	// unload backwards in case of dependencies
	for (auto it = m_assets.rbegin(); it != m_assets.rend(); ++it)
	{
		Path const& assetPath = *it;

		auto registeredIt = m_registeredAssets.find(assetPath);
		if (registeredIt == m_registeredAssets.end())
		{
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

void Minty::Scene::on_update(Time const& time)
{
	mp_systemManager->update(time);
	mp_entityManager->update(time);
}
void Minty::Scene::on_finalize()
{
	mp_systemManager->finalize();
	mp_entityManager->finalize();
}

void Minty::Scene::on_render()
{
	mp_systemManager->render();
	mp_entityManager->render();
}
