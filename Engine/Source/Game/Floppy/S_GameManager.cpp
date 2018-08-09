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
	m_key_delay   = 0.3f;
	m_key_elapsed = 0.1f;
}

/*virtual */ void S_GameManager::Start()
{
	mp_floppy         = CGameObject::Find("Floppy");
	auto* p_prompt_go = CGameObject::Find("Prompt");
	auto* p_camera_go = CGameObject::FindWithTag("MainCamera");

	if (p_camera_go)
		mp_camera = p_camera_go->GetComponent<S_CameraController>();

	if(p_prompt_go)
		mp_prompt = p_prompt_go->GetComponent<S_CommandPrompt>();
}

/*virtual */ void S_GameManager::Update()
{
	m_key_elapsed += CTime::delta_time;

	if (Sdk::Input::IsKeyPressed(GLFW_KEY_LEFT_CONTROL) && m_key_elapsed >= m_key_delay)
	{
		m_key_elapsed = 0.0f;

		if(mp_prompt->IsOpen())
		{
			mp_prompt->ClosePrompt();
			mp_camera->SetEnabled(true);
		}
		else
		{
			mp_prompt->OpenPrompt();
			mp_camera->SetEnabled(false);
		}
	}
}

/*virtual */ void S_GameManager::OnDestroy()
{
	// None
}
