/// \file       Game.cpp
/// \date       01/08/2018
/// \project    OOM-Engine
/// \package    Game
/// \author     Vincent STEHLY--CALISTO

#include <Core/Debug/SLogger.hpp>
#include "Hook.hpp"
#include "SDK/SDK.hpp"

#include "Import/CMeshImporter"

void LoadScene()
{
    // TODO : make the camera creation easier
    CGameObject* p_camera = Sdk::GameObject::CreateCamera();
    p_camera->AddComponent<S_CameraController>();
    p_camera->SetTag("MainCamera");

    Sdk::Import::ImportMesh("Resources/Mesh/Cube.obj");
}