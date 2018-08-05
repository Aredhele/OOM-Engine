/// \file       CAudioEngine.cpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Audio
/// \author     Vincent STEHLY--CALISTO

#include <dsound.h>

#include "Core/Debug/SLogger.hpp"
#include "Audio/CAudioEngine.hpp"
#include "Audio/CAudioSource3D.hpp"
#include "Audio/CAudioListener3D.hpp"

#include "Composite/CGameObject.hpp"
#include "Built-in/Script/S_Camera.hpp"

#include "Render/Gizmos/CGizmosAudioSource.hpp"

namespace Oom
{

/* static */ CAudioEngine* CAudioEngine::sp_instance = nullptr;

bool CAudioEngine::Initialize()
{
    SLogger::LogInfo("Audio engine initialization.");

    HRESULT result = DirectSoundCreate8(nullptr, &mp_direct_sound, nullptr);

    if(result != DS_OK)
    {
        SLogger::LogError("Unable to create the direct sound context.");
        return false;
    }

	result = mp_direct_sound->SetCooperativeLevel(GetDesktopWindow(), DSSCL_PRIORITY);

    if(result != DS_OK)
    {
        SLogger::LogError("Unable to set up the audio context.");
        return false;
    }

	CreateBuffer();
    SLogger::LogInfo("Audio engine initialized.");

    sp_instance = this;
	m_sources.clear();
	m_listeners.clear();

    return true;
}

void CAudioEngine::Release()
{
	if (mp_primary_buffer)
	{
		mp_primary_buffer->Release();
		mp_primary_buffer = nullptr;
	}

	// Release the direct sound interface pointer.
	if (mp_direct_sound)
	{
		mp_direct_sound->Release();
		mp_direct_sound = nullptr;
	}

    sp_instance = nullptr;
}

void CAudioEngine::Update(float delta_time)
{
	DrawGizmos();

	// Getting listeners
	if(m_listeners.empty())
	{
		return;
	}
	else if(m_listeners.size() > 1)
	{
		SLogger::LogWaring("Too many listener in the scene.");
	}

	CAudioListener3D* p_listener = m_listeners[0];
	HRESULT result  = p_listener->mp_listener->SetPosition(
		p_listener->GetGameObject()->GetTransform().GetPosition().x,
		p_listener->GetGameObject()->GetTransform().GetPosition().z,
		p_listener->GetGameObject()->GetTransform().GetPosition().y, DS3D_IMMEDIATE);

	if(result != DS_OK)
	{
		SLogger::LogError("Failed to move the listener.");
	}

	result = p_listener->mp_listener->SetOrientation(
		p_listener->GetGameObject()->GetTransform().GetForward().x,
		p_listener->GetGameObject()->GetTransform().GetForward().z,
		p_listener->GetGameObject()->GetTransform().GetForward().y,
		glm::normalize(p_listener->GetGameObject()->GetTransform().GetUp()).x,
		glm::normalize(p_listener->GetGameObject()->GetTransform().GetUp()).z,
		glm::normalize(p_listener->GetGameObject()->GetTransform().GetUp()).y,
		DS3D_IMMEDIATE);

	if (result != DS_OK)
	{
		SLogger::LogError("Failed to orientate the listener.");
	}

	// Updates source
	for(CAudioSource3D* p_source : m_sources)
	{
		if(p_source->mp_source_3D_buffer)
		{
			p_source->mp_source_3D_buffer->SetPosition(
				p_source->GetTransform()->GetPosition().x,
				p_source->GetTransform()->GetPosition().z,
				p_source->GetTransform()->GetPosition().y,
				DS3D_IMMEDIATE);
		}
	}
}

void CAudioEngine::CreateBuffer()
{
	HRESULT result;
	DSBUFFERDESC buffer_description;
	WAVEFORMATEX wave_format;

	// Primary buffer creation
	buffer_description.dwSize          = sizeof(DSBUFFERDESC);
	buffer_description.dwFlags         = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRL3D;
	buffer_description.dwReserved      = 0;
	buffer_description.lpwfxFormat     = nullptr;
	buffer_description.dwBufferBytes   = 0;
	buffer_description.guid3DAlgorithm = GUID_NULL;

	// Get the primary buffer
	result = mp_direct_sound->CreateSoundBuffer(&buffer_description, &mp_primary_buffer, nullptr);
	if (FAILED(result))
	{
		SLogger::LogError("Failed to create the primary buffer.");
		return;
	}

	// Setup the format of the primary sound bufffer.
	wave_format.wFormatTag      = WAVE_FORMAT_PCM;
	wave_format.nSamplesPerSec  = 44100;
	wave_format.wBitsPerSample  = 16;
	wave_format.nChannels       = 2;
	wave_format.nBlockAlign     = (wave_format.wBitsPerSample / 8) * wave_format.nChannels;
	wave_format.nAvgBytesPerSec =  wave_format.nSamplesPerSec      * wave_format.nBlockAlign;
	wave_format.cbSize          = 0;

	result = mp_primary_buffer->SetFormat(&wave_format);
	if (FAILED(result))
	{
		SLogger::LogError("Failed to set the format of the primary buffer");
		return;
	}

	mp_primary_buffer->SetVolume(DSBVOLUME_MAX);
}

void CAudioEngine::DrawGizmos()
{
	// Updates source
	for (CAudioSource3D* p_source : m_sources)
	{
		if (p_source->mp_source_3D_buffer)
		{
			D3DVALUE min = 0;
			D3DVALUE max = 0;

			p_source->mp_source_3D_buffer->GetMinDistance(&min);
			p_source->mp_source_3D_buffer->GetMaxDistance(&max);

			DrawAudioSource(p_source->GetTransform()->GetPosition(), min, max, 30, 1.0f);
		}
	}
}

/* static */ IDirectSoundBuffer* CAudioEngine::GetPrimaryBuffer()
{
	return sp_instance->mp_primary_buffer;
}

/* static */ IDirectSound8* CAudioEngine::GetDirectSoundInterface()
{
	return sp_instance->mp_direct_sound;
}

/* static */ void CAudioEngine::RegisterCAudioSource3D(CAudioSource3D* p_source)
{
	sp_instance->m_sources.push_back(p_source);
}

/* static */ void CAudioEngine::RegisterCAudioListener3D(CAudioListener3D* p_listener)
{
	sp_instance->m_listeners.push_back(p_listener);
}

/* static */ void CAudioEngine::UnregisterCAudioSource3D(CAudioSource3D* p_source)
{
	for(auto i = 0; i < sp_instance->m_sources.size(); ++i)
	{
		if(sp_instance->m_sources[i] == p_source)
		{
			sp_instance->m_sources[i] = sp_instance->m_sources.back();
			sp_instance->m_sources.pop_back();
			break;
		}
	}
}

/* static */ void CAudioEngine::UnregisterCAudioListener3D(CAudioListener3D* p_listener)
{
	for (auto i = 0; i < sp_instance->m_listeners.size(); ++i)
	{
		if (sp_instance->m_listeners[i] == p_listener)
		{
			sp_instance->m_listeners[i] = sp_instance->m_listeners.back();
			sp_instance->m_listeners.pop_back();
			break;
		}
	}
}

}
