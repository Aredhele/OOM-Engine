/// \file       S_Collision.cpp
/// \date       06/08/2018
/// \project    OOM-Engine
/// \package    Built-in/SCirpt
/// \author     Vincent STEHLY--CALISTO

#include "Built-in/Script/S_Collision.hpp"

/*virtual */ void S_Collision::Start()
{
	// None
}

/*virtual */ void S_Collision::Update()
{
	const glm::vec3 pos = glm::vec3(10.0f, 10.0f, 10.0f);
	const glm::vec3 dir = glm::normalize(glm::vec3(0.0f) - pos);
	Sdk::Debug::DrawRay(pos, dir * 20.0f, glm::vec3(1.0f));
}

/*virtual */ void S_Collision::OnCollisionEnter(const CCollision& collision)
{
	Sdk::Debug::LogUser("OnCollisionEnter");
}
