/// \file       Game.cpp
/// \date       01/08/2018
/// \project    OOM-Engine
/// \package    Game
/// \author     Vincent STEHLY--CALISTO

#include "SDK/SDK.hpp"
#include "Scene/Hook.hpp"
#include "Scene/CScene.hpp"

// Game include
#include "Game/Prefabs.hpp"

// Temporary
CAudioBuffer buffer_1;
CAudioBuffer buffer_2;

void LoadScene()
{
	CScene::LoadScene(CScene::EScene::DemoScreenSpaceUI);
}

void LoadGameScene()
{
	Sdk::Debug::EnableGizmo(EGizmo::Ray);
	Sdk::Debug::EnableGizmo(EGizmo::Box);
	Sdk::Debug::EnableGizmo(EGizmo::Axis);
	Sdk::Debug::EnableGizmo(EGizmo::Line);
	Sdk::Debug::EnableGizmo(EGizmo::Grid);
	Sdk::Debug::EnableGizmo(EGizmo::AudioSource);

	auto& player = Game::Prefabs::CreatePlayer();
}

void LoadDemoSceneAudio()
{
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
	Sdk::Render::EnablePostProcessing();
	Sdk::Render::EnablePostEffect(EPostEffect::FXAA);

	Sdk::Debug::EnableGizmo(EGizmo::Ray);
	Sdk::Debug::EnableGizmo(EGizmo::Box);
	Sdk::Debug::EnableGizmo(EGizmo::Axis);
	Sdk::Debug::EnableGizmo(EGizmo::Line);
	Sdk::Debug::EnableGizmo(EGizmo::Grid);
	Sdk::Debug::EnableGizmo(EGizmo::Transform);

	Sdk::GameObject::CreateDirectionalLight();

	auto* p_camera = Sdk::GameObject::CreateFreeCamera();
	p_camera->GetTransform().SetPosition(4.0f, 4.0f, 4.0f);

	auto* p_ground_go = Sdk::Import::ImportMesh("Resources/Mesh/Cube.obj")[0];
	auto* p_physic_go = Sdk::Import::ImportMesh("Resources/Mesh/Cube.obj")[0];

	p_ground_go->GetTransform().SetPosition(0.0f, 0.0f, 0.0f);
	p_physic_go->GetTransform().SetPosition(0.0f, 0.6f, 5.0f);
	p_ground_go->SetTag("Ground");

	auto* p_ground_body = p_ground_go->AddComponent<CRigidBody>();
	auto* p_ground_box  = p_ground_go->AddComponent<CBoxCollider>();

	// Static body
	p_ground_body->SetBodyType(CRigidBody::EBodyType::Static);

	// Dynamic body (by default)
	auto* p_physic_body = p_physic_go->AddComponent<CRigidBody>  ();
	auto* p_physic_box  = p_physic_go->AddComponent<CBoxCollider>();
	auto* p_script      = p_physic_go->AddComponent<S_Collision>();

	p_physic_box->SetExtent(glm::vec3(3.0f, 3.0f, 3.0f));

	// Raycast test
	const glm::vec3 pos = glm::vec3(10.0f, 10.0f, 10.0f);
	const glm::vec3 dir = glm::normalize(glm::vec3(0.0f) - pos);

	CRayCast ray_cast = Sdk::Physic::RayCast(pos, dir * 20.0f);
	if(ray_cast.GetGameObject())
	{
		/* Ray cast hit */
	}
}

void LoadDemoScreenSpaceUI()
{
	Sdk::Debug::EnableGizmo(EGizmo::Axis);
	Sdk::Debug::EnableGizmo(EGizmo::Grid);
	Sdk::Debug::EnableGizmo(EGizmo::Transform);

	Sdk::GameObject::CreateFreeCamera();

	auto* p_sprite_go = Sdk::GameObject::CreateUISprite();
}

void LoadDemoTransformation()
{
	Sdk::Render::EnablePostProcessing();
	Sdk::Render::EnablePostEffect(EPostEffect::FXAA);

	Sdk::Debug::EnableGizmo(EGizmo::Ray);
	Sdk::Debug::EnableGizmo(EGizmo::Box);
	Sdk::Debug::EnableGizmo(EGizmo::Axis);
	Sdk::Debug::EnableGizmo(EGizmo::Line);
	Sdk::Debug::EnableGizmo(EGizmo::Grid);
	Sdk::Debug::EnableGizmo(EGizmo::Transform);

	Sdk::GameObject::CreateDirectionalLight();

	auto* p_camera_go = Sdk::GameObject::CreateFreeCamera();
	auto* p_camera    = p_camera_go->GetComponent<S_Camera>();

	p_camera->GetTransform()->SetPosition(30.0f, 30.0f, 30.0f);
	p_camera->GetTransform()->LookAt(0.0f, 0.0f, 0.0f);

	auto* p_scale_go       = Sdk::Import::ImportMesh("Resources/Mesh/Cube.obj")[0];
	auto* p_translate_go   = Sdk::Import::ImportMesh("Resources/Mesh/Cube.obj")[0];

	auto* p_rotate_x_go = Sdk::Import::ImportMesh("Resources/Mesh/Cube.obj")[0];
	auto* p_rotate_y_go = Sdk::Import::ImportMesh("Resources/Mesh/Cube.obj")[0];
	auto* p_rotate_z_go = Sdk::Import::ImportMesh("Resources/Mesh/Cube.obj")[0];
	auto* p_around_z_go = Sdk::Import::ImportMesh("Resources/Mesh/Cube.obj")[0];
	auto* p_look_at_go  = Sdk::Import::ImportMesh("Resources/Mesh/Cube.obj")[0];

	p_scale_go->GetTransform().SetPosition    (  0.0f,   0.0f,  8.0f);
	p_look_at_go->GetTransform().SetPosition  (-12.0f, -12.0f,  0.0f);
	p_rotate_x_go->GetTransform().SetPosition ( 12.0f,  12.0f,  0.0f);
	p_rotate_y_go->GetTransform().SetPosition (-12.0f,  12.0f,  0.0f);
	p_rotate_z_go->GetTransform().SetPosition ( 12.0f, -12.0f,  0.0f);
	p_around_z_go->GetTransform().SetPosition (  9.0f,   0.0f,  0.0f);
	p_translate_go->GetTransform().SetPosition(  0.0f,   0.0f,  0.0f);
	
	p_scale_go->AddComponent    <S_Scale>    ();
	p_translate_go->AddComponent<S_Translate>();

	// Setting up rotations
	auto* p_look_at     = p_look_at_go->AddComponent <S_LookAt>();
	auto* p_component_x = p_rotate_x_go->AddComponent<S_Rotate>();
	auto* p_component_y = p_rotate_y_go->AddComponent<S_Rotate>();
	auto* p_component_z = p_rotate_z_go->AddComponent<S_Rotate>();
	auto* p_component_a = p_around_z_go->AddComponent<S_Rotate>();

	p_component_x->SetAxis(glm::vec3(1.0f, 0.0f, 0.0f));
	p_component_y->SetAxis(glm::vec3(0.0f, 1.0f, 0.0f));
	p_component_z->SetAxis(glm::vec3(0.0f, 0.0f, 1.0f));
	p_component_a->SetAxis(glm::vec3(0.0f, 0.0f, 1.0f));
	p_component_a->IsAround();

	p_look_at->SetTarget(p_around_z_go);
}