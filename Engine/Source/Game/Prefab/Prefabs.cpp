#include "Game/Prefab/Prefabs.hpp"

CGameObject& Game::Prefabs::CreatePlayer() 
{
	/*auto& player = *CEngine::Instantiate();

	// Add the camera component
	bool b_first_camera = (CEngine::FindWithTag("MainCamera") == nullptr);
	player.AddComponent<S_Camera>();
	player.SetTag(b_first_camera ? "MainCamera" : "");
	player.AddComponent<CAudioListener3D>();
	
	// Add controlS
	player.AddComponent<S_CameraController>();



	return player;*/
	return *Sdk::GameObject::CreateEmpty();
}

CGameObject& Game::Prefabs::CreateCB_Asset(Asset::Size size)
{
	auto& go = Game::Prefabs::priv::CreateAsset(size);
	return go;

}

CGameObject& Game::Prefabs::CreateRoadAsset(Asset::Size size)
{
	auto& go = Game::Prefabs::priv::CreateAsset(size);
	return go;
}

CGameObject& Game::Prefabs::CreateBigAsset()
{
	auto& go = Game::Prefabs::priv::CreateAsset(Asset::Size::Heavy);
	return go;
}

CGameObject& Game::Prefabs::priv::CreateAsset(Asset::Size size)
{
	/*auto& go = *CEngine::Instantiate();
	auto& asset = *go.AddComponent<Game::Asset>();
	go.AddComponent<CRigidBody>();
	go.AddComponent<CBoxCollider>();
	asset.init(size);
	switch(size)
	{
	case Asset::Size::Light:
		go.GetTransform().SetScale(1, 1, 1);
		break;
	case Asset::Size::Standard:
		go.GetTransform().SetScale(1.5, 1.5, 1.5);
		break;
	case Asset::Size::Heavy:
		go.GetTransform().SetScale(2, 2, 2);
		break;
	}	
	return go;*/
	return *Sdk::GameObject::CreateEmpty();
}