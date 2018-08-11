/// \file       S_GameManager.hpp
/// \date       08/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_S_GAME_MANAGER_HPP__
#define OOM_ENGINE_S_GAME_MANAGER_HPP__

#include "SDK/SDK.hpp"
#include "Game/Floppy/Asset/S_AssetSpawner.hpp"
#include "Prompt/Capcha.hpp"
#include "S_Floppy.hpp"

// Forward declaration
class S_CommandPrompt;

class S_GameManager : public CBehavior
{
public:

	void Awake     () final;	
	void Start     () final;
	void Update    () final;
	void OnDestroy () final;

	void StartConveyorBelt  (ESpawnZone zone);
	void StopConveyorBelt   (ESpawnZone zone);
	void OpenDoor	        (ESpawnZone zone);
	void CloseDoor		    (ESpawnZone zone);
	void TryActivateFirewall();
	void ActivateFireWall   ();
	void DeactivateFireWall();
	void TryCleanAllCB();
	void CleanAllCB();
	void StopCleanAllCB();
	void ShowHelp();
	void StartHacking();
	void Logout();
	void ProcessUnknownCommand(const CString& command);

	void GameOver();
	void GameWon();

private:

	void DoCapcha			();
	bool CapchaTestPassed	(CString answer);

private:

	S_Floppy*        mp_floppy = nullptr;
	S_CommandPrompt*    mp_prompt = nullptr;
	S_CameraController* mp_camera = nullptr;

	float m_key_delay;
	float m_key_elapsed;

	// Game logic
	bool m_door_state    [3];
	bool m_conveyor_state[4];

	// Firewall
	bool  m_firewall_activated;
	float m_firewall_cooldown;
	float m_firewall_duration;
	float m_firewall_elapsed;

	// Cleanup
	bool  m_clean_up_activated;
	float m_clean_up_cooldown;
	float m_clean_up_duration;
	float m_clean_up_elapsed;

	// Flags
	bool m_tried_activate_firewall = false;
	bool m_tried_clean_all_CB = false;
	bool m_on_capcha = false;
	bool m_startedHacking = false;
	bool m_game_over = false;

	Game::Capcha m_current_capcha;
};

#endif // !OOM_ENGINE_S_GAME_MANAGER_HPP__
