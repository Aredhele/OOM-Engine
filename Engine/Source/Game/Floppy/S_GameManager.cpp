/// \file       S_GameManager.cpp
/// \date       08/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#include "Game/Floppy/S_GameManager.hpp"
#include "Game/Floppy/Asset/S_ConveyorAsset.hpp"
#include "Game/Floppy/Prompt/S_CommandPrompt.hpp"
#include "Game/Floppy/Util/S_ConveyorAudioController.hpp"

/*virtual */ void S_GameManager::Awake()
{
	mp_floppy     = nullptr;
	m_key_delay   = 0.3f;
	m_key_elapsed = 0.1f;
}

/*virtual */ void S_GameManager::Start()
{
	mp_floppy         = CGameObject::Find("Floppy");
	auto* p_prompt_go = CGameObject::Find("Prompt");
	auto* p_camera_go = CGameObject::FindWithTag("MainCamera");

	if (p_camera_go)
		mp_camera = p_camera_go->GetComponent<S_CameraController>();

	if(p_prompt_go)
		mp_prompt = p_prompt_go->GetComponent<S_CommandPrompt>();

	m_conveyor_state[0] = true;
	m_conveyor_state[1] = true;
	m_conveyor_state[2] = true;
	m_conveyor_state[3] = true;
}

/*virtual */ void S_GameManager::Update()
{
	m_key_elapsed += CTime::delta_time;

	if (Sdk::Input::IsKeyPressed(GLFW_KEY_LEFT_CONTROL) && m_key_elapsed >= m_key_delay)
	{
		m_key_elapsed = 0.0f;

		if(mp_prompt->IsOpen())
		{
			mp_prompt->ClosePrompt();
			mp_camera->SetEnabled(true);
		}
		else
		{
			mp_prompt->OpenPrompt();
			mp_camera->SetEnabled(false);
		}
	}
}

/*virtual */ void S_GameManager::OnDestroy()
{
	// None
}

void S_GameManager::StartConveyorBelt(ESpawnZone zone)
{
	if(!m_conveyor_state[zone - 3])
	{
		// Start the conveyor
		m_conveyor_state[zone - 3] = true;

		CString tag_spawner;
		CString tag_conveyor;
		switch (zone)
		{
			case C1: tag_spawner = "C1"; tag_conveyor = "C1_Conveyor"; break;
			case C2: tag_spawner = "C2"; tag_conveyor = "C2_Conveyor"; break;
			case C3: tag_spawner = "C3"; tag_conveyor = "C3_Conveyor"; break;
			case C4: tag_spawner = "C4"; tag_conveyor = "C4_Conveyor"; break;

			default:
			{
				return;
			}
		}

		auto spawner   = CGameObject::FindWithTag(tag_spawner);
		auto conveyors  = CGameObject::FindGameObjectsWithTag(tag_conveyor);
		auto controller = CGameObject::Find("Conveyor_" + tag_spawner);

		if (spawner)
			spawner->SetActive(true);

		if (controller)
			controller->GetComponent<S_ConveyorAudioController>()->ActivateConveyor();

		for (auto* p_conveyor : conveyors)
		{
			auto* p_controller = p_conveyor->GetComponent<S_ConveyorAsset>();
			p_controller->SetEnabled(true);
		}

		mp_prompt->LogMessage("> Warning : Conveyor " + tag_spawner + " started");
	}
}

void S_GameManager::StopConveyorBelt(ESpawnZone zone)
{
	// Case 1 : The conveyor is already stopped
	// Nothing to do
	if (!m_conveyor_state[zone - 3]) {
		return;
	}

	// Case 2 : There is already a conveyor stopped
	// Unauthorized action
	for (bool state : m_conveyor_state)
	{
		if (!state)
			return;
	}

	// Case 3 : Authorized stop
	m_conveyor_state[zone - 3] = false;

	CString tag_spawner;
	CString tag_conveyor;
	switch(zone)
	{
		case C1: tag_spawner = "C1"; tag_conveyor = "C1_Conveyor"; break;
		case C2: tag_spawner = "C2"; tag_conveyor = "C2_Conveyor"; break;
		case C3: tag_spawner = "C3"; tag_conveyor = "C3_Conveyor"; break;
		case C4: tag_spawner = "C4"; tag_conveyor = "C4_Conveyor"; break;

		default:
		{
			return;
		}
	}

	auto spawner    = CGameObject::FindWithTag(tag_spawner);
	auto conveyors  = CGameObject::FindGameObjectsWithTag(tag_conveyor);
	auto controller = CGameObject::Find("Conveyor_" + tag_spawner);

	if (spawner)
		spawner->SetActive(false);

	if (controller)
		controller->GetComponent<S_ConveyorAudioController>()->DesactivateConveyor();

	for(auto* p_conveyor : conveyors)
	{
		auto* p_controller = p_conveyor->GetComponent<S_ConveyorAsset>();
		p_controller->SetEnabled(false);
	}

	mp_prompt->LogMessage("> Warning : Conveyor " + tag_spawner + " stopped");
}
