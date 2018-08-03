/// \file       CAudioBuffer.cpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Audio
/// \author     Vincent STEHLY--CALISTO

#include "Audio/CAudioBuffer.hpp"

namespace Oom
{

CAudioBuffer::CAudioBuffer()
{
	mp_pcm          = nullptr;
	mp_sound_buffer = nullptr;
}

CAudioBuffer::~CAudioBuffer()
{
	// TODO
}

bool CAudioBuffer::LoadFromFile(const CString& path)
{
	return true;
}

}

