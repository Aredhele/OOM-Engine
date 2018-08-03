/// \file       CAudioEngine.cpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Audio
/// \author     Vincent STEHLY--CALISTO

#include <dsound.h>
#include "Core/Debug/SLogger.hpp"
#include "Audio/CAudioEngine.hpp"
#include "Audio/CAudioDecoder.hpp"

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
	buffer_description.lpwfxFormat     = NULL;
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
	// In this case it is a .WAV file recorded at 44,100 samples per second in 16-bit stereo (cd audio format).
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

/* static */ IDirectSound3DListener8* CAudioEngine::Allocate3DListener()
{
	IDirectSound3DListener8* p_listener = nullptr;

	// Obtain a listener interface.
	HRESULT result = sp_instance->mp_primary_buffer->QueryInterface(IID_IDirectSound3DListener8, (LPVOID*)&p_listener);

	if (FAILED(result))
	{
		SLogger::LogError("Failed to create the listener");
		return nullptr;
	}

	return p_listener;
}

/* static */ void Oom::CAudioEngine::Release3DListener(IDirectSound3DListener8* p_listener)
{
    // TODO
}


}