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

	p_light->SetLightIntensity(0.6f);
	p_light->SetAmbientIntensity(0.35f);
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
	auto* p_super_alarm = Sdk::GameObject::CreateEmpty();
	auto* p_alarm_on    = Sdk::GameObject::CreateGameObjectFromMesh("SuperAsset_Alarm_ON" );
	auto* p_alarm_off   = Sdk::GameObject::CreateGameObjectFromMesh("SuperAsset_Alarm_OFF");

	p_alarm_on->SetName ("Alarm_On");
	p_alarm_off->SetName("Alarm_Off");

	p_alarm_on->SetTag ("Alarm");
	p_alarm_off->SetTag("Alarm");

	p_super_alarm->SetTag("Super_alarm_controller");
	auto* p_super_alarm_controller = p_super_alarm->AddComponent<S_AlarmController>();

	p_super_alarm_controller->SetTargetRenderer(p_alarm_on->GetComponent<CMeshRenderer>(), p_alarm_off->GetComponent<CMeshRenderer>());
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

	p_alarm_controller_1->GetTransform().SetPosition(-27.0f, -19.0f,  4.0f);
	p_alarm_controller_2->GetTransform().SetPosition(-27.0f,  19.0f,  4.0f);
	p_alarm_controller_4->GetTransform().SetPosition( 26.0f,  20.0f,  4.0f);
	p_alarm_controller_6->GetTransform().SetPosition( 20.0f, -26.0f,  4.0f);
	p_alarm_controller_3->GetTransform().SetPosition( 0.0f,   30.0f,  4.0f);
	p_alarm_controller_7->GetTransform().SetPosition( 0.0f,  -30.0f,  4.0f);
	p_alarm_controller_5->GetTransform().SetPosition( 30.0f,   0.0f,  4.0f);

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

	// Notes
	// Big assets put 35 s to arrive on floppy
	// A normal wave make 24s to spawn
	// The first arrives after 22s in a normal wave

	CString normal_wave = "1112123333";

	// Introduction with small waves
	p_manager->RegisterAssetWave(1.0f, 3.0f, EAsset::BusAsset, ESpawnZone::R1, normal_wave);
	p_manager->RegisterAssetWave(15.0f, 3.5f, EAsset::ConveyorAsset, ESpawnZone::C1, normal_wave);

	p_manager->RegisterAssetWave(46.0f, 3.0f, EAsset::BusAsset, ESpawnZone::R2, normal_wave);
	p_manager->RegisterAssetWave(60.0f, 3.5f, EAsset::ConveyorAsset, ESpawnZone::C2, normal_wave);

	p_manager->RegisterAssetWave(68.0f, 3.0f, EAsset::BusAsset, ESpawnZone::R3, normal_wave);
	p_manager->RegisterAssetWave(72.0f, 3.5f, EAsset::ConveyorAsset, ESpawnZone::C3, normal_wave);

	p_manager->RegisterAssetWave(104.0f, 3.0f, EAsset::BigAsset, ESpawnZone::R3, "1");

	p_manager->RegisterAssetWave(120.0f, 3.0f, EAsset::BusAsset, ESpawnZone::R1, normal_wave);
	p_manager->RegisterAssetWave(130.0f, 3.0f, EAsset::BigAsset, ESpawnZone::R1, "1");
	p_manager->RegisterAssetWave(137.0f, 3.5f, EAsset::ConveyorAsset, ESpawnZone::C1, normal_wave);

	p_manager->RegisterAssetWave(142.0f, 3.0f, EAsset::BusAsset, ESpawnZone::R3, normal_wave);
	p_manager->RegisterAssetWave(148.0f, 3.0f, EAsset::BigAsset, ESpawnZone::R2, "1");
	p_manager->RegisterAssetWave(155.0f, 3.5f, EAsset::ConveyorAsset, ESpawnZone::C2, normal_wave);

	p_manager->RegisterAssetWave(164.0f, 3.0f, EAsset::BusAsset, ESpawnZone::R2, normal_wave);
	p_manager->RegisterAssetWave(168.0f, 3.0f, EAsset::BigAsset, ESpawnZone::R2, "1");
	p_manager->RegisterAssetWave(175.0f, 3.5f, EAsset::ConveyorAsset, ESpawnZone::C3, normal_wave);



	p_manager->RegisterAssetWave(200.0f, 3.0f, EAsset::BusAsset, ESpawnZone::R1, normal_wave);
	p_manager->RegisterAssetWave(205.0f, 3.5f, EAsset::ConveyorAsset, ESpawnZone::C2, normal_wave);
	p_manager->RegisterAssetWave(213.0f, 3.0f, EAsset::BusAsset, ESpawnZone::R3, normal_wave);
	p_manager->RegisterAssetWave(217.0f, 3.0f, EAsset::BigAsset, ESpawnZone::R2, "1");
	p_manager->RegisterAssetWave(220.0f, 3.5f, EAsset::ConveyorAsset, ESpawnZone::C1, normal_wave);
	p_manager->RegisterAssetWave(230.0f, 3.0f, EAsset::BusAsset, ESpawnZone::R2, normal_wave);
	p_manager->RegisterAssetWave(237.0f, 3.5f, EAsset::ConveyorAsset, ESpawnZone::C3, normal_wave);
	p_manager->RegisterAssetWave(249.0f, 3.5f, EAsset::ConveyorAsset, ESpawnZone::C4, normal_wave);

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


