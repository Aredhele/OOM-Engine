/// \file       S_SoundSource.cpp
/// \date       09/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#include "Game/Floppy/Util/S_SoundSource.hpp"

/* virtual */ void S_SoundSource::Awake()
{
	// None
}

/* virtual */ void S_SoundSource::Start()
{
	m_audio_buffer.LoadFromFile(m_path);

	auto* p_source = GetGameObject()->AddComponent<CAudioSource3D>();
	p_source->SetAudioBuffer(&m_audio_buffer);

	p_source->SetMinDistance (15.0f);
	p_source->SetMaxDistance (25.0f);

	p_source->Play(true);
}

void S_SoundSource::SetSound(const char* path)
{
	m_path = path;
}
