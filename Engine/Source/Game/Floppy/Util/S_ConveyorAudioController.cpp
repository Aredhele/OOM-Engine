/// \file       S_ConveyorAudioController.cpp
/// \date       00/08/2018
/// \project    OOM-Engine
/// \package    Game/Floppy/Util
/// \author     Vincent STEHLY--CALISTO

#include "Game/Floppy/Util/S_ConveyorAudioController.hpp"

/* virtual */ void S_ConveyorAudioController::Awake()
{
	mp_source_switch_on       = nullptr;
	mp_source_switch_off      = nullptr;
}

/* virtual */ void S_ConveyorAudioController::Start()
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
}

/* virtual */ void S_ConveyorAudioController::OnDestroy()
{
	mp_source_switch_on->Stop();
	mp_source_switch_off->Stop();
}

void S_ConveyorAudioController::ActivateConveyor()
{
	mp_source_switch_on->Play();
}

void S_ConveyorAudioController::DesactivateConveyor()
{
	mp_source_switch_off->Play();
}
