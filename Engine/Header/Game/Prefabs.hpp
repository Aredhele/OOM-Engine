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