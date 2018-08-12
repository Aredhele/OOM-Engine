/// \file       Game.cpp
/// \date       01/08/2018
/// \project    OOM-Engine
/// \package    Game
/// \author     Vincent STEHLY--CALISTO

#include "SDK/SDK.hpp"
#include "Scene/Hook.hpp"
#include "Scene/CScene.hpp"
#include "Game/Prefab/Prefab.hpp"

// Temporary
CAudioBuffer buffer_1;
CAudioBuffer buffer_2;

void LoadScene()
{
	CScene::LoadScene(CScene::EScene::Game);
}

void LoadGameScene()
{
	// Enabling debug gizmos
	Sdk::Debug::EnableGizmo(EGizmo::Ray);

    // Sdk::Debug::EnableGizmo(EGizmo::Box);
    // Sdk::Debug::EnableGizmo(EGizmo::Axis);
    // Sdk::Debug::EnableGizmo(EGizmo::Line);
    // Sdk::Debug::EnableGizmo(EGizmo::Grid);
    // 
    // Sdk::Debug::EnableGizmo(EGizmo::AllColliders);
    // Sdk::Debug::EnableGizmo(EGizmo::AllTransforms);
    // Sdk::Debug::EnableGizmo(EGizmo::AllPointLights);
    // Sdk::Debug::EnableGizmo(EGizmo::AllAudioSources);
    // Sdk::Debug::EnableGizmo(EGizmo::AllDirectionalLights);

	// Importing 3D assets
	Sdk::Import::ImportMesh("Resources/Mesh/Mesh_Asset.obj");
	Sdk::Import::ImportMesh("Resources/Mesh/Mesh_Floppy.obj");
	Sdk::Import::ImportMesh("Resources/Mesh/Mesh_Super_Asset.obj");
	Sdk::Import::ImportMesh("Resources/Mesh/Mesh_Environment.obj");

	// Setting up the scene
	Prefab::CreatePlayer();
	Prefab::CreateGlobalLighting();
	Prefab::CreateStaticEnvironment();

    Prefab::CreateDoors();
	Prefab::CreateAlarms();
	Prefab::CreateConveyors();
	Prefab::CreateFloppy();

	Prefab::CreateGameManager();
	Prefab::CreateCommandPrompt();
	Prefab::CreateSpawnerManager();


	// Create the crosshair
	auto& crosshairSprite = *Sdk::GameObject::CreateUISprite();
	auto* p_material      = crosshairSprite.GetComponent<CMaterial>();

	p_material->SetColor(glm::vec3(0.0f, 1.0f, 0.0f));
	p_material->SetTexture(Sdk::Import::ImportTexture("Resources/Texture/Crosshair.png"));
	crosshairSprite.GetTransform().SetPosition(0.5f, 0.5f, 0.0f);
}

void LoadDemoSceneAudio()
{
	Sdk::Debug::EnableGizmo(EGizmo::Ray);
	Sdk::Debug::EnableGizmo(EGizmo::Box);
	Sdk::Debug::EnableGizmo(EGizmo::Axis);
	Sdk::Debug::EnableGizmo(EGizmo::Line);
	Sdk::Debug::EnableGizmo(EGizmo::Grid);
	Sdk::Debug::EnableGizmo(EGizmo::AllAudioSources);

	auto* p_camera = Sdk::GameObject::CreateFreeCamera();

	// Loads 2 sounds from a file
	buffer_1.LoadFromFile("Resources/Music/Music_floppy_jam.ogg");
	buffer_2.LoadFromFile("Resources/Music/Music_floppy_jam.ogg");

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
	Sdk::Debug::EnableGizmo(EGizmo::Ray);
	Sdk::Debug::EnableGizmo(EGizmo::Box);
	Sdk::Debug::EnableGizmo(EGizmo::Axis);
	Sdk::Debug::EnableGizmo(EGizmo::Line);
	Sdk::Debug::EnableGizmo(EGizmo::Grid);
	Sdk::Debug::EnableGizmo(EGizmo::AllColliders);
	Sdk::Debug::EnableGizmo(EGizmo::AllTransforms);

	Sdk::GameObject::CreateDirectionalLight();
	Sdk::Import::ImportMesh("Resources/Mesh/Cube.obj");

	auto* p_camera = Sdk::GameObject::CreateFreeCamera();

	auto* p_ground_go_1 = Sdk::GameObject::CreateGameObjectFromMesh("Cube");
	auto* p_ground_go_2 = Sdk::GameObject::CreateGameObjectFromMesh("Cube");
	auto* p_ground_go_3 = Sdk::GameObject::CreateGameObjectFromMesh("Cube");
	auto* p_ground_go_4 = Sdk::GameObject::CreateGameObjectFromMesh("Cube");

	// Static
	p_ground_go_1->GetTransform().SetPosition( 0.8f, 0.0f,  3.0f);
	p_ground_go_2->GetTransform().SetPosition( 2.8f, 0.0f,  5.0f);
	p_ground_go_3->GetTransform().SetPosition(-0.8f, 0.0f, 10.0f);
	p_ground_go_4->GetTransform().SetPosition(-1.8f, 0.0f,  2.0f);

	p_ground_go_1->AddComponent<CBoxCollider>();
	p_ground_go_2->AddComponent<CBoxCollider>();
	p_ground_go_3->AddComponent<CBoxCollider>();
	p_ground_go_4->AddComponent<CBoxCollider>();

	auto* p_ground_body_1 = p_ground_go_1->AddComponent<CRigidBody>();
	auto* p_ground_body_2 = p_ground_go_2->AddComponent<CRigidBody>();
	auto* p_ground_body_3 = p_ground_go_3->AddComponent<CRigidBody>();
	auto* p_ground_body_4 = p_ground_go_4->AddComponent<CRigidBody>();

	// Static body
	p_ground_body_1->SetBodyType(CRigidBody::EBodyType::Static);
	p_ground_body_2->SetBodyType(CRigidBody::EBodyType::Static);
	p_ground_body_3->SetBodyType(CRigidBody::EBodyType::Static);
	p_ground_body_4->SetBodyType(CRigidBody::EBodyType::Static);

	p_ground_body_2->SetOrientationX(45.0f);

	// Controller
	auto* p_controller = Sdk::GameObject::CreateEmpty();
	p_controller->AddComponent<S_Spawner>();
}

void LoadDemoScreenSpaceUI()
{
	Sdk::Debug::EnableGizmo(EGizmo::Axis);
	Sdk::Debug::EnableGizmo(EGizmo::Grid);
	Sdk::Debug::EnableGizmo(EGizmo::Transform);

	Sdk::GameObject::CreateFreeCamera();

	auto* p_sprite_go_1  = Sdk::GameObject::CreateUISprite();
	auto* p_sprite_go_2  = Sdk::GameObject::CreateUISprite();
	auto* p_sprite_go_3  = Sdk::GameObject::CreateUISprite();

	auto* p_sprite_mat_1 = p_sprite_go_1->GetComponent<CMaterial>();
	auto* p_sprite_mat_2 = p_sprite_go_2->GetComponent<CMaterial>();
	auto* p_sprite_mat_3 = p_sprite_go_3->GetComponent<CMaterial>();

	auto* p_renderer_1   = p_sprite_go_1->GetComponent<CUISpriteRenderer>();
	auto* p_renderer_2   = p_sprite_go_2->GetComponent<CUISpriteRenderer>();
	auto* p_renderer_3   = p_sprite_go_3->GetComponent<CUISpriteRenderer>();

	p_sprite_mat_1->SetTexture(Sdk::Import::ImportTexture("Resources/Texture/Default.png"));
	p_sprite_mat_2->SetTexture(Sdk::Import::ImportTexture("Resources/Texture/Default.png"));
	p_sprite_mat_3->SetTexture(Sdk::Import::ImportTexture("Resources/Texture/Default.png"));

	p_renderer_1->SetSortingLayer(0);
	p_renderer_2->SetSortingLayer(1);
	p_renderer_3->SetSortingLayer(2);

	p_sprite_go_1->GetTransform().SetScale   (3.0, 3.0f, 1.0f);
	p_sprite_go_2->GetTransform().SetScale   (3.0, 3.0f, 1.0f);
	p_sprite_go_3->GetTransform().SetScale   (3.0, 3.0f, 1.0f);

	p_sprite_go_1->GetTransform().SetPosition(.25f, .5f, 0.0f);
	p_sprite_go_2->GetTransform().SetPosition(.50f, .5f, 0.0f);
	p_sprite_go_3->GetTransform().SetPosition(.75f, .5f, 0.0f);

	p_sprite_mat_1->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
	p_sprite_mat_2->SetColor(glm::vec3(0.0f, 1.0f, 0.0f));
	p_sprite_mat_3->SetColor(glm::vec3(0.0f, 0.0f, 1.0f));

	// Add some texts
	auto* p_text_go_1 = Sdk::GameObject::CreateUIText();
	auto* p_text_go_2 = Sdk::GameObject::CreateUIText();
	auto* p_text_go_3 = Sdk::GameObject::CreateUIText();

	auto* p_text_1 = p_text_go_1->GetComponent<S_Text>();
	auto* p_text_2 = p_text_go_2->GetComponent<S_Text>();
	auto* p_text_3 = p_text_go_3->GetComponent<S_Text>();

	p_text_go_1->GetTransform().SetPosition(0.15f, 0.35f, 0.0f);
	p_text_go_2->GetTransform().SetPosition(0.40f, 0.35f, 0.0f);
	p_text_go_3->GetTransform().SetPosition(0.65f, 0.35f, 0.0f);

	p_text_1->SetText("R");
	p_text_2->SetText("G");
	p_text_3->SetText("B");
}

void LoadDemoSceneTransformation()
{
	Sdk::Debug::EnableGizmo(EGizmo::Axis);
	Sdk::Debug::EnableGizmo(EGizmo::Grid);
	Sdk::Debug::EnableGizmo(EGizmo::AllTransforms);

	Sdk::GameObject::CreateFreeCamera();
	Sdk::GameObject::CreateDirectionalLight();

	Sdk::Import::ImportMesh("Resources/Mesh/Cube.obj");

	auto* p_scale_go     = Sdk::GameObject::CreateGameObjectFromMesh("Cube");
	auto* p_translate_go = Sdk::GameObject::CreateGameObjectFromMesh("Cube");
	auto* p_rotate_x_go  = Sdk::GameObject::CreateGameObjectFromMesh("Cube");
	auto* p_rotate_y_go  = Sdk::GameObject::CreateGameObjectFromMesh("Cube");
	auto* p_rotate_z_go  = Sdk::GameObject::CreateGameObjectFromMesh("Cube");
	auto* p_around_z_go  = Sdk::GameObject::CreateGameObjectFromMesh("Cube");
	auto* p_look_at_go   = Sdk::GameObject::CreateGameObjectFromMesh("Cube");
	auto* p_rotate_c_go  = Sdk::GameObject::CreateGameObjectFromMesh("Cube");

	// OK
	p_scale_go->GetTransform().SetPosition      (  0.0f,   0.0f,  8.0f);
	p_look_at_go->GetTransform().SetEulerAngles (  0.0f,  20.0f,  0.0f);
	p_look_at_go->GetTransform().SetPosition    (-12.0f, -12.0f,  0.0f);
	
	p_rotate_x_go->GetTransform().SetPosition   ( 12.0f,  12.0f,  0.0f);
	p_rotate_y_go->GetTransform().SetPosition   (-12.0f,  12.0f,  0.0f);
	p_rotate_z_go->GetTransform().SetPosition   ( 12.0f, -12.0f,  0.0f);
	p_around_z_go->GetTransform().SetPosition   (  9.0f,   0.0f,  3.0f);
	p_rotate_c_go->GetTransform().SetPosition   (  0.0f,   0.0f, 12.0f);
	p_translate_go->GetTransform().SetPosition  (  0.0f,   0.0f,  0.0f);
	
	p_scale_go->AddComponent    <S_Scale>    ();
	p_translate_go->AddComponent<S_Translate>();

	// Setting up rotations
	auto* p_look_at     = p_look_at_go->AddComponent <S_LookAt>();
	auto* p_component_x = p_rotate_x_go->AddComponent<S_Rotate>();
	auto* p_component_y = p_rotate_y_go->AddComponent<S_Rotate>();
	auto* p_component_z = p_rotate_z_go->AddComponent<S_Rotate>();
	auto* p_component_a = p_around_z_go->AddComponent<S_Rotate>();
	auto* p_component_c = p_rotate_c_go->AddComponent<S_Rotate>();

	p_component_x->SetAxis(glm::vec3(1.0f, 0.0f, 0.0f));
	p_component_y->SetAxis(glm::vec3(0.0f, 1.0f, 0.0f));
	p_component_z->SetAxis(glm::vec3(0.0f, 0.0f, 1.0f));
	p_component_a->SetAxis(glm::vec3(0.0f, 0.0f, 1.0f));
	p_component_c->SetAxis(glm::vec3(1.0f, 0.0f, 1.0f));
	p_component_a->IsAround();

	p_look_at->SetTarget(p_around_z_go);	
}

void LoadDemoSceneRendering()
{
	Sdk::Debug::EnableGizmo(EGizmo::Axis);
	Sdk::Debug::EnableGizmo(EGizmo::Grid);
	Sdk::Debug::EnableGizmo(EGizmo::Transform);
	Sdk::Debug::EnableGizmo(EGizmo::AllPointLights);
	Sdk::Debug::EnableGizmo(EGizmo::AllDirectionalLights);

	Sdk::GameObject::CreateFreeCamera();
	Sdk::Import::ImportMesh("Resources/Mesh/Cube.obj");

	auto* p_point_go       = Sdk::GameObject::CreatePointLight();
	auto* p_directional_go = Sdk::GameObject::CreateDirectionalLight();
	auto* p_point_light    = p_point_go->GetComponent<S_PointLight>();

	p_point_light->SetRange    (5.0f);
	p_point_light->SetIntensity(1.0f);
	p_point_light->SetColor    (glm::vec3(0.0f, 0.0f, 1.0f));
	
	p_point_go->GetTransform().SetPosition(3.0f, 0.0f, 2.0f);
	p_directional_go->GetTransform().SetPosition(10.0f, 10.0f, 6.0f);

	p_point_go->AddComponent<S_RotateLight>();
	p_directional_go->AddComponent<S_RotateLight>();
	
	for(auto i = -5; i < 6; ++i) {
		for(auto j = -5; j < 6; ++j) {
			auto* p_object_1 = Sdk::GameObject::CreateGameObjectFromMesh("Cube");
			auto* p_object_2 = Sdk::GameObject::CreateGameObjectFromMesh("Cube");
			p_object_1->GetTransform().SetPosition(i, j, 0.0f);
			p_object_2->GetTransform().SetPosition(i, j, 7.0f);
		}
	}

	for(auto i = 0; i < 6; ++i) {
		auto* p_object_1 = Sdk::GameObject::CreateGameObjectFromMesh("Cube");
		auto* p_object_2 = Sdk::GameObject::CreateGameObjectFromMesh("Cube");
		auto* p_object_3 = Sdk::GameObject::CreateGameObjectFromMesh("Cube");
		auto* p_object_4 = Sdk::GameObject::CreateGameObjectFromMesh("Cube");

		p_object_1->GetTransform().SetPosition( 5,  5, i + 1);
		p_object_2->GetTransform().SetPosition(-5,  5, i + 1);
		p_object_3->GetTransform().SetPosition( 5, -5, i + 1);
		p_object_4->GetTransform().SetPosition(-5, -5, i + 1);
	}
}