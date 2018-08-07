/// \file       S_Spawner.cpp
/// \date       07/08/2018
/// \project    OOM-Engine
/// \package    Built-in/SCirpt
/// \author     Vincent STEHLY--CALISTO

#include "Built-in/Script/S_Spawner.hpp"

/*virtual */ void S_Spawner::Start()
{
	// Spawn the first
	auto* p_cube = Sdk::Import::ImportMesh("Resources/Mesh/Cube.obj")[0];

	// Drop it
	p_cube->GetTransform().SetPosition(0.0f, 0.0f, 13.0f);

	auto* p_cube_body = p_cube->AddComponent<CRigidBody>();
	auto* p_cube_box  = p_cube->AddComponent<CBoxCollider>();
}

/*virtual */ void S_Spawner::Update()
{
	const glm::vec3 pos = glm::vec3(10.0f, 10.0f, 10.0f);
	const glm::vec3 dir = glm::normalize(glm::vec3(0.0f) - pos);

	// Display the raycast
	Sdk::Debug::DrawRay(pos, dir * 20.0f, glm::vec3(1.0f));

	CRayCast ray_cast = Sdk::Physic::RayCast(pos, dir * 20.0f);
	if (ray_cast.GetGameObject())
	{
		Destroy(ray_cast.GetGameObject());

		auto* p_cube = Sdk::Import::ImportMesh("Resources/Mesh/Cube.obj")[0];
		p_cube->GetTransform().SetPosition(0.0f, 0.0f, 13.0f);

		auto* p_cube_body = p_cube->AddComponent<CRigidBody>();
		auto* p_cube_box = p_cube->AddComponent<CBoxCollider>();
	}
}

/*virtual */ void S_Spawner::OnCollisionEnter(const CCollision& collision)
{
	Sdk::Debug::LogUser("OnCollisionEnter");
}
