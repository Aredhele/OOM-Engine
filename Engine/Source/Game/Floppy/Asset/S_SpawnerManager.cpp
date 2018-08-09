/// \file       S_SpawnerManager.cpp
/// \date       09/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#include "Game/Floppy/Asset/S_SpawnerManager.hpp"

/*virtual */ void S_SpawnerManager::Awake()
{
	// None
}

/*virtual */ void S_SpawnerManager::Start()
{
	CreateSpawners();
	DispatchWaves ();
}

/*virtual */ void S_SpawnerManager::Update()
{
	// None
}

/*virtual */ void S_SpawnerManager::OnDestroy()
{
	// None
}

void S_SpawnerManager::CreateSpawners()
{
	m_asset_spawners.push_back(CGameObject::Instantiate(glm::vec3( 0.0f,  -55.0f, 4.0f))); // R1
	m_asset_spawners.push_back(CGameObject::Instantiate(glm::vec3( 0.0f,   55.0f, 4.0f))); // R2
	m_asset_spawners.push_back(CGameObject::Instantiate(glm::vec3( 58.0f,   0.0f, 4.0f))); // R3
	m_asset_spawners.push_back(CGameObject::Instantiate(glm::vec3(-46.0f, -40.0f, 4.0f))); // C1
	m_asset_spawners.push_back(CGameObject::Instantiate(glm::vec3(-46.0f,  40.0f, 4.0f))); // C2
	m_asset_spawners.push_back(CGameObject::Instantiate(glm::vec3( 47.0f,  40.0f, 4.0f))); // C3
	m_asset_spawners.push_back(CGameObject::Instantiate(glm::vec3( 38.0f, -45.0f, 4.0f))); // C4

	for (auto p_spawner : m_asset_spawners)
	{
		p_spawner->AddComponent<S_AssetSpawner>();
	}
}

void S_SpawnerManager::DispatchWaves()
{
	for(auto* p_wave : m_waves_to_dispatch)
	{
		m_asset_spawners[p_wave->m_zone]->GetComponent<S_AssetSpawner>()->RegisterAssetWave(p_wave);
	}

	m_waves_to_dispatch.clear();
}

void S_SpawnerManager::RegisterAssetWave(float time, ESpawnZone zone)
{
	RegisterAssetWave(time, 0.0f, EAsset::BigAsset, zone, "1");
}

void S_SpawnerManager::RegisterAssetWave(float time, float delay, EAsset type, ESpawnZone zone, const CString& pattern)
{
	m_waves_to_dispatch.push_back(new CAssetWave(time, delay, type, zone, pattern));
}


