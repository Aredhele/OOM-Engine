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

	friend class CAudioBuffer;
	friend class CAudioSource3D;
    friend class CAudioListener3D;

	static IDirectSound8*			GetDirectSoundInterface   ();
	static IDirectSoundBuffer*		GetPrimaryBuffer          ();
	static void						RegisterCAudioSource3D    (CAudioSource3D*   p_source);
	static void						RegisterCAudioListener3D  (CAudioListener3D* p_listener);
	static void						UnregisterCAudioSource3D  (CAudioSource3D*   p_source);
	static void						UnregisterCAudioListener3D(CAudioListener3D* p_listener);

private:

	void CreateBuffer();
	void DrawGizmos  ();

private:

    friend class CEngine;

    bool Initialize();
    void Update    (float delta_time);
    void Release   ();

    static CAudioEngine* sp_instance;

private:

    IDirectSound8*         mp_direct_sound        = nullptr;
	IDirectSoundBuffer*    mp_primary_buffer      = nullptr;

    std::vector<CAudioSource3D*>   m_sources;
    std::vector<CAudioListener3D*> m_listeners;
};

}

#endif // !OOM_ENGINE_C_AUDIO_ENGINE_HPP__