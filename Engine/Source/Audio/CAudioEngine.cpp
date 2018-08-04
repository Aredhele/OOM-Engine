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
	// Getting the camera
	CGameObject* p_camera = CEngine::FindWithTag("MainCamera");

	if (!p_camera)
	{
		SLogger::LogWaring("No main camera found.");
		return;
	}

	// Getting listeners
	// TODO
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