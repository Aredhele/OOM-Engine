/// \file       IAsset.cpp
/// \date       08/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#include "Game/Floppy/Asset/IAsset.hpp"

void IAsset::SetSpeed(float speed)
{
	m_speed = speed;
}

void IAsset::SetAssetType(EAsset asset_type)
{
	m_asset_type = asset_type;
}

void IAsset::SetKiloBytes(uint32_t kilo_bytes)
{
	m_kilo_bytes = kilo_bytes;
}

float IAsset::GetSpeed() const
{
	return m_speed;
}

uint32_t IAsset::GetKiloBytes() const
{
	return m_kilo_bytes;
}

EAsset IAsset::GetAssetType() const
{
	return m_asset_type;
}
