/// \file       IAsset.cpp
/// \date       08/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#include "Game/Floppy/Asset/IAsset.hpp"

void IAsset::SetAssetType(EAsset asset_type)
{
	m_asset_type = asset_type;
}

IAsset::EAsset IAsset::GetAssetType() const
{
	return m_asset_type;
}
