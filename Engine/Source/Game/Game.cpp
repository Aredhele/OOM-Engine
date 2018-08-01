/// \file       Game.cpp
/// \date       01/08/2018
/// \project    OOM-Engine
/// \package    Game
/// \author     Vincent STEHLY--CALISTO

#include "Hook.hpp"
#include "SDK/SDK.hpp"

#include "Import/CMeshImporter"

void LoadScene()
{
    CGameObject* p_camera = Sdk::GameObject::CreateCamera();
    p_camera->AddComponent<S_CameraController>();
    p_camera->SetTag("MainCamera");

    std::vector<CGameObject*> gog1 = Sdk::Import::ImportMesh("Resources/Mesh/R8.obj");
    std::vector<CGameObject*> gog2 = Sdk::Import::ImportMesh("Resources/Mesh/Cube.obj");
}