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

    CGameObject* go = Sdk::GameObject::CreateText();
    auto* p_text    = go->GetComponent<S_Text>();

    p_text->Set("hello, world", glm::vec2(730.0f, 580.0f), 100, glm::vec3(0.3f));
}