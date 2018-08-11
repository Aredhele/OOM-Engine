/// \file       Prefab.cpp
/// \date       08/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#include "Game/Prefab/Prefab.hpp"

// Game scritps
#include "Game/Floppy/S_Floppy.hpp"
#include "Game/Floppy/S_GameManager.hpp"
#include "Game/Floppy/Player/S_Player.hpp"
#include "Game/Floppy/Asset/S_SpawnerManager.hpp"
#include "Game/Floppy/Prompt/S_CommandPrompt.hpp"
#include "Game/Floppy/Controller/S_DoorController.hpp"
#include "Game/Floppy/Controller/S_AlarmController.hpp"
#include "Game/Floppy/Controller/S_ConveyorController.hpp"

namespace Prefab
{
	
void CreatePlayer()
{
	auto* p_game_object = Sdk::GameObject::CreateFreeCamera();

	// Player script
	p_game_object->AddComponent<S_Player>();

	p_game_object->SetTag ("MainCamera"); ///< Required by the camera
	p_game_object->SetName("Player");     ///< Required to find the player

	p_game_object->GetTransform().SetPosition   (15.0f, 0.0f, 16.0f);
	p_game_object->GetTransform().SetEulerAngles(0.0f, 0.0f,  90.0f);

	auto* p_camera_script = p_game_object->GetComponent<S_Camera>();
	p_camera_script->SetClearColor(glm::vec3(0.05f, 0.0f, 0.0f));
}

void CreateGlobalLighting()
{
	auto* p_game_object = Sdk::GameObject::CreateDirectionalLight();

	p_game_object->SetTag ("Light");
	p_game_object->SetName("Directional_Light");
	p_game_object->GetTransform().SetPosition(0.0f, 0.0f, 10.0f);

	auto* p_light = p_game_object->GetComponent<S_DirectionalLight>();

	p_light->SetLightIntensity(0.3f);
	p_light->SetAmbientIntensity(0.2f);
	p_light->SetLightColor(glm::vec3(0.8f, 0.6f, 0.6f));

	Sdk::Render::EnablePostEffect(EPostEffect::Fog);
	Sdk::Render::EnablePostEffect(EPostEffect::Vignette);
}

void CreateStaticEnvironment()
{	
	auto* p_plane       = Sdk::GameObject::CreateGameObjectFromMesh("Plane");
	auto* p_panels      = Sdk::GameObject::CreateGameObjectFromMesh("Panels");
	auto* p_row_plane   = Sdk::GameObject::CreateGameObjectFromMesh("Rows_Plane");
	auto* p_grey_chips  = Sdk::GameObject::CreateGameObjectFromMesh("Grey_Chips");
	auto* p_center_zone = Sdk::GameObject::CreateGameObjectFromMesh("CenterZone");
	auto* p_static_trim = Sdk::GameObject::CreateGameObjectFromMesh("Static_Trim");

	// Resetting names to avoid issues if 
	// their true name change withing the .obj file
	p_plane->SetName      ("Plane");
	p_panels->SetName     ("Panels");
	p_row_plane->SetName  ("Row_Plane");
	p_grey_chips->SetName ("Grey_Chips");
	p_center_zone->SetName("Center_Zone");
	p_static_trim->SetName("Static_Zone");

	p_plane->SetTag      ("Static");
	p_panels->SetTag     ("Static");
	p_row_plane->SetTag  ("Static");
	p_grey_chips->SetTag ("Static");
	p_center_zone->SetTag("Static");
	p_static_trim->SetTag("Static");
}

void CreateAlarms()
{
	auto* p_alarm_on  = Sdk::GameObject::CreateGameObjectFromMesh("SuperAsset_Alarm_ON" );
	auto* p_alarm_off = Sdk::GameObject::CreateGameObjectFromMesh("SuperAsset_Alarm_OFF");

	p_alarm_on->SetName ("Alarm_On");
	p_alarm_off->SetName("Alarm_Off");

	p_alarm_on->SetTag ("Alarm");
	p_alarm_off->SetTag("Alarm");
}

void CreateDoors()
{
	// Door blocks
	auto* p_door_block_1 = Sdk::GameObject::CreateGameObjectFromMesh("Door_Block_01");
	auto* p_door_block_2 = Sdk::GameObject::CreateGameObjectFromMesh("Door_Block_02");
	auto* p_door_block_3 = Sdk::GameObject::CreateGameObjectFromMesh("Door_Block_03");

	p_door_block_1->SetName("Door_Block_R1");
	p_door_block_2->SetName("Door_Block_R3");
	p_door_block_3->SetName("Door_Block_R2");

	p_door_block_1->SetTag("Door_Block");
	p_door_block_2->SetTag("Door_Block");
	p_door_block_3->SetTag("Door_Block");

	p_door_block_1->AddComponent<S_DoorController>();
	p_door_block_2->AddComponent<S_DoorController>();
	p_door_block_3->AddComponent<S_DoorController>();

	// Door frames on
	auto* p_door_01_on = Sdk::GameObject::CreateGameObjectFromMesh("Porte_01_ON");
	auto* p_door_02_on = Sdk::GameObject::CreateGameObjectFromMesh("Porte_02_ON");
	auto* p_door_03_on = Sdk::GameObject::CreateGameObjectFromMesh("Porte_03_ON");
	auto* p_door_04_on = Sdk::GameObject::CreateGameObjectFromMesh("Porte_04_ON");
	auto* p_door_05_on = Sdk::GameObject::CreateGameObjectFromMesh("Porte_05_ON");
	auto* p_door_06_on = Sdk::GameObject::CreateGameObjectFromMesh("Porte_06_ON");
	auto* p_door_07_on = Sdk::GameObject::CreateGameObjectFromMesh("Porte_07_ON");

	p_door_01_on->SetName("Door_01_On");
	p_door_02_on->SetName("Door_02_On");
	p_door_03_on->SetName("Door_03_On");
	p_door_04_on->SetName("Door_04_On");
	p_door_05_on->SetName("Door_05_On");
	p_door_06_on->SetName("Door_06_On");
	p_door_07_on->SetName("Door_07_On");

	p_door_01_on->SetTag("Door_On");
	p_door_02_on->SetTag("Door_On");
	p_door_03_on->SetTag("Door_On");
	p_door_04_on->SetTag("Door_On");
	p_door_05_on->SetTag("Door_On");
	p_door_06_on->SetTag("Door_On");
	p_door_07_on->SetTag("Door_On");

	// Door frames off
	auto* p_door_01_off = Sdk::GameObject::CreateGameObjectFromMesh("Porte_01_OFF");
	auto* p_door_02_off = Sdk::GameObject::CreateGameObjectFromMesh("Porte_02_OFF");
	auto* p_door_03_off = Sdk::GameObject::CreateGameObjectFromMesh("Porte_03_OFF");
	auto* p_door_04_off = Sdk::GameObject::CreateGameObjectFromMesh("Porte_04_OFF");
	auto* p_door_05_off = Sdk::GameObject::CreateGameObjectFromMesh("Porte_05_OFF");
	auto* p_door_06_off = Sdk::GameObject::CreateGameObjectFromMesh("Porte_06_OFF");
	auto* p_door_07_off = Sdk::GameObject::CreateGameObjectFromMesh("Porte_07_OFF");

	p_door_01_off->SetName("Door_01_Off");
	p_door_02_off->SetName("Door_02_Off");
	p_door_03_off->SetName("Door_03_Off");
	p_door_04_off->SetName("Door_04_Off");
	p_door_05_off->SetName("Door_05_Off");
	p_door_06_off->SetName("Door_06_Off");
	p_door_07_off->SetName("Door_07_Off");

	p_door_01_off->SetTag("Door_Off");
	p_door_02_off->SetTag("Door_Off");
	p_door_03_off->SetTag("Door_Off");
	p_door_04_off->SetTag("Door_Off");
	p_door_05_off->SetTag("Door_Off");
	p_door_06_off->SetTag("Door_Off");
	p_door_07_off->SetTag("Door_Off");

	auto* p_alarm_controller_1 = Sdk::GameObject::CreateEmpty();
	auto* p_alarm_controller_2 = Sdk::GameObject::CreateEmpty();
	auto* p_alarm_controller_3 = Sdk::GameObject::CreateEmpty();
	auto* p_alarm_controller_4 = Sdk::GameObject::CreateEmpty();
	auto* p_alarm_controller_5 = Sdk::GameObject::CreateEmpty();
	auto* p_alarm_controller_6 = Sdk::GameObject::CreateEmpty();
	auto* p_alarm_controller_7 = Sdk::GameObject::CreateEmpty();

	p_alarm_controller_1->SetTag("Alarm_controller_CB1");
	p_alarm_controller_2->SetTag("Alarm_controller_CB2");
	p_alarm_controller_4->SetTag("Alarm_controller_CB3");
	p_alarm_controller_6->SetTag("Alarm_controller_CB4");

	p_alarm_controller_3->SetTag("Alarm_controller_D2");
	p_alarm_controller_5->SetTag("Alarm_controller_D3");
	p_alarm_controller_7->SetTag("Alarm_controller_D1");

	auto* p_controller_1 = p_alarm_controller_1->AddComponent<S_AlarmController>();
	auto* p_controller_2 = p_alarm_controller_2->AddComponent<S_AlarmController>();
	auto* p_controller_4 = p_alarm_controller_4->AddComponent<S_AlarmController>();
	auto* p_controller_6 = p_alarm_controller_6->AddComponent<S_AlarmController>();
	auto* p_controller_3 = p_alarm_controller_3->AddComponent<S_AlarmController>();
	auto* p_controller_5 = p_alarm_controller_5->AddComponent<S_AlarmController>();
	auto* p_controller_7 = p_alarm_controller_7->AddComponent<S_AlarmController>();

	p_controller_1->SetTargetRenderer(p_door_01_on->GetComponent<CMeshRenderer>(), p_door_01_off->GetComponent<CMeshRenderer>());
	p_controller_2->SetTargetRenderer(p_door_02_on->GetComponent<CMeshRenderer>(), p_door_02_off->GetComponent<CMeshRenderer>());
	p_controller_4->SetTargetRenderer(p_door_04_on->GetComponent<CMeshRenderer>(), p_door_04_off->GetComponent<CMeshRenderer>());
	p_controller_6->SetTargetRenderer(p_door_06_on->GetComponent<CMeshRenderer>(), p_door_06_off->GetComponent<CMeshRenderer>());
	p_controller_3->SetTargetRenderer(p_door_03_on->GetComponent<CMeshRenderer>(), p_door_03_off->GetComponent<CMeshRenderer>());
	p_controller_5->SetTargetRenderer(p_door_05_on->GetComponent<CMeshRenderer>(), p_door_05_off->GetComponent<CMeshRenderer>());
	p_controller_7->SetTargetRenderer(p_door_07_on->GetComponent<CMeshRenderer>(), p_door_07_off->GetComponent<CMeshRenderer>());
}

void CreateConveyors()
{
	auto* p_conveyor_01 = Sdk::GameObject::CreateGameObjectFromMesh("Tapis_01");
	auto* p_conveyor_02 = Sdk::GameObject::CreateGameObjectFromMesh("Tapis_02");
	auto* p_conveyor_03 = Sdk::GameObject::CreateGameObjectFromMesh("Tapis_03");
	auto* p_conveyor_04 = Sdk::GameObject::CreateGameObjectFromMesh("Tapis_04");

	p_conveyor_01->SetName("Conveyor_C1");
	p_conveyor_02->SetName("Conveyor_C2");
	p_conveyor_03->SetName("Conveyor_C3");
	p_conveyor_04->SetName("Conveyor_C4");

	p_conveyor_01->SetTag("Conveyor");
	p_conveyor_02->SetTag("Conveyor");
	p_conveyor_03->SetTag("Conveyor");
	p_conveyor_04->SetTag("Conveyor");

	p_conveyor_01->AddComponent<S_ConveyorController>();
	p_conveyor_02->AddComponent<S_ConveyorController>();
	p_conveyor_03->AddComponent<S_ConveyorController>();
	p_conveyor_04->AddComponent<S_ConveyorController>();
}

void CreateGameManager()
{
	auto* p_game_object = Sdk::GameObject::CreateEmpty();

	p_game_object->SetTag("Game_Manager");
	p_game_object->SetName("Game_Manager");
	p_game_object->AddComponent<S_GameManager>();	
}

void CreateCommandPrompt()
{
	auto* p_game_object = Sdk::GameObject::CreateEmpty();

	p_game_object->SetTag("Prompt");
	p_game_object->SetName("Prompt");
	p_game_object->AddComponent<S_CommandPrompt>();
}

void CreateSpawnerManager()
{
	auto* p_game_object = Sdk::GameObject::CreateEmpty();
	auto* p_manager     = p_game_object->AddComponent<S_SpawnerManager>();

	p_game_object->SetTag("Spawner_manager");
	p_game_object->SetName("Spawner_manager");

	// Test
	//p_manager->RegisterAssetWave(5.0f, 8.0f, EAsset::BigAsset,      ESpawnZone::R2, "1111");
	//p_manager->RegisterAssetWave(6.0f, 5.0f, EAsset::BusAsset,		ESpawnZone::R3, "122112123");
	//p_manager->RegisterAssetWave(0.0f, 7.0f, EAsset::BusAsset,		ESpawnZone::R1, "111123123");
	//p_manager->RegisterAssetWave(3.0f, 3.0f, EAsset::ConveyorAsset, ESpawnZone::C1, "111222211");
	//p_manager->RegisterAssetWave(3.0f, 3.0f, EAsset::ConveyorAsset, ESpawnZone::C2, "111222211");
	//p_manager->RegisterAssetWave(3.0f, 3.0f, EAsset::ConveyorAsset, ESpawnZone::C3, "111222211");
	//p_manager->RegisterAssetWave(3.0f, 3.0f, EAsset::ConveyorAsset, ESpawnZone::C4, "111222211");
	//
	//p_manager->RegisterAssetWave(5.0f, 4.0f, EAsset::ConveyorAsset, ESpawnZone::C2, "212112113");
	//p_manager->RegisterAssetWave(7.0f, 2.0f, EAsset::ConveyorAsset, ESpawnZone::C3, "111211112");
	//p_manager->RegisterAssetWave(4.0f, 2.5f, EAsset::ConveyorAsset, ESpawnZone::C4, "111122311");

	// Introduction with small waves
	p_manager->RegisterAssetWave(1.0f, 2.0f, EAsset::BusAsset, ESpawnZone::R2, "112233");
	p_manager->RegisterAssetWave(13.0f, 2.0f, EAsset::ConveyorAsset, ESpawnZone::C1, "112233"); 
	// 25 s

	p_manager->RegisterAssetWave(25.0f, 2.0f, EAsset::BusAsset, ESpawnZone::R1, "12131213");
	p_manager->RegisterAssetWave(30.0f, 2.0f, EAsset::BusAsset, ESpawnZone::R3, "1212113");
	p_manager->RegisterAssetWave(33.0f, 2.0f, EAsset::BusAsset, ESpawnZone::R2, "121213");
	// 39s

	p_manager->RegisterAssetWave(39.0f, 2.0f, EAsset::ConveyorAsset, ESpawnZone::C2, "12131213");
	p_manager->RegisterAssetWave(44.0f, 2.0f, EAsset::ConveyorAsset, ESpawnZone::C1, "12131213");
	p_manager->RegisterAssetWave(48.0f, 2.0f, EAsset::ConveyorAsset, ESpawnZone::C3, "12131213");
	p_manager->RegisterAssetWave(52.0f, 2.0f, EAsset::ConveyorAsset, ESpawnZone::C4, "12131213");
	// 70s

	p_manager->RegisterAssetWave(70.0f, 2.0f, EAsset::ConveyorAsset, ESpawnZone::C2, "12131213");
	p_manager->RegisterAssetWave(74.0F, 2.0f, EAsset::BusAsset, ESpawnZone::R1, "12131213");
	p_manager->RegisterAssetWave(78.0f, 2.0f, EAsset::ConveyorAsset, ESpawnZone::C1, "12131213");
	p_manager->RegisterAssetWave(83.0f, 2.0f, EAsset::BusAsset, ESpawnZone::R3, "1212113");
	// 97s

	p_manager->RegisterAssetWave(97.0f, 2.0f, EAsset::ConveyorAsset, ESpawnZone::C1, "1213112131");
	p_manager->RegisterAssetWave(103.0F, 2.0f, EAsset::BusAsset, ESpawnZone::R2, "1211312131");
	p_manager->RegisterAssetWave(107.0f, 2.0f, EAsset::ConveyorAsset, ESpawnZone::C3, "121131213");
	p_manager->RegisterAssetWave(113.0f, 2.0f, EAsset::BusAsset, ESpawnZone::R1, "12121213");
	p_manager->RegisterAssetWave(118.0f, 2.0f, EAsset::BusAsset, ESpawnZone::R3, "121321213");
	p_manager->RegisterAssetWave(123.0f, 2.0f, EAsset::ConveyorAsset, ESpawnZone::C2, "1213213");
	p_manager->RegisterAssetWave(127.0f, 2.0f, EAsset::ConveyorAsset, ESpawnZone::C4, "12213");
	// 137s

	p_manager->RegisterAssetWave(138, 2.0f, EAsset::ConveyorAsset, ESpawnZone::C1, "12131121231");
	p_manager->RegisterAssetWave(138, 2.0f, EAsset::BusAsset, ESpawnZone::R2, "1211312131");
	p_manager->RegisterAssetWave(138.0f, 2.0f, EAsset::ConveyorAsset, ESpawnZone::C3, "121131213");
	p_manager->RegisterAssetWave(138.0f, 2.0f, EAsset::BusAsset, ESpawnZone::R1, "1132113");
	p_manager->RegisterAssetWave(138.0f, 2.0f, EAsset::BusAsset, ESpawnZone::R3, "1213212131");
	p_manager->RegisterAssetWave(138.0f, 2.0f, EAsset::ConveyorAsset, ESpawnZone::C2, "121321213");
	p_manager->RegisterAssetWave(138.0f, 2.0f, EAsset::ConveyorAsset, ESpawnZone::C4, "121213");
	// 160s

	p_manager->RegisterAssetWave(162.0f, 2.0f, EAsset::BigAsset, ESpawnZone::R1, "1");
	// 168s

	p_manager->RegisterAssetWave(168.0f, 2.0f, EAsset::ConveyorAsset, ESpawnZone::C3, "12131213");
	p_manager->RegisterAssetWave(174.0, 2.0f, EAsset::BusAsset, ESpawnZone::R1, "12131213");
	p_manager->RegisterAssetWave(177.0f, 2.0f, EAsset::BigAsset, ESpawnZone::R2, "1");
	p_manager->RegisterAssetWave(180.0f, 2.0f, EAsset::ConveyorAsset, ESpawnZone::C1, "12131213");
	p_manager->RegisterAssetWave(183.0f, 2.0f, EAsset::BusAsset, ESpawnZone::R3, "1212113");
	// 197s
	
	p_manager->RegisterAssetWave(197.0f, 2.0f, EAsset::ConveyorAsset, ESpawnZone::C1, "1213112131");
	p_manager->RegisterAssetWave(200.0F, 2.0f, EAsset::BusAsset, ESpawnZone::R2, "1211312131");
	p_manager->RegisterAssetWave(203.0f, 2.0f, EAsset::ConveyorAsset, ESpawnZone::C3, "121131213");
	p_manager->RegisterAssetWave(205.0f, 2.0f, EAsset::BigAsset, ESpawnZone::R3, "1");
	p_manager->RegisterAssetWave(208.0f, 2.0f, EAsset::BusAsset, ESpawnZone::R1, "12121213");
	p_manager->RegisterAssetWave(211.0f, 2.0f, EAsset::BusAsset, ESpawnZone::R3, "121321213");
	p_manager->RegisterAssetWave(214.0f, 2.0f, EAsset::BigAsset, ESpawnZone::R2, "1");
	p_manager->RegisterAssetWave(217.0f, 2.0f, EAsset::ConveyorAsset, ESpawnZone::C2, "1213213");
	p_manager->RegisterAssetWave(220.0f, 2.0f, EAsset::ConveyorAsset, ESpawnZone::C4, "12213");
	// 230s

}

void CreateFloppy()
{
	auto* p_game_object = Sdk::GameObject::CreateGameObjectFromMesh("Floppy");

	p_game_object->SetTag("Floppy");
	p_game_object->SetName("Floppy");
	p_game_object->AddComponent<S_Floppy>();

	p_game_object->GetTransform().SetScale   (4.0f, 4.0f, 4.0f);
	p_game_object->GetTransform().SetPosition(0.0f, 0.0f, 8.0f);
}

}


