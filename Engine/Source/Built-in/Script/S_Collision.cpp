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
	// None
}

/*virtual */ void S_Collision::OnCollisionEnter(const CCollision& collision)
{
	Sdk::Debug::LogUser("OnCollisionEnter");
}
