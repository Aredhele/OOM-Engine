/// \file       S_AssetSpawner.cpp
/// \date       09/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#include "Game/Floppy/Asset/S_AssetSpawner.hpp"

// Assets
#include "Game/Floppy/Asset/S_BigAsset.hpp"
#include "Game/Floppy/Asset/S_BusAsset.hpp"
#include "Game/Floppy/Asset/S_ConveyorAsset.hpp"

/*virtual */ void S_AssetSpawner::Awake()
{
	// None
}

/*virtual */ void S_AssetSpawner::Start()
{
	// None
}

/*virtual */ void S_AssetSpawner::Update()
{
	ProcessWaitingList();
	ProcessActiveWave ();
}

/*virtual */ void S_AssetSpawner::OnDestroy()
{
	for (auto* p_wave : m_waves_to_process)
		delete p_wave;

	for (auto* p_wave : m_processing_waves)
		delete p_wave;

	m_waves_to_process.clear();
	m_processing_waves.clear();
}

/*virtual */ void S_AssetSpawner::OnDrawGizmos()
{
	Sdk::Debug::DrawBox(GetTransform()->GetPosition(), 2.0f, 2.0f, glm::vec3(1.0f, 0.0f, 0.0f));
}

void S_AssetSpawner::ProcessWaitingList()
{
	for(auto i = 0; i < m_waves_to_process.size(); /* None */)
	{
		if(CTime::time >= m_waves_to_process[i]->m_time)
		{
			// The wave is candidate to be processed
			m_processing_waves.push_back(m_waves_to_process[i]);
			m_processing_waves.back()->m_elapsed = m_processing_waves.back()->m_delay;

			m_waves_to_process[i] = m_waves_to_process.back();
			m_waves_to_process.pop_back();
		}
		else
		{
			i++;
		}
	}
}

void S_AssetSpawner::ProcessActiveWave()
{
	for (auto i = 0; i < m_processing_waves.size(); /* None */)
	{
		// Buffer wave pointer
		auto* p_wave = m_processing_waves[i];

		// Incrementing internal timer
		p_wave->m_elapsed += CTime::delta_time;

		// Check if its time to spawn (and if there something to spawn)
		if(p_wave->m_elapsed >= p_wave->m_delay && 
		   p_wave->m_current <  p_wave->m_pattern.Size())
		{
			// Spawning !
			SpawnAsset(
				p_wave->m_type, 
				p_wave->m_pattern[p_wave->m_current] - '0');

			p_wave->m_current += 1;
			p_wave->m_elapsed  = 0.0f;
		}

		// Check if the wave is over
		if(p_wave->m_current >= p_wave->m_pattern.Size())
		{
			// The wave must be removed
			m_processing_waves[i] = m_processing_waves.back();
			m_processing_waves.pop_back();

			delete p_wave;
			p_wave = nullptr;
		}
		else
		{
			i++;
		}
	}
}

void S_AssetSpawner::SpawnAsset(EAsset type, unsigned size)
{
	switch(type)
	{
		case BigAsset:		SpawnBigAsset     (size); break;
		case BusAsset:      SpawnBusAsset     (size); break;
		case ConveyorAsset: SpawnConveyorAsset(size); break;
	}
}

void S_AssetSpawner::SpawnBigAsset(uint32_t size)
{
	// Creating the big asset
	auto* p_game_object = CGameObject::Instantiate(GetTransform()->GetPosition() + glm::vec3(0.0f, 0.0f, 6.0f));
	auto* p_big_asset   = p_game_object->AddComponent<S_BigAsset>();

	p_big_asset->SetKiloBytes(S_BigAsset::s_cost);
	p_game_object->GetTransform().SetScale(0.5f, 0.5f, 0.5f);
	p_game_object->SetTag("Big_Asset");
}

void S_AssetSpawner::SpawnBusAsset(uint32_t size) 
{
	// Creating the bus asset
	auto* p_game_object = CGameObject::Instantiate(GetTransform()->GetPosition());
	auto* p_bus_asset   = p_game_object->AddComponent<S_BusAsset>();

	p_bus_asset->SetKiloBytes(S_BusAsset::s_cost * size);
	p_game_object->GetTransform().SetScale(size, size, size);
	p_game_object->SetTag("Bus_Asset");
}

void S_AssetSpawner::SpawnConveyorAsset(uint32_t size)
{
	// Creating the conveyor asset
	auto* p_game_object    = CGameObject::Instantiate(GetTransform()->GetPosition());
	auto* p_conveyor_asset = p_game_object->AddComponent<S_ConveyorAsset>();

	p_conveyor_asset->SetKiloBytes(S_ConveyorAsset::s_cost * size);
	p_game_object->GetTransform().SetScale(size, size, size);
	p_game_object->SetTag("Conveyor_Asset");
}

void S_AssetSpawner::RegisterAssetWave(CAssetWave* p_asset_wave)
{
	m_waves_to_process.push_back(p_asset_wave);
}
