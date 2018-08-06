/// \file       S_LookAt.cpp
/// \date       06/08/2018
/// \project    OOM-Engine
/// \package    Composite
/// \author     Vincent STEHLY--CALISTO

#include "SDK/SDK.hpp"

/*virtual */ void S_LookAt::Start()
{
	GetTransform()->LookAt(mp_target->GetTransform());
}

/*virtual */ void S_LookAt::Update()
{
	GetTransform()->LookAt(mp_target->GetTransform());
}

void S_LookAt::SetTarget(Oom::CGameObject* p_game_object)
{
	mp_target = p_game_object;
}
