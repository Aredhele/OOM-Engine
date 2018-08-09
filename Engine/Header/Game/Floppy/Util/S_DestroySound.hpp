/// \file       S_DestroySound.hpp
/// \date       09/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_S_DESTROY_SOUND_HPP__
#define OOM_ENGINE_S_DESTROY_SOUND_HPP__

#include "SDK/SDK.hpp"

class S_DestroySound : public CBehavior
{
public:

	void Awake () final;
	void Start () final;

private:

	CAudioBuffer m_damage_buffer;
};

#endif // !OOM_ENGINE_S_DESTROY_SOUND_HPP__
