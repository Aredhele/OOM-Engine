/// \file       CAssetWave.cpp
/// \date       09/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#include "Game/Floppy/Asset/CAssetWave.hpp"

CAssetWave::CAssetWave(float time, float delay, EAsset type, ESpawnZone zone, CString pattern)
: m_time   (time)
, m_delay  (delay)
, m_type   (type)
, m_zone   (zone)
, m_pattern(pattern)
, m_elapsed(0.0f)
, m_current(0)
{
	// None
}
