/// \file       S_GameManager.cpp
/// \date       08/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#include "Game/Floppy/S_GameManager.hpp"
#include "Game/Floppy/Asset/S_ConveyorAsset.hpp"
#include "Game/Floppy/Prompt/S_CommandPrompt.hpp"
#include "Game/Floppy/Controller/S_ConveyorController.hpp"
#include "Game/Floppy/Controller/S_DoorController.hpp"
#include "Game/Floppy/Prompt/Capcha.hpp"

/*virtual */ void S_GameManager::Awake()
{
	mp_floppy     = nullptr;
	m_key_delay   = 0.3f;
	m_key_elapsed = 0.1f;

	m_door_state[0] = true;
	m_door_state[1] = true;
	m_door_state[2] = true;

	m_conveyor_state[0] = true;
	m_conveyor_state[1] = true;
	m_conveyor_state[2] = true;
	m_conveyor_state[3] = true;

	m_firewall_cooldown  = 30.0f;
	m_firewall_elapsed   = 30.0f;
	m_firewall_activated = false;
	m_firewall_duration  = 10.0f;
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

	// Firewall update
	if(m_firewall_activated)
	{
		m_firewall_elapsed += CTime::delta_time;

		if(m_firewall_elapsed >= m_firewall_duration)
			DeactivateFireWall();
	}

	m_firewall_elapsed += CTime::delta_time;
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

		auto spawner    = CGameObject::FindWithTag(tag_spawner);
		auto conveyors  = CGameObject::FindGameObjectsWithTag(tag_conveyor);
		auto controller = CGameObject::Find("Conveyor_" + tag_spawner);

		if (spawner)
			spawner->SetActive(true);

		if (controller)
			controller->GetComponent<S_ConveyorController>()->ActivateConveyor();

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
		controller->GetComponent<S_ConveyorController>()->DesactivateConveyor();

	for(auto* p_conveyor : conveyors)
	{
		auto* p_controller = p_conveyor->GetComponent<S_ConveyorAsset>();
		p_controller->SetEnabled(false);
	}

	mp_prompt->LogMessage("> Warning : Conveyor " + tag_spawner + " stopped");
}

void S_GameManager::OpenDoor(ESpawnZone zone)
{
	if (!m_door_state[zone]) 
	{
		m_door_state[zone] = true;

		CString door_name;
		CString door_type;
		switch (zone)
		{
			case R1: door_name = "Door_Block_R1"; door_type = "R1"; break;
			case R2: door_name = "Door_Block_R2"; door_type = "R2"; break;
			case R3: door_name = "Door_Block_R3"; door_type = "R3"; break;

			default:
			{
				return;
			}
		}

		auto* p_door = CGameObject::Find(door_name);

		if (p_door)
			p_door->GetComponent<S_DoorController>()->OpenDoor();

		mp_prompt->LogMessage("> Warning : Door " + door_type + " opened");
	}
}

void S_GameManager::CloseDoor(ESpawnZone zone)
{
	// Case 1 : The door is already closed
	// Nothing to do
	if (!m_door_state[zone]) {
		return;
	}

	// Case 2 : There is already a door closed
	// Unauthorized action
	for (bool state : m_door_state)
	{
		if (!state)
			return;
	}

	// Case 3 : Authorized close
	m_door_state[zone] = false;

	CString door_name;
	CString door_type;
	switch (zone)
	{
		case R1: door_name = "Door_Block_R1"; door_type = "R1"; break;
		case R2: door_name = "Door_Block_R2"; door_type = "R2"; break;
		case R3: door_name = "Door_Block_R3"; door_type = "R3"; break;

		default:
		{
			return;
		}
	}

	auto* p_door = CGameObject::Find(door_name);

	if(p_door)
		p_door->GetComponent<S_DoorController>()->CloseDoor();

	mp_prompt->LogMessage("> Warning : Door " + door_type + " closed");
}

void S_GameManager::TryActivateFirewall()
{
	m_tried_activate_firewall = true;
	DoCapcha();
}

void S_GameManager::ActivateFireWall()
{
	// Case 1 : Already activated
	if (m_firewall_activated)
	{
		mp_prompt->LogMessage("FIREWALL ALREADY ACTIVATED");
		return;
	}

	// Case 2 : Cooldow left
	if(m_firewall_elapsed < m_firewall_cooldown)
	{
		CString message = "FIREWALL NOT READY (";
		const int time_left = m_firewall_cooldown - m_firewall_elapsed;

		// String to int
		char buffer[8] = { '\0' };
		sprintf(buffer, "%d", time_left);

		message += buffer;
		message += " SECONDS LEFT)";

		mp_prompt->LogMessage(message.Data());
		return;
	}

	mp_prompt->LogMessage("ACTIVATING FIREWALL...");
	mp_prompt->LogMessage("FIREWALL ACTIVATED");
	// Case 3 : Allowed
	m_firewall_elapsed   = 0.0f;
	m_firewall_activated = true;

	// Gets all door
	auto* p_door_1 = CGameObject::Find("Door_Block_R1");
	auto* p_door_2 = CGameObject::Find("Door_Block_R2");
	auto* p_door_3 = CGameObject::Find("Door_Block_R3");

	if (p_door_1) p_door_1->GetComponent<S_DoorController>()->CloseDoor();
	if (p_door_2) p_door_2->GetComponent<S_DoorController>()->CloseDoor();
	if (p_door_3) p_door_3->GetComponent<S_DoorController>()->CloseDoor();
}

void S_GameManager::TryCleanAllCB()
{
	m_tried_clean_all_CB = true;
	DoCapcha();
}

void S_GameManager::DeactivateFireWall()
{
	m_firewall_elapsed   = 0.0f;
	m_firewall_activated = false;

	mp_prompt->LogMessage("FIREWALL DEACTIVATED");

	// Gets all door
	auto* p_door_1 = CGameObject::Find("Door_Block_R1");
	auto* p_door_2 = CGameObject::Find("Door_Block_R2");
	auto* p_door_3 = CGameObject::Find("Door_Block_R3");

	if (p_door_1) p_door_1->GetComponent<S_DoorController>()->OpenDoor();
	if (p_door_2) p_door_2->GetComponent<S_DoorController>()->OpenDoor();
	if (p_door_3) p_door_3->GetComponent<S_DoorController>()->OpenDoor();
}

void S_GameManager::CleanAllCB()
{
	
}

void S_GameManager::ShowHelp()
{
	mp_prompt->LogMessage("COMMANDS :");
	mp_prompt->LogMessage("STOP [CB CODE]");
	mp_prompt->LogMessage("AVAILABLE COMMANDS : ");
	mp_prompt->LogMessage("OPEN [DOOR CODE]");
	mp_prompt->LogMessage("CLOSE [DOOR CODE]");
	mp_prompt->LogMessage("START [CB CODE]");
	mp_prompt->LogMessage("STOP [CB CODE]");
	mp_prompt->LogMessage("ACTIVATE FIREWALL");
	mp_prompt->LogMessage("CLEAN ALL CB");
	mp_prompt->LogMessage("DOOR CODES : D1, D2, D3");
	mp_prompt->LogMessage("CB CODES : CB1, CB2, CB3, CB4");
	mp_prompt->LogMessage("USE \"START HACKING\" TO START");
}

void S_GameManager::StartHacking()
{
	// TODO start spawning waves
	mp_prompt->LogMessage("START HACKING");
}

void S_GameManager::ProcessUnknownCommand(const CString& command)
{
	if (m_on_capcha)
	{
		if (CapchaTestPassed(command)) {
			m_on_capcha = false;
			mp_prompt->LogMessage("TEST PASSED");
			if (m_tried_activate_firewall) { m_tried_activate_firewall = false; ActivateFireWall(); }
			else if (m_tried_clean_all_CB) { m_tried_clean_all_CB = false; CleanAllCB(); }
		}
		else
		{
			mp_prompt->LogMessage("BAD ANSWER");
			mp_prompt->LogMessage("THE ANSWER WAS : " + m_current_capcha.answer);
			mp_prompt->LogMessage("GENERATING NEW SECURITY TEST");
			DoCapcha();
		}
	}
	else
	{
		mp_prompt->LogMessage("ERROR : COMMAND NOT FOUND");
	}
}

void S_GameManager::DoCapcha()
{
	mp_prompt->LogMessage("SENSITIVE COMMAND SUBMITTED");
	mp_prompt->LogMessage("PLEASE PASS THIS TEST TO CONFIRM YOU ARE NOT A BOT");
	m_on_capcha = true;
	m_current_capcha = Game::Capcha::generateCapcha();
	mp_prompt->LogMessage(m_current_capcha.question);
}

bool S_GameManager::CapchaTestPassed(CString answer)
{
	return answer == m_current_capcha.answer;
}
