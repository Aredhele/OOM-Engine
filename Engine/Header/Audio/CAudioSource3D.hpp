/// \file       CAudioSource3D.hpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Audio
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_AUDIO_SOURCE_3_D_HPP__
#define OOM_ENGINE_C_AUDIO_SOURCE_3_D_HPP__

#include <dsound.h>
#include "Composite/IComponent.hpp"

namespace Oom
{
	
// Forward declaration
class CAudioBuffer;

class CAudioSource3D : public IComponent
{
public:

	void Play  (bool must_loop = false);
	void Stop  ();
	void SetFrequency  (float pitch);
	void SetMinDistance(float distance);
	void SetMaxDistance(float distance);
	void SetVolume     (uint32_t volume);
	void SetAudioBuffer(CAudioBuffer* p_audio_buffer);

public:

	void OnEnable () final;
	void OnDisable() final;
	void OnDestroy() final;

protected:

	void _Register() final;
	void _Destroy () final;

private:

	friend class CAudioEngine;
	
	CAudioBuffer*           mp_audio_buffer     = nullptr;
	IDirectSound3DBuffer8*  mp_source_3D_buffer = nullptr;
};

}

#endif // !OOM_ENGINE_C_AUDIO_SOURCE_3_D_HPP__
