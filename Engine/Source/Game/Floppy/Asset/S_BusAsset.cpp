/// \file       S_BusAsset.cpp
/// \date       08/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#include "Game/Floppy/Asset/S_BusAsset.hpp"

/* virtual */ void S_BusAsset::Awake()
{
	SetAssetType(EAsset::BusAsset);
}

/* virtual */ void S_BusAsset::Start()
{
	// None
}

/* virtual */ void S_BusAsset::Update()
{
	// None
}

/* virtual */ void S_BusAsset::OnDestroy()
{
	// None
}
