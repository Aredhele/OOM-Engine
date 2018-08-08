/// \file       S_GameManager.hpp
/// \date       08/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#include "SDK/SDK.hpp"
#include "Game/Asset.hpp"

namespace Game::Prefabs {
	
	CGameObject& CreatePlayer();
	
	CGameObject& CreateCB_Asset(Asset::Size size);
	CGameObject& CreateRoadAsset(Asset::Size size);
	CGameObject& CreateBigAsset();
}

namespace Game::Prefabs::priv
{
	CGameObject& CreateAsset(Asset::Size size);
}