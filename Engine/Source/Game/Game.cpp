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
}