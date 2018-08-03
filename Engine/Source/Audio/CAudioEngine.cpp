/// \file       CAudioEngine.cpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Audio
/// \author     Vincent STEHLY--CALISTO

#include "Core/Debug/SLogger.hpp"
#include "Audio/CAudioEngine.hpp"

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

    SLogger::LogInfo("Audio engine initialized.");

    sp_instance = this;
    return true;
}


void CAudioEngine::Release()
{
    sp_instance = nullptr;
}

void CAudioEngine::Update(float delta_time)
{

}

/* static */ IDirectSound3DListener8* CAudioEngine::Allocate3DListener()
{
    IDirectSound3DListener8* p_listener = nullptr;
    HRESULT result = sp_instance->mp_direct_sound->QueryInterface(IID_IDirectSound3DListener, (void**)&p_listener);

    if(result != DS_OK)
    {
        SLogger::LogError("Unable to create the audio listener");
    }

    return nullptr;
}

/* static */ void Oom::CAudioEngine::Release3DListener(IDirectSound3DListener8* p_listener)
{
    // TODO
}


}