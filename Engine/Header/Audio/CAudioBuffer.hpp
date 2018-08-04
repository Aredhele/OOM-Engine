/// \file       CAudioBuffer.hpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Audio
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_AUDIO_BUFFER_HPP__
#define OOM_ENGINE_C_AUDIO_BUFFER_HPP__

#include <dsound.h>
#include "Audio/CPCMData.hpp"
#include "Core/Standard/CString.hpp"

namespace Oom
{
	
class CAudioBuffer
{
public:

	CAudioBuffer();
	~CAudioBuffer();

	bool LoadFromFile(const CString& path);
	
private:

	friend class CAudioEngine;
	friend class CAudioSource3D;

	CPCMData		       m_pcm_data;
	IDirectSoundBuffer8*   mp_secondary_buffer;
}; 

}

#endif // !OOM_ENGINE_C_AUDIO_BUFFER_HPP__