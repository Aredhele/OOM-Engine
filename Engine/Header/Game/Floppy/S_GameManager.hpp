/// \file       S_GameManager.hpp
/// \date       08/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_S_GAME_MANAGER_HPP__
#define OOM_ENGINE_S_GAME_MANAGER_HPP__

#include "SDK/SDK.hpp"

class S_GameManager : public CBehavior
{
public:

	void Awake     () final;	
	void Start     () final;
	void Update    () final;
	void OnDestroy () final;

private:

	CGameObject* mp_floppy;
};

#endif // !OOM_ENGINE_S_GAME_MANAGER_HPP__
