/// \file       CAudioDecoder.hpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Audio
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_AUDIO_DECODER_HPP__
#define OOM_ENGINE_C_AUDIO_DECODER_HPP__

namespace Oom
{
	
class CAudioDecoder
{
public:

	static bool DecodeOGG(const char* p_path, void* tmp);
	static bool DecodeWAV(const char* p_path, void* tmp);
};

}

#endif // !OOM_ENGINE_C_AUDIO_DECODER_HPP__