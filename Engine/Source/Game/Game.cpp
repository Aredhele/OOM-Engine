/// \file       Game.cpp
/// \date       01/08/2018
/// \project    OOM-Engine
/// \package    Game
/// \author     Vincent STEHLY--CALISTO

#include <Core/Debug/SLogger.hpp>
#include <Import/CTextureImporter.hpp>
#include "Hook.hpp"
#include "SDK/SDK.hpp"

#include "Import/CMeshImporter"


CAudioBuffer buffer;

void LoadScene()
{
    auto* cam =Sdk::GameObject::CreateFreeCamera();
    Sdk::Import::ImportMesh("Resources/Mesh/Cube.obj");
    Sdk::Import::ImportMesh("Resources/Mesh/Environment_01.obj");

    CGameObject* go = Sdk::GameObject::CreateText();
    auto* p_text    = go->GetComponent<S_Text>();

    p_text->Set("OOM-Engine v0.1", glm::vec2(00.0f, 850.0f), 50, glm::vec3(0.3f));

    auto* p_direc = Sdk::GameObject::CreateDirectionalLight();
    auto* p_point = Sdk::GameObject::CreatePointLight();

	cam->AddComponent<CAudioListener3D>();
	auto* p_source_go   = Sdk::GameObject::CreateAudioSource3D();


	buffer.LoadFromFile("Resources/XMasMono.ogg");

	auto* p_source = p_source_go->GetComponent<CAudioSource3D>();
	p_source->SetAudioBuffer(&buffer);
	p_source->SetMinDistance(5.0f);
	p_source->SetMaxDistance(15.0f);
	p_source->Play();

    auto* p_light = p_point->GetComponent<S_PointLight>();
    p_light->SetColor(glm::vec3(1.0f));
    p_light->SetIntensity(0.8f);
    p_light->SetRange(25.0f);

    p_point->GetTransform().SetLocalPosition(glm::vec3(0.0f,0.0f, 10.0f));

    auto* p_directional = p_direc->GetComponent<S_DirectionalLight>();
    p_directional->SetLightIntensity  (0.8f);
    p_directional->SetAmbientIntensity(0.3f);
    p_directional->SetDirection       (glm::vec3(-0.6f, -0.1f, -0.1f));
    p_directional->SetLightColor      (glm::vec3(1.0f, 1.0f, 1.0f));
    p_directional->SetAmbientColor    (glm::vec3(1.0f, 1.0f, 1.0f));

    p_direc->GetTransform().SetLocalPosition(glm::vec3(5.0f, 5.0f, 20.0f));
}