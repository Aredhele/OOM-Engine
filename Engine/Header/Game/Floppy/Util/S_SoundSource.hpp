/// \file       S_SoundSource.hpp
/// \date       09/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_S_SOUND_SOURCE_HPP__
#define OOM_ENGINE_S_SOUND_SOURCE_HPP__

#include "SDK/SDK.hpp"

class S_SoundSource : public CBehavior
{
public:

	void Awake		() final;
	void Start		() final;
	void OnDestroy  () final;
	void SetSound	(const char* path);

private:

	CString         m_path;
	CAudioBuffer    m_audio_buffer;
	CAudioSource3D* mp_source;
};

#endif // !OOM_ENGINE_S_SOUND_SOURCE_HPP__
