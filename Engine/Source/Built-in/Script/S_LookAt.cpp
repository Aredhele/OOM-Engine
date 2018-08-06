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

	Sdk::Debug::DrawBox(GetTransform()->GetTarget(), 0.2f, 0.2f, glm::vec3(0.0f, 0.0f, 1.0f));
	Sdk::Debug::DrawRay(GetTransform()->GetPosition(), GetTransform()->GetUp()      * 5.0, glm::vec3(0.0f, 1.0f, 0.0f));
	Sdk::Debug::DrawRay(GetTransform()->GetPosition(), GetTransform()->GetRight()   * 5.0, glm::vec3(0.0f, 0.0f, 1.0f));
	Sdk::Debug::DrawRay(GetTransform()->GetPosition(), GetTransform()->GetForward() * 5.0, glm::vec3(1.0f, 0.0f, 0.0f));
}

void S_LookAt::SetTarget(Oom::CGameObject* p_game_object)
{
	mp_target = p_game_object;
}
