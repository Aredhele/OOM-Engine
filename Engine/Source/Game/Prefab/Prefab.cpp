/// \file       Prefab.cpp
/// \date       08/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#include "Game/Prefab/Prefab.hpp"

// Game scritps
#include "Game/Floppy/S_Floppy.hpp"
#include "Game/Floppy/S_GameManager.hpp"
#include "Game/Floppy/Asset/S_SpawnerManager.hpp"

namespace Prefab
{
	
void CreatePlayer()
{
	auto* p_game_object = Sdk::GameObject::CreateFreeCamera();

	p_game_object->SetTag ("MainCamera"); ///< Required by the camera
	p_game_object->SetName("Player");     ///< Required to find the player
}

void CreateGlobalLighting()
{
	auto* p_game_object = Sdk::GameObject::CreateDirectionalLight();

	p_game_object->SetTag ("Light");
	p_game_object->SetName("Directional_Light");
	p_game_object->GetTransform().SetPosition(0.0f, 0.0f, 10.0f);
}

void CreateStaticEnvironment()
{	
	auto* p_plane       = Sdk::GameObject::CreateGameObjectFromMesh("Plane");
	auto* p_panels      = Sdk::GameObject::CreateGameObjectFromMesh("Panels");
	auto* p_grey_chips  = Sdk::GameObject::CreateGameObjectFromMesh("Grey_Chips");
	auto* p_center_zone = Sdk::GameObject::CreateGameObjectFromMesh("CenterZone");
	auto* p_static_trim = Sdk::GameObject::CreateGameObjectFromMesh("Static_Trim");

	// Resetting names to avoid issues if 
	// their true name change withing the .obj file
	p_plane->SetName      ("Plane");
	p_panels->SetName     ("Panels");
	p_grey_chips->SetName ("Grey_Chips");
	p_center_zone->SetName("Center_Zone");
	p_static_trim->SetName("Static_Zone");

	p_plane->SetTag      ("Static");
	p_panels->SetTag     ("Static");
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

	p_door_block_1->SetName("Door_Block_01");
	p_door_block_2->SetName("Door_Block_02");
	p_door_block_3->SetName("Door_Block_03");

	p_door_block_1->SetTag("Door_Block");
	p_door_block_2->SetTag("Door_Block");
	p_door_block_3->SetTag("Door_Block");

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
}

void CreateConveyors()
{
	auto* p_conveyor_01 = Sdk::GameObject::CreateGameObjectFromMesh("Tapis_01");
	auto* p_conveyor_02 = Sdk::GameObject::CreateGameObjectFromMesh("Tapis_02");
	auto* p_conveyor_03 = Sdk::GameObject::CreateGameObjectFromMesh("Tapis_03");
	auto* p_conveyor_04 = Sdk::GameObject::CreateGameObjectFromMesh("Tapis_04");

	p_conveyor_01->SetName("Conveyor_01");
	p_conveyor_02->SetName("Conveyor_02");
	p_conveyor_03->SetName("Conveyor_03");
	p_conveyor_04->SetName("Conveyor_04");

	p_conveyor_01->SetTag("Conveyor");
	p_conveyor_02->SetTag("Conveyor");
	p_conveyor_03->SetTag("Conveyor");
	p_conveyor_04->SetTag("Conveyor");
}

void CreateGameManager()
{
	auto* p_game_object = Sdk::GameObject::CreateEmpty();

	p_game_object->SetTag("Game_Manager");
	p_game_object->SetName("Game_Manager");
	p_game_object->AddComponent<S_GameManager>();	
}

void CreateSpawnerManager()
{
	auto* p_game_object = Sdk::GameObject::CreateEmpty();
	auto* p_manager     = p_game_object->AddComponent<S_SpawnerManager>();

	p_game_object->SetTag("Spawner_manager");
	p_game_object->SetName("Spawner_manager");

	// Test
	p_manager->RegisterAssetWave(5.0f, 8.0f, EAsset::BigAsset,      ESpawnZone::R2, "1111");
	p_manager->RegisterAssetWave(6.0f, 5.0f, EAsset::BusAsset,		ESpawnZone::R3, "122112123");
	p_manager->RegisterAssetWave(6.0f, 7.0f, EAsset::BusAsset,		ESpawnZone::R1, "111123123");
	p_manager->RegisterAssetWave(3.0f, 3.0f, EAsset::ConveyorAsset, ESpawnZone::C1, "111222211");
	p_manager->RegisterAssetWave(3.0f, 3.0f, EAsset::ConveyorAsset, ESpawnZone::C2, "111222211");
	p_manager->RegisterAssetWave(3.0f, 3.0f, EAsset::ConveyorAsset, ESpawnZone::C3, "111222211");
	p_manager->RegisterAssetWave(3.0f, 3.0f, EAsset::ConveyorAsset, ESpawnZone::C4, "111222211");

	p_manager->RegisterAssetWave(5.0f, 4.0f, EAsset::ConveyorAsset, ESpawnZone::C2, "212112113");
	p_manager->RegisterAssetWave(7.0f, 2.0f, EAsset::ConveyorAsset, ESpawnZone::C3, "111211112");
	p_manager->RegisterAssetWave(4.0f, 2.5f, EAsset::ConveyorAsset, ESpawnZone::C4, "111122311");
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


