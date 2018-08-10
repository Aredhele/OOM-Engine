/// \file       S_ConveyorController.cpp
/// \date       00/08/2018
/// \project    OOM-Engine
/// \package    Game/Floppy/Controller
/// \author     Vincent STEHLY--CALISTO

#include "Game/Floppy/Controller/S_ConveyorController.hpp"

/* virtual */ void S_ConveyorController::Awake()
{
	mp_material               = nullptr;
	mp_source_switch_on       = nullptr;
	mp_source_switch_off      = nullptr;
	m_is_activated			  = true;
	m_activated_texture		  = 0;
	m_desactivated_texture	  = 0;
	m_uv_offset				  = 0.0f;
}

/* virtual */ void S_ConveyorController::Start()
{
	m_audio_buffer_switch_on.LoadFromFile("Resources/Sound/sound_switchon_conveyor.ogg");
	m_audio_buffer_shutdown.LoadFromFile ("Resources/Sound/sound_shutdown_conveyor.ogg");

	mp_source_switch_on  = GetGameObject()->AddComponent<CAudioSource3D>();
	mp_source_switch_off = GetGameObject()->AddComponent<CAudioSource3D>();

	mp_source_switch_on->SetAudioBuffer (&m_audio_buffer_switch_on);
	mp_source_switch_off->SetAudioBuffer(&m_audio_buffer_shutdown);

	mp_source_switch_on->SetMinDistance(15.0f);
	mp_source_switch_on->SetMaxDistance(30.0f);

	mp_source_switch_off->SetMinDistance(15.0f);
	mp_source_switch_off->SetMaxDistance(30.0f);

	// To animate the texture
	mp_material = GetGameObject()->GetComponent<CMaterial>();

	// Getting texture
	m_desactivated_texture = Sdk::Import::ImportTexture("Resources/Texture/T_TapisRoulant_Unactivated_small.png");
	m_activated_texture    = mp_material->GetTexture();  

	// Sets to activated
	mp_material->SetTexture(m_activated_texture);
}

void S_ConveyorController::Update()
{
	if(m_is_activated)
	{
		m_uv_offset += CTime::delta_time;
		mp_material->SetUVOffset(glm::vec2(0.0f, -m_uv_offset));
	}
}

/* virtual */ void S_ConveyorController::OnDestroy()
{
	mp_source_switch_on->Stop();
	mp_source_switch_off->Stop();
}

void S_ConveyorController::ActivateConveyor()
{
	m_is_activated = true;
	mp_source_switch_on->Play();
	mp_material->SetTexture(m_activated_texture);
}

void S_ConveyorController::DesactivateConveyor()
{
	m_is_activated = false;
	mp_source_switch_off->Play();
	mp_material->SetTexture(m_desactivated_texture);
}
