/// \file       S_GameManager.cpp
/// \date       08/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#include "Game/Floppy/S_Floppy.hpp"
#include "Game/Floppy/Prompt/Capcha.hpp"
#include "Game/Floppy/S_GameManager.hpp"
#include "Game/Floppy/Asset/S_ConveyorAsset.hpp"
#include "Game/Floppy/Prompt/S_CommandPrompt.hpp"
#include "Game/Floppy/Asset/S_SpawnerManager.hpp"
#include "Game/Floppy/Controller/S_DoorController.hpp"
#include "Game/Floppy/Controller/S_ConveyorController.hpp"

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

	m_firewall_activated = false;
	m_firewall_cooldown  = 30.0f;
	m_firewall_elapsed   = 30.0f;
	m_firewall_duration  = 10.0f;

	m_clean_up_activated = false;
	m_clean_up_cooldown  = 30.0f;
	m_clean_up_elapsed   = 30.0f;
	m_clean_up_duration  = 2.0f;
}

/*virtual */ void S_GameManager::Start()
{
	mp_floppy         = CGameObject::Find("Floppy")->GetComponent<S_Floppy>();
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

	// Cleaning update
	if (m_clean_up_activated)
	{
		m_clean_up_elapsed += CTime::delta_time;

		if (m_clean_up_elapsed >= m_clean_up_duration)
			StopCleanAllCB();
	}

	if (mp_floppy->GetCurrentSize() > mp_floppy->GetLimitSize())
	{
		GameOver();
	}

	m_clean_up_elapsed += CTime::delta_time;
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
		CString code_CB;
		switch (zone)
		{
			case C1: code_CB = "CB1";  tag_spawner = "C1"; tag_conveyor = "C1_Conveyor"; break;
			case C2: code_CB = "CB2"; tag_spawner = "C2"; tag_conveyor = "C2_Conveyor"; break;
			case C3: code_CB = "CB3"; tag_spawner = "C3"; tag_conveyor = "C3_Conveyor"; break;
			case C4: code_CB = "CB4"; tag_spawner = "C4"; tag_conveyor = "C4_Conveyor"; break;

			default:
			{
				return;
			}
		}

		auto spawner    = CGameObject::FindWithTag(tag_spawner);
		auto conveyors  = CGameObject::FindGameObjectsWithTag(tag_conveyor);
		auto controller = CGameObject::Find("Conveyor_" + tag_spawner);

		if (spawner)
			spawner->GetComponent<S_AssetSpawner>()->UnblockConveyor();

		if (controller)
			controller->GetComponent<S_ConveyorController>()->ActivateConveyor();

		for (auto* p_conveyor : conveyors)
		{
			auto* p_controller = p_conveyor->GetComponent<S_ConveyorAsset>();
			p_controller->SetEnabled(true);
		}

		mp_prompt->LogMessage(code_CB + " STARTED");
	}
	else
	{
		mp_prompt->LogMessage("CB ALREADY STARTED");
	}
}

void S_GameManager::StopConveyorBelt(ESpawnZone zone)
{
	// Case 1 : The conveyor is already stopped
	// Nothing to do
	if (!m_conveyor_state[zone - 3]) {
		mp_prompt->LogMessage("CB ALREADY STOPPED");
		return;
	}

	// Case 2 : There is already a conveyor stopped
	// Unauthorized action
	for (bool state : m_conveyor_state)
	{
		if (!state)
		{
			mp_prompt->LogMessage("YOU CAN'T STOP SEVERAL CB AT THE SAME TIME");
			return;
		}
	}

	// Case 3 : Authorized stop
	m_conveyor_state[zone - 3] = false;

	CString tag_spawner;
	CString tag_conveyor;
	CString code_CB;
	switch(zone)
	{
		case C1: code_CB = "CB1";  tag_spawner = "C1"; tag_conveyor = "C1_Conveyor"; break;
		case C2: code_CB = "CB2"; tag_spawner = "C2"; tag_conveyor = "C2_Conveyor"; break;
		case C3: code_CB = "CB3"; tag_spawner = "C3"; tag_conveyor = "C3_Conveyor"; break;
		case C4: code_CB = "CB4"; tag_spawner = "C4"; tag_conveyor = "C4_Conveyor"; break;

		default:
		{
			return;
		}
	}

	auto spawner    = CGameObject::FindWithTag(tag_spawner);
	auto conveyors  = CGameObject::FindGameObjectsWithTag(tag_conveyor);
	auto controller = CGameObject::Find("Conveyor_" + tag_spawner);

	if (spawner)
		spawner->GetComponent<S_AssetSpawner>()->BlockConveyor();

	if (controller)
		controller->GetComponent<S_ConveyorController>()->DesactivateConveyor();

	for(auto* p_conveyor : conveyors)
	{
		auto* p_controller = p_conveyor->GetComponent<S_ConveyorAsset>();
		p_controller->SetEnabled(false);
	}

	mp_prompt->LogMessage(code_CB + " STOPPED");
}

void S_GameManager::OpenDoor(ESpawnZone zone)
{
	if (!m_door_state[zone]) 
	{
		m_door_state[zone] = true;

		CString door_name;
		CString door_type;
		CString code_door;
		switch (zone)
		{
			case R1: code_door = "D1";  door_name = "Door_Block_R1"; door_type = "R1"; break;
			case R2: code_door = "D2"; door_name = "Door_Block_R2"; door_type = "R2"; break;
			case R3: code_door = "D3"; door_name = "Door_Block_R3"; door_type = "R3"; break;

			default:
			{
				return;
			}
		}

		auto* p_door = CGameObject::Find(door_name);

		if (p_door)
			p_door->GetComponent<S_DoorController>()->OpenDoor();

		mp_prompt->LogMessage(code_door + "OPENED");
	}
	else
	{
		mp_prompt->LogMessage("DOOR ALREADY OPENED");	
	}
}

void S_GameManager::CloseDoor(ESpawnZone zone)
{
	// Case 1 : The door is already closed
	// Nothing to do
	if (!m_door_state[zone]) {
		mp_prompt->LogMessage("DOOR ALREDY CLOSED");
		return;
	}

	// Case 2 : There is already a door closed
	// Unauthorized action
	for (bool state : m_door_state)
	{
		if (!state)
		{
			mp_prompt->LogMessage("YOU CAN'T CLOSE SEVERAL DOORS AT THE SAME TIME");
			return;
		}
	}

	// Case 3 : Authorized close
	m_door_state[zone] = false;

	CString door_name;
	CString door_type;
	CString code_door;
	switch (zone)
	{
		case R1: code_door = "D1";  door_name = "Door_Block_R1"; door_type = "R1"; break;
		case R2: code_door = "D2"; door_name = "Door_Block_R2"; door_type = "R2"; break;
		case R3: code_door = "D3"; door_name = "Door_Block_R3"; door_type = "R3"; break;

		default:
		{
			return;
		}
	}

	auto* p_door = CGameObject::Find(door_name);

	if(p_door)
		p_door->GetComponent<S_DoorController>()->CloseDoor();

	mp_prompt->LogMessage(code_door + " CLOSED");
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
	// Case 1 : Cooldown left
	if(m_clean_up_elapsed < m_clean_up_cooldown)
	{
		CString message = "CLEANUP NOT READY (";
		const int time_left = m_firewall_cooldown - m_firewall_elapsed;

		// String to int
		char buffer[8] = { '\0' };
		sprintf(buffer, "%d", time_left);

		message += buffer;
		message += " SECONDS LEFT)";

		mp_prompt->LogMessage(message.Data());
		return;
	}

	// Case 2 : Allowed
	m_clean_up_activated = true;
	m_clean_up_elapsed   = 0.0f;

	// Gets all conveyors
	auto conveyors = CGameObject::FindGameObjectsWithTag("Conveyor");

	for(auto* p_conveyor : conveyors)
	{
		auto* p_controller = p_conveyor->GetComponent<S_ConveyorController>();

		if (p_controller)
			p_controller->StartClean();
	}

	// Gets all conveyor assets
	auto asset_c1 = CGameObject::FindGameObjectsWithTag("C1_Conveyor");
	auto asset_c2 = CGameObject::FindGameObjectsWithTag("C2_Conveyor");
	auto asset_c3 = CGameObject::FindGameObjectsWithTag("C3_Conveyor");
	auto asset_c4 = CGameObject::FindGameObjectsWithTag("C4_Conveyor");

	asset_c1.insert(asset_c1.end(), asset_c2.begin(), asset_c2.end());
	asset_c1.insert(asset_c1.end(), asset_c3.begin(), asset_c3.end());
	asset_c1.insert(asset_c1.end(), asset_c4.begin(), asset_c4.end());

	for(auto* p_asset : asset_c1)
	{
		auto* p_conveyor_asset = p_asset->GetComponent<S_ConveyorAsset>();

		if (p_conveyor_asset)
			p_conveyor_asset->Clean();
	}

	// Gets all spawner
	auto* p_spawner_1 = CGameObject::FindWithTag("C1");
	auto* p_spawner_2 = CGameObject::FindWithTag("C2");
	auto* p_spawner_3 = CGameObject::FindWithTag("C3");
	auto* p_spawner_4 = CGameObject::FindWithTag("C4");

	if (p_spawner_1) p_spawner_1->GetComponent<S_AssetSpawner>()->StartClean();
	if (p_spawner_2) p_spawner_2->GetComponent<S_AssetSpawner>()->StartClean();
	if (p_spawner_3) p_spawner_3->GetComponent<S_AssetSpawner>()->StartClean();
	if (p_spawner_4) p_spawner_4->GetComponent<S_AssetSpawner>()->StartClean();

	mp_prompt->LogMessage("ALL CB CLEANED UP");
}

void S_GameManager::StopCleanAllCB()
{
	m_clean_up_elapsed   = 0.0f;
	m_clean_up_activated = false;

	// Gets all conveyors
	auto conveyors = CGameObject::FindGameObjectsWithTag("Conveyor");

	for (auto* p_conveyor : conveyors)
	{
		auto* p_controller = p_conveyor->GetComponent<S_ConveyorController>();

		if (p_controller)
			p_controller->StopClean();
	}

	// Gets all spawner
	auto* p_spawner_1 = CGameObject::FindWithTag("C1");
	auto* p_spawner_2 = CGameObject::FindWithTag("C2");
	auto* p_spawner_3 = CGameObject::FindWithTag("C3");
	auto* p_spawner_4 = CGameObject::FindWithTag("C4");

	if (p_spawner_1) p_spawner_1->GetComponent<S_AssetSpawner>()->StopClean();
	if (p_spawner_2) p_spawner_2->GetComponent<S_AssetSpawner>()->StopClean();
	if (p_spawner_3) p_spawner_3->GetComponent<S_AssetSpawner>()->StopClean();
	if (p_spawner_4) p_spawner_4->GetComponent<S_AssetSpawner>()->StopClean();

	mp_prompt->LogMessage("CB CLEAN UP FINISHED");
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
	mp_prompt->LogMessage("START HACKING");
	mp_prompt->LogMessage("LOGOUT");
	mp_prompt->LogMessage("DOOR CODES : D1, D2, D3");
	mp_prompt->LogMessage("CB CODES : CB1, CB2, CB3, CB4");
	mp_prompt->LogMessage("USE \"START HACKING\" TO START");
}

void S_GameManager::StartHacking()
{
	if (m_startedHacking)
	{
		mp_prompt->LogMessage("ALREADY HACKING");
	}
	
	auto* p_manager_go = CGameObject::FindWithTag("Spawner_manager");

	if (p_manager_go)
	{
		auto* p_manager = p_manager_go->GetComponent<S_SpawnerManager>();
		if (p_manager)
		{
			p_manager->DispatchWaves();
		}
	}

	mp_prompt->LogMessage("STARTING HACKING");
	m_startedHacking = true;
}

void S_GameManager::Logout()
{
	Sdk::Application::Exit();
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

void S_GameManager::GameOver()
{
	mp_prompt->OpenPrompt();
	mp_prompt->LogMessage("F#TAàAL E&RORR : FLOçPY DIùK OOV\\RFLO|ING");
	mp_prompt->LogMessage("SY[STèM CRAAA'A{SHI@NG");
	//TODO wait for 2 seconds and crash the game
	while (true) {} // OR CRASH THE GAME LIKE THAT YEAH !
}

void S_GameManager::GameWon()
{
	mp_prompt->OpenPrompt();
	mp_prompt->LogMessage("INCOMING EXTERNal MESSAGE :");
	mp_prompt->LogMessage("WELL DONE DUDE !");
	mp_prompt->LogMessage("THE PRODUCTION IS OVER AND THE FLOPPY IS FINE");
	mp_prompt->LogMessage("YOU CAN USE  \"LOGOUT\" TO DISCONNECT FROM THE SYSTEM");
	mp_prompt->LogMessage("SEE YOU !");
	mp_prompt->LogMessage("[END OF MESSAGE]");
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
