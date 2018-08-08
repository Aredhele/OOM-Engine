/// \file       S_ConveyorAsset.cpp
/// \date       08/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#include "Game/Floppy/Asset/S_ConveyorAsset.hpp"

/* virtual */ void S_ConveyorAsset::Awake()
{
	SetAssetType(EAsset::ConveyorAsset);
}

/* virtual */ void S_ConveyorAsset::Start()
{
	// None
}

/* virtual */ void S_ConveyorAsset::Update()
{
	// None
}

/* virtual */ void S_ConveyorAsset::OnDestroy()
{
	// None
}
