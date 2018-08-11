/// \file       S_AssetSpawner.cpp
/// \date       09/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#include "Game/Floppy/Asset/S_AssetSpawner.hpp"

// Assets
#include "Game/Floppy/Asset/S_BigAsset.hpp"
#include "Game/Floppy/Asset/S_BusAsset.hpp"
#include "Game/Floppy/Util/S_SoundSource.hpp"
#include "Game/Floppy/Asset/S_ConveyorAsset.hpp"
#include "Game/Floppy/Controller/S_AlarmController.hpp"

/*virtual */ void S_AssetSpawner::Awake()
{
	m_is_cleaning    = false;
	m_block_conveyor = false;
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

			// Enemies incommmmmingggg
			TriggerAlarm(
				m_processing_waves.back()->m_zone, 
				m_processing_waves.back()->m_type);
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
		if ((m_block_conveyor || m_is_cleaning) && m_processing_waves[i]->m_type == ConveyorAsset)
		{
			i++;
			continue;
		}
			
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
	auto* p_game_object = CGameObject::Instantiate(GetTransform()->GetPosition() + glm::vec3(0.0f, 0.0f, 12.0f));
	auto* p_big_asset = p_game_object->AddComponent<S_BigAsset>();

	p_big_asset->SetSpeed(1.0f);
	p_big_asset->SetHitPoint(5);
	p_big_asset->SetKiloBytes(S_BigAsset::s_cost);

	p_game_object->SetTag("Big_Asset");
	p_game_object->GetTransform().SetScale(1.0f, 1.0f, 1.0f);
	p_game_object->GetTransform().SetOrientation(GetTransform()->GetOrientation());
}

void S_AssetSpawner::SpawnBusAsset(uint32_t size) 
{
	// Creating the bus asset
	auto* p_game_object = CGameObject::Instantiate(GetTransform()->GetPosition());
	auto* p_bus_asset = p_game_object->AddComponent<S_BusAsset>();

	p_bus_asset->SetSpeed(2.0f);
	p_bus_asset->SetHitPoint(1);
	p_bus_asset->SetKiloBytes(S_BusAsset::s_cost * size);

	p_game_object->SetTag("Bus_Asset");
	p_game_object->GetTransform().SetScale(size * 0.75, size * 0.75, size * 0.75);
	p_game_object->GetTransform().SetOrientation(GetTransform()->GetOrientation());
}

void S_AssetSpawner::SpawnConveyorAsset(uint32_t size)
{
	// Creating the conveyor asset
	auto* p_game_object = CGameObject::Instantiate(GetTransform()->GetPosition());
	auto* p_conveyor_asset = p_game_object->AddComponent<S_ConveyorAsset>();

	p_conveyor_asset->SetSpeed(2.0f);
	p_conveyor_asset->SetHitPoint(1);
	p_conveyor_asset->SetKiloBytes(S_ConveyorAsset::s_cost * size);

	p_game_object->GetTransform().SetScale(size * 0.75, size * 0.75, size * 0.75);
	p_game_object->SetTag(GetGameObject()->GetTag() + "_Conveyor");
	p_game_object->GetTransform().SetOrientation(GetTransform()->GetOrientation());
}

void S_AssetSpawner::TriggerAlarm(ESpawnZone zone, EAsset type)
{
	CGameObject* p_alarm_controller = nullptr;
	if(type == EAsset::BigAsset)
	{
		p_alarm_controller = CGameObject::FindWithTag("Super_alarm_controller");

		if(p_alarm_controller)
		{
			auto* p_controller = p_alarm_controller->GetComponent<S_AlarmController>();
			if (p_controller)
			{
				p_controller->TriggerAlarm();
			}
		}

		return;
	}

	// Switching on the door alarm
	switch(zone)
	{
		case R1: p_alarm_controller = CGameObject::FindWithTag("Alarm_controller_D1");  break;
		case R2: p_alarm_controller = CGameObject::FindWithTag("Alarm_controller_D2");  break;
		case R3: p_alarm_controller = CGameObject::FindWithTag("Alarm_controller_D3");  break;
		case C1: p_alarm_controller = CGameObject::FindWithTag("Alarm_controller_CB1"); break;
		case C2: p_alarm_controller = CGameObject::FindWithTag("Alarm_controller_CB2"); break;
		case C3: p_alarm_controller = CGameObject::FindWithTag("Alarm_controller_CB3"); break;
		case C4: p_alarm_controller = CGameObject::FindWithTag("Alarm_controller_CB4"); break;
	}

	if(p_alarm_controller)
	{
		auto* p_controller = p_alarm_controller->GetComponent<S_AlarmController>();
		if(p_controller)
		{
			p_controller->TriggerAlarm();
		}
	}
}

void S_AssetSpawner::RegisterAssetWave(CAssetWave* p_asset_wave)
{
	m_waves_to_process.push_back(p_asset_wave);
}

void S_AssetSpawner::StartClean()
{
	m_is_cleaning = true;
}

void S_AssetSpawner::StopClean()
{
	m_is_cleaning = false;
}

void S_AssetSpawner::BlockConveyor()
{
	m_block_conveyor = true;
}

void S_AssetSpawner::UnblockConveyor()
{
	m_block_conveyor = false;
}
