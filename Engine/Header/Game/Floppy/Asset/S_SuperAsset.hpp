/// \file       S_SuperAsset.hpp
/// \date       08/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_S_SUPER_ASSET_HPP__
#define OOM_ENGINE_S_SUPER_ASSET_HPP__

#include "SDK/SDK.hpp"
#include "Game/Floppy/Asset/IAsset.hpp"

class S_SuperAsset : public CBehavior, public IAsset
{
public:

	void Awake    () final;
	void Start    () final;
	void Update   () final;
	void OnDestroy() final;
};

#endif // !OOM_ENGINE_S_SUPER_ASSET_HPP__
