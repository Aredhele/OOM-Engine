/// \file       Game.cpp
/// \date       01/08/2018
/// \project    OOM-Engine
/// \package    Game
/// \author     Vincent STEHLY--CALISTO

#include "SDK/SDK.hpp"
#include "Scene/Hook.hpp"
#include "Scene/CScene.hpp"

// User script
#include "Game/S_CameraRotator.hpp"

// Temporary
CAudioBuffer buffer_1;
CAudioBuffer buffer_2;

void LoadScene()
{
	CScene::LoadScene(CScene::EScene::DemoAudio);
}

void LoadGameScene()
{
	// TODO
}

void LoadDemoSceneAudio()
{
	// Settings
	Sdk::Render::EnablePostProcessing();
	Sdk::Render::EnablePostEffect(EPostEffect::FXAA);

	Sdk::Debug::EnableGizmo(EGizmo::Ray);
	Sdk::Debug::EnableGizmo(EGizmo::Box);
	Sdk::Debug::EnableGizmo(EGizmo::Axis);
	Sdk::Debug::EnableGizmo(EGizmo::Line);
	Sdk::Debug::EnableGizmo(EGizmo::Grid);
	Sdk::Debug::EnableGizmo(EGizmo::AudioSource);

	auto* p_camera = Sdk::GameObject::CreateFreeCamera();

	p_camera->AddComponent   <S_CameraRotator>();
	p_camera->RemoveComponent<S_CameraController>();

	// Loads 2 sounds from a file
	buffer_1.LoadFromFile("Resources/Music/Town-Academy.ogg");
	buffer_2.LoadFromFile("Resources/Music/Town-Dungeon.ogg");

	// Creates 2 game objets with audio source attatched
	auto* p_source_1_go = Sdk::GameObject::CreateAudioSource3D();
	auto* p_source_2_go = Sdk::GameObject::CreateAudioSource3D();

	p_source_1_go->GetTransform().SetPosition(-5.0f, 0.0f, 0.0f);
	p_source_2_go->GetTransform().SetPosition( 5.0f, 0.0f, 0.0f);

	// Gets the audio components
	auto* p_source_1 = p_source_1_go->GetComponent<CAudioSource3D>();
	auto* p_source_2 = p_source_2_go->GetComponent<CAudioSource3D>();

	// Gives to source the audio buffer resource
	p_source_1->SetAudioBuffer(&buffer_1);
	p_source_2->SetAudioBuffer(&buffer_2);

	p_source_1->SetMinDistance(2.0f);
	p_source_1->SetMaxDistance(10.0f);
	p_source_1->Play();

	p_source_2->SetMinDistance(3.0f);
	p_source_2->SetMaxDistance(10.0f);
	p_source_2->Play();
}

void LoadDemoScenePhysics()
{
	// TODO
}