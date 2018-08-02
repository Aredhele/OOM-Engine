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

void LoadScene()
{
    Sdk::GameObject::CreateFreeCamera();
    Sdk::Import::ImportMesh("Resources/Mesh/Cube.obj");
    Sdk::Import::ImportMesh("Resources/Mesh/Environment_01.obj");

    CGameObject* go = Sdk::GameObject::CreateText();
    auto* p_text    = go->GetComponent<S_Text>();

    p_text->Set("OOM-Engine v0.1", glm::vec2(00.0f, 850.0f), 50, glm::vec3(0.3f));

    auto* p_direc = Sdk::GameObject::CreateDirectionalLight();
    auto* p_point = Sdk::GameObject::CreatePointLight();

    auto* p_light = p_point->GetComponent<S_PointLight>();
    p_light->SetColor(glm::vec3(1.0f));
    p_light->SetIntensity(0.8f);
    p_light->SetRange(1.0f);
    p_point->GetTransform().SetLocalPosition(glm::vec3(0.0f,0.0f, 2.0f));


    auto* p_directional = p_direc->GetComponent<S_DirectionalLight>();
    p_directional->SetLightIntensity (0.1f);
    p_directional->SetAmbientIntensity(0.1f);
    p_directional->SetDirection       (glm::vec3(-0.4f, -0.1f, -0.8f));
    p_directional->SetLightColor      (glm::vec3(1.0f, 1.0f, 1.0f));
    p_directional->SetAmbientColor    (glm::vec3(1.0f, 1.0f, 1.0f));
}