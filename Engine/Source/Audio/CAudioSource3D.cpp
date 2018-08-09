/// \file       CAudioSource3D.cpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Audio
/// \author     Vincent STEHLY--CALISTO

#include "Audio/CAudioEngine.hpp"
#include "Audio/CAudioBuffer.hpp"
#include "Audio/CAudioSource3D.hpp"

#include "Core/Debug/SLogger.hpp"

namespace Oom
{

void CAudioSource3D::OnEnable()
{
	// None
}

void CAudioSource3D::OnDisable()
{
	// None
}

void CAudioSource3D::OnDestroy()
{
	// None
}

void CAudioSource3D::_Register()
{
	CAudioEngine::RegisterCAudioSource3D(this);
}

void CAudioSource3D::_Destroy()
{
	CAudioEngine::UnregisterCAudioSource3D(this);

	if (mp_audio_buffer)
	{
		mp_audio_buffer->mp_secondary_buffer->Stop();
		mp_audio_buffer->mp_secondary_buffer->Release();
	}
		
	if (mp_source_3D_buffer)
		mp_source_3D_buffer->Release();
}

void CAudioSource3D::SetAudioBuffer(CAudioBuffer* p_audio_buffer)
{
	if(p_audio_buffer == nullptr)
	{
		if(mp_audio_buffer)
		{
			mp_audio_buffer->mp_secondary_buffer->Stop();
			mp_audio_buffer = nullptr;
		}

		if (mp_source_3D_buffer)
			mp_source_3D_buffer->Release();

		return;
	}

	if(p_audio_buffer && mp_source_3D_buffer)
	{
		if (mp_source_3D_buffer)
			mp_source_3D_buffer->Release();
	}

	mp_audio_buffer = p_audio_buffer;
	
	IDirectSoundBuffer8* p_source_buffer = mp_audio_buffer->mp_secondary_buffer;
	HRESULT result = p_source_buffer->QueryInterface(IID_IDirectSound3DBuffer8, (void**)&mp_source_3D_buffer);

	if (result != DS_OK)
	{
		SLogger::LogError("Unable to create the 3D sound buffer.");
		return;
	}
}

void CAudioSource3D::Play(bool must_loop)
{
	if (mp_audio_buffer)
		mp_audio_buffer->mp_secondary_buffer->Play(0, 0, must_loop);
}

void CAudioSource3D::Stop()
{
	if (mp_audio_buffer)
		mp_audio_buffer->mp_secondary_buffer->Stop();
}

void CAudioSource3D::SetFrequency(float pitch)
{
	if (mp_audio_buffer)
	{
		const DWORD base_freq = mp_audio_buffer->m_pcm_data.wave_header.m_fmt_sampling_rate;
		mp_audio_buffer->mp_secondary_buffer->SetFrequency(base_freq * pitch);
	}
}

void CAudioSource3D::SetMinDistance(float distance)
{
	if (mp_source_3D_buffer)
		mp_source_3D_buffer->SetMinDistance(distance, DS3D_IMMEDIATE);
}

void CAudioSource3D::SetMaxDistance(float distance)
{
	if (mp_source_3D_buffer)
		mp_source_3D_buffer->SetMaxDistance(distance, DS3D_IMMEDIATE);
}

void CAudioSource3D::SetVolume(uint32_t volume)
{
	LONG dx_volume = (volume == 0) ? -10000 : (int)floorf(2000.0f * log10f((float)(volume) / 100.0f) + 0.5f);

	if (mp_audio_buffer)
		mp_audio_buffer->mp_secondary_buffer->SetVolume(dx_volume);
}

}
