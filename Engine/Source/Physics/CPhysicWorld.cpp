/// \file       CPhysicWorld.cpp
/// \date       24/07/2018
/// \project    OOM-Engine
/// \package    Physics
/// \author     Vincent STEHLY--CALISTO

#include <QU3E/q3.h>

#include "Physics/CRigidBody.hpp"
#include "Physics/CBoxCollider.hpp"
#include "Physics/CPhysicWorld.hpp"
#include "Physics/CContactListener.hpp"

#include "Core/Debug/SLogger.hpp"
#include "Composite/CGameObject.hpp"
#include "Composite/Component/CTransform.hpp"
#include "Render/Gizmos/CGizmosCollider.hpp"

namespace Oom
{

/* static */ CPhysicWorld* CPhysicWorld::sp_instance = nullptr;

/* static */ void CPhysicWorld::RayCast(q3QueryCallback* p_callback, q3RaycastData* p_ray_cast_data)
{
	sp_instance->mp_scene->RayCast(p_callback, *p_ray_cast_data);
}

bool CPhysicWorld::Initialize(const SPhysicWorldCreateInfo& world_create_info)
{
    SLogger::LogInfo("Physic world initialization.");

    sp_instance = this;
    mp_scene    = new q3Scene(world_create_info.delta_time);
	mp_listener = new CContactListener();

	// Setting the gravity
	mp_scene->SetGravity(q3Vec3(
		world_create_info.gravity_x, 
		world_create_info.gravity_z, 
		world_create_info.gravity_y));

	// Listener for collision callback
	mp_scene->SetContactListener(mp_listener);

    SLogger::LogInfo("Physic world : Delta = %f ms - Gravity = %f", world_create_info.delta_time, world_create_info.gravity_z);
    SLogger::LogInfo("Physic world initialization.");

    return true;
}

void CPhysicWorld::Release()
{
    SLogger::LogInfo("Releasing physic world.");

    mp_scene->Shutdown();
    delete mp_scene;

    mp_scene    = nullptr;
    sp_instance = nullptr;

    SLogger::LogInfo("Renderer physic world.");
}

void CPhysicWorld::Update()
{
	// Update body positions
	for(auto* p_body : m_bodies)
	{
		// Rotation ... ? Rotate the body instead !
	    p_body->SetPosition(p_body->GetTransform()->GetPosition());
	}

	mp_scene->Step();

	// Update GO positions
	for(auto* p_body : m_bodies)
	{
		const glm::vec3 orientation = p_body->GetOrientation();
	    const glm::vec3 translation = p_body->GetPosition   () - p_body->GetTransform()->GetPosition();

		// It just works !
	    p_body->GetTransform()->Translate(translation);
		p_body->GetTransform()->SetOrientation(orientation);

		// Drawing debug
		for(auto* p_collider : p_body->GetGameObject()->GetComponents<CBoxCollider>())
		{
		/*	DrawCollider(
				p_collider->GetTransform()->GetPosition(),
				p_collider->GetExtent(),
				p_collider->GetTransform()->GetEulerAngles(),
				glm::vec3(0.1f, 0.1f, 0.9f));*/
		}
	}
}

/* static */ q3Scene* CPhysicWorld::GetScene()
{
    return sp_instance->mp_scene;
}

/* static */ void CPhysicWorld::RegisterBody(CRigidBody* p_body)
{
    sp_instance->m_bodies.push_back(p_body);
}

/* static */ void CPhysicWorld::UnregisterBody(CRigidBody* p_body)
{
    std::vector<CRigidBody*>& bodies = sp_instance->m_bodies;

    for(auto i = 0; i < bodies.size(); ++i)
    {
        if(bodies[i] == p_body)
        {
            bodies[i] = bodies.back();
            bodies.pop_back();
            break;
        }
    }
}

}
