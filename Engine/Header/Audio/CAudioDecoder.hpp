/// \file       CAudioDecoder.hpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Audio
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_AUDIO_DECODER_HPP__
#define OOM_ENGINE_C_AUDIO_DECODER_HPP__

#include "Audio/CPCMData.hpp"

namespace Oom
{
	
class CAudioDecoder
{
public:

	static bool DecodeOGG(const char* p_path, CPCMData& pcm_data);
	static bool DecodeWAV(const char* p_path, CPCMData& pcm_data);
};

}

#endif // !OOM_ENGINE_C_AUDIO_DECODER_HPP__