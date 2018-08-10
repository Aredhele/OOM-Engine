/// \file       S_SoundSource.cpp
/// \date       09/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#include "Game/Floppy/Util/S_SoundSource.hpp"

/* virtual */ void S_SoundSource::Awake()
{
	mp_source = nullptr;
}

/* virtual */ void S_SoundSource::Start()
{
	m_audio_buffer.LoadFromFile(m_path);

	mp_source = GetGameObject()->AddComponent<CAudioSource3D>();
	mp_source->SetAudioBuffer(&m_audio_buffer);

	mp_source->SetMinDistance (15.0f);
	mp_source->SetMaxDistance (25.0f);

	mp_source->Play();
}

void S_SoundSource::OnDestroy()
{
	mp_source->Stop();
}

void S_SoundSource::SetSound(const char* path)
{
	m_path = path;
}
