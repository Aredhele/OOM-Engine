/// \file       S_DestroySound.cpp
/// \date       09/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#include "Game/Floppy/Util/S_DestroySound.hpp"

/* virtual */ void S_DestroySound::Awake()
{
	// None
}

/* virtual */ void S_DestroySound::Start()
{
	m_damage_buffer.LoadFromFile("resources/Sound/sound_bigasset_killed.ogg");

	auto* p_source = GetGameObject()->AddComponent<CAudioSource3D>();
	p_source->SetAudioBuffer(&m_damage_buffer);

	p_source->SetMinDistance (15.0f);
	p_source->SetMaxDistance (25.0f);

	p_source->Play(true);
}