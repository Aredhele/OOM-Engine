/// \file       S_GameManager.cpp
/// \date       08/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#include "Game/Floppy/S_GameManager.hpp"
#include "Game/Floppy/Prompt/S_CommandPrompt.hpp"

/*virtual */ void S_GameManager::Awake()
{
	mp_floppy     = nullptr;
	m_key_delay   = 0.1f;
	m_key_elapsed = 0.1f;
}

/*virtual */ void S_GameManager::Start()
{
	mp_floppy         = CGameObject::Find("Floppy");
	auto* p_prompt_go = CGameObject::Find("Prompt");
}

/*virtual */ void S_GameManager::Update()
{
	if (Sdk::Input::IsKeyPressed(GLFW_KEY_LEFT_CONTROL) && m_key_elapsed >= m_key_delay)
	{
		m_key_elapsed = 0.0f;
		// mp_prompt->GetComponent<S_CommandPrompt>()->IsOpen();
	}
}

/*virtual */ void S_GameManager::OnDestroy()
{
	// None
}
