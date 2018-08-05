#include "Game/Prefabs.hpp"

CGameObject& Game::Prefabs::CreatePlayer() 
{
	CGameObject& player = *CEngine::Instantiate();

	// Add the camera component
	bool b_first_camera = (CEngine::FindWithTag("MainCamera") == nullptr);
	player.AddComponent<S_Camera>();
	player.SetTag(b_first_camera ? "MainCamera" : "");
	player.AddComponent<CAudioListener3D>();
	
	// Add controlS
	player.AddComponent<S_CameraController>();



	return player;
}