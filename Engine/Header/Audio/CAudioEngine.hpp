/// \file       CAudioEngine.hpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Audio
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_AUDIO_ENGINE_HPP__
#define OOM_ENGINE_C_AUDIO_ENGINE_HPP__

#include <vector>
#include <dsound.h>

namespace Oom
{

// Forward declaration
class CAudioSource3D;
class CAudioListener3D;

class CAudioEngine
{
private:

    friend class CAudioListener3D;

    static IDirectSound3DListener8* Allocate3DListener();
    static void                     Release3DListener (IDirectSound3DListener8* p_listener);

private:

	void CreateBuffer();

private:

    friend class CEngine;

    bool Initialize();
    void Update    (float delta_time);
    void Release   ();

    static CAudioEngine* sp_instance;

private:

    IDirectSound8*         mp_direct_sound     = nullptr;
	IDirectSoundBuffer*    mp_primary_buffer   = nullptr;
	IDirectSound3DBuffer8* mp_secondary_buffer = nullptr;

    std::vector<CAudioSource3D*>   m_sources;
    std::vector<CAudioListener3D*> m_listeners;
};

}

#endif // !OOM_ENGINE_C_AUDIO_ENGINE_HPP__