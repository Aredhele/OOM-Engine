/// \file       S_SpawnerManager.hpp
/// \date       09/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_S_ASSET_MANAGER_HPP__
#define OOM_ENGINE_S_ASSET_MANAGER_HPP__

#include "SDK/SDK.hpp"
#include "Game/Floppy/Asset/S_AssetSpawner.hpp"

class S_SpawnerManager : public CBehavior
{
public:

	void Awake    () final;
	void Start    () final;
	void Update   () final;
	void OnDestroy() final;

public:

	void RegisterAssetWave(float time, ESpawnZone zone);
	void RegisterAssetWave(float time, float delay, EAsset type, ESpawnZone zone, const CString& pattern);

private:

	void CreateSpawners ();
	void DispatchWaves  ();

private:

	std::vector<CAssetWave*>   m_waves_to_dispatch;
	std::vector<CGameObject*>  m_asset_spawners;
};



#endif // !OOM_ENGINE_S_ASSET_MANAGER_HPP__