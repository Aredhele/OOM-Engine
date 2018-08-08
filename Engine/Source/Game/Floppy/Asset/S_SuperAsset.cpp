/// \file       S_SuperAsset.cpp
/// \date       08/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#include "Game/Floppy/Asset/S_SuperAsset.hpp"

/* virtual */ void S_SuperAsset::Awake()
{
	SetAssetType(EAsset::SuperAsset);
}

/* virtual */ void S_SuperAsset::Start()
{
	// None
}

/* virtual */ void S_SuperAsset::Update()
{
	// None
}

/* virtual */ void S_SuperAsset::OnDestroy()
{
	// None
}
