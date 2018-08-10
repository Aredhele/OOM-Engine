/// \file       S_AssetSpawner.hpp
/// \date       09/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_S_ASSET_SPAWNER_HPP__
#define OOM_ENGINE_S_ASSET_SPAWNER_HPP__

#include "SDK/SDK.hpp"
#include "Game/Floppy/Asset/CAssetWave.hpp"

class S_AssetSpawner : public CBehavior
{
public:

	void Awake        () final;
	void Start        () final;
	void Update       () final;
	void OnDestroy    () final;
	void OnDrawGizmos () final;

public:

	void RegisterAssetWave(CAssetWave* p_asset_wave);

private:

	void ProcessWaitingList ();
	void ProcessActiveWave  ();
	void SpawnAsset         (EAsset type, uint32_t size);

	void SpawnBigAsset	    (uint32_t size);
	void SpawnBusAsset      (uint32_t size);
	void SpawnConveyorAsset (uint32_t size);

private:

	bool					 m_block_conveyor;
	std::vector<CAssetWave*> m_waves_to_process;
	std::vector<CAssetWave*> m_processing_waves;
};

#endif // !OOM_ENGINE_S_ASSET_SPAWNER_HPP__