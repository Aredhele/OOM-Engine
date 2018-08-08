/// \file       IAsset.hpp
/// \date       08/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_I_ASSET_HPP__
#define OOM_ENGINE_I_ASSET_HPP__

#include "SDK/SDK.hpp"

class IAsset
{
public:

	enum EAsset
	{
		BusAsset,
		SuperAsset,
		ConveyorAsset
	};

public:

	void SetAssetType(EAsset asset_type);

public:

	EAsset GetAssetType() const;

protected:

	EAsset m_asset_type;
};

#endif // !OOM_ENGINE_S_ASSET_HPP__
