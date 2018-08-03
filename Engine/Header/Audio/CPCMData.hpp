/// \file       CPCMData.cpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Audio
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_PCM_DATA_HPP__
#define OOM_ENGINE_C_PCM_DATA_HPP__

#include <vector>
#include "Audio/CWaveHeader.hpp"

namespace Oom
{

struct CPCMData
{
	CWaveHeader          wave_header;
	std::vector<int16_t> samples;
};

}

#endif // !OOM_ENGINE_C_PCM_DATA_HPP__