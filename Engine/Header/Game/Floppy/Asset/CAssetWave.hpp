/// \file       CAssetWave.hpp
/// \date       09/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_ASSET_WAVE_HPP__
#define OOM_ENGINE_C_ASSET_WAVE_HPP__

#include "Game/Floppy/Asset/IAsset.hpp"

enum ESpawnZone : uint32_t
{
	R1 = 0x0,
	R2 = 0x1,
	R3 = 0x2,
	C1 = 0x3,
	C2 = 0x4,
	C3 = 0x5,
	C4 = 0x6
};

class CAssetWave
{
public:

	CAssetWave(float time, float delay, EAsset type, ESpawnZone zone, CString pattern);

private:

	friend class S_AssetSpawner;
	friend class S_SpawnerManager;

	float      m_time;
	float      m_delay;
	EAsset     m_type;
	ESpawnZone m_zone;
	CString    m_pattern;

	float      m_elapsed;
	uint32_t   m_current;
};

#endif // !OOM_ENGINE_S_ASSET_SPAWNER_HPP__