/// \file       S_GameManager.hpp
/// \date       08/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_S_GAME_MANAGER_HPP__
#define OOM_ENGINE_S_GAME_MANAGER_HPP__

#include "SDK/SDK.hpp"
#include "Game/Floppy/Asset/S_AssetSpawner.hpp"

// Forward declaration
class S_CommandPrompt;

class S_GameManager : public CBehavior
{
public:

	void Awake     () final;	
	void Start     () final;
	void Update    () final;
	void OnDestroy () final;

public:

	void StartConveyorBelt(ESpawnZone zone);
	void StopConveyorBelt (ESpawnZone zone);
	void OpenDoor	      (ESpawnZone zone);
	void CloseDoor		  (ESpawnZone zone);

private:

	CGameObject*        mp_floppy = nullptr;
	S_CommandPrompt*    mp_prompt = nullptr;
	S_CameraController* mp_camera = nullptr;

	float		     m_key_delay;
	float		     m_key_elapsed;

	// Game logic
	bool			 m_conveyor_state[4];
};

#endif // !OOM_ENGINE_S_GAME_MANAGER_HPP__
