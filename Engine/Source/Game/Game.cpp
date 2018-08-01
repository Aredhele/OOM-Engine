/// \file       Game.cpp
/// \date       01/08/2018
/// \project    OOM-Engine
/// \package    Game
/// \author     Vincent STEHLY--CALISTO

#include "Hook.hpp"
#include "SDK/SDK.hpp"

void LoadScene()
{
    CGameObject* p_camera = Sdk::GameObject::CreateCamera();
    p_camera->SetTag("MainCamera");
}