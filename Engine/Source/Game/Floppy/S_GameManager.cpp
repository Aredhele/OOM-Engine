/// \file       S_GameManager.cpp
/// \date       08/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#include "Game/Floppy/S_GameManager.hpp"

/*virtual */ void S_GameManager::Awake()
{
	mp_floppy = nullptr;

	glm::quat x = glm::eulerAngles(glm::quat());
}

/*virtual */ void S_GameManager::Start()
{
	mp_floppy = CGameObject::Find("Floppy");
}

/*virtual */ void S_GameManager::Update()
{
	// None
}

/*virtual */ void S_GameManager::OnDestroy()
{
	// None
}
