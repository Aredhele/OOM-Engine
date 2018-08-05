/// \file       CPhysicWorld.cpp
/// \date       24/07/2018
/// \project    OOM-Engine
/// \package    Physics
/// \author     Vincent STEHLY--CALISTO

#include <QU3E/q3.h>

#include "Physics/CRigidBody.hpp"
#include "Physics/CPhysicWorld.hpp"
#include "Physics/CContactListener.hpp"

#include "Core/Debug/SLogger.hpp"
#include "Composite/Component/CTransform.hpp"

namespace Oom
{

/* static */ CPhysicWorld* CPhysicWorld::sp_instance = nullptr;

bool CPhysicWorld::Initialize(float delta_time)
{
    SLogger::LogInfo("Physic world initialization.");

    sp_instance = this;
    mp_scene    = new q3Scene(delta_time);
	mp_listener = new CContactListener();

	mp_scene->SetContactListener(mp_listener);

    SLogger::LogInfo("Physic world : Delta = %f ms - Gravity = %f", delta_time, -9.81f);
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
        // TODO : Rotation
        p_body->SetPosition(p_body->GetTransform()->GetPosition());
    }

    mp_scene->Step();

    // Update GO positions
    for(auto* p_body : m_bodies)
    {
        // TODO : Rotation
        const glm::vec3 translation = p_body->GetPosition() - p_body->GetTransform()->GetPosition();
        p_body->GetTransform()->Translate(translation);
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