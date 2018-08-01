/// \file       CBoxCollider.cpp
/// \date       01/08/2018
/// \project    OOM-Engine
/// \package    Physics
/// \author     Vincent STEHLY--CALISTO

#include "QU3E/q3.h"
#include "Physics/CRigidBody.hpp"
#include "Physics/CPhysicWorld.hpp"
#include "Physics/CBoxCollider.hpp"
#include "Composite/CGameObject.hpp"

namespace Oom
{

void Oom::CBoxCollider::OnEnable()
{
    auto* p_body = GetGameObject()->GetComponent<CRigidBody>();

    if(p_body)
    {
        q3Transform local_space;
        glm::vec3 position = p_body->GetPosition();
        local_space.position = q3Vec3(position.x, position.z, position.y);
        // TODO : Rotation

        m_box_def.Set(local_space, q3Vec3(1.0f, 1.0f, 1.0f));
        mp_box = p_body->mp_body->AddBox(m_box_def);
    }
}

void Oom::CBoxCollider::OnDisable()
{
    auto* p_body = GetGameObject()->GetComponent<CRigidBody>();

    if(p_body && mp_box)
    {
        if(mp_box)
        {
            p_body->mp_body->RemoveBox(mp_box);
            mp_box = nullptr;
        }
    }
}

void Oom::CBoxCollider::_Register()
{
    mp_box = nullptr;
    m_box_def.SetRestitution(0.0f);
    m_box_def.SetDensity    (1.0f);
    m_box_def.SetFriction   (0.4f);
    m_box_def.SetSensor     (false);

    q3Transform local_space;
    auto* p_body = GetGameObject()->GetComponent<CRigidBody>();

    if(p_body)
    {
        glm::vec3 position = p_body->GetPosition();
        local_space.position = q3Vec3(position.x, position.z, position.y);

        // TODO : Rotation
    }
    else
    {
        q3Identity (local_space);
    }

    m_box_def.Set(local_space, q3Vec3(1.0f, 1.0f, 1.0f));

    if(p_body)
    {
        mp_box = p_body->mp_body->AddBox(m_box_def);
    }
}

void Oom::CBoxCollider::_Destroy()
{
    auto* p_body = GetGameObject()->GetComponent<CRigidBody>();

    if(p_body && mp_box)
    {
        p_body->mp_body->RemoveBox(mp_box);
        mp_box = nullptr;
    }
}

void CBoxCollider::OnBodyAttached()
{
    auto* p_body = GetGameObject()->GetComponent<CRigidBody>();

    if(p_body && IsEnabled() && mp_box == nullptr)
    {
        q3Transform local_space;
        glm::vec3 position = p_body->GetPosition();
        local_space.position = q3Vec3(position.x, position.z, position.y);

        // TODO : Rotation

        m_box_def.Set(local_space, q3Vec3(1.0f, 1.0f, 1.0f));
        mp_box = p_body->mp_body->AddBox(m_box_def);
    }
}

void CBoxCollider::RemoveBoxHandle()
{
    mp_box = nullptr;
}

}
