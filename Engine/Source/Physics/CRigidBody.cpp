/// \file       CRigidBody.cpp
/// \date       24/07/2018
/// \project    OOM-Engine
/// \package    Physics
/// \author     Vincent STEHLY--CALISTO

#include "Render/Config.hpp"

#include <QU3E/q3.h>
#include <Glm/ext.hpp>
#include <GLM/gtx/euler_angles.hpp>

#include "Composite/CGameObject.hpp"

#include "Physics/CRigidBody.hpp"
#include "Physics/CPhysicWorld.hpp"

namespace Oom
{

/* virtual */ void CRigidBody::OnEnable()
{
    // Test ?
    mp_body->SetToSleep();
}

/* virtual */ void CRigidBody::OnDisable()
{
    // Test ?
    mp_body->SetToAwake();
}

/* virtual */ void CRigidBody::_Register()
{
    // Allocating the q3body
    // TODO : Make a method to recreate the body
    q3Scene*  p_scene = CPhysicWorld::GetScene();
    q3BodyDef body_def;

    // Getting the transform
    glm::vec3 world_position = mp_transform->GetWorldPosition();

    body_def.bodyType   = eDynamicBody;
    body_def.position.x = world_position.x;
    body_def.position.y = world_position.z;
    body_def.position.z = world_position.y;

    // TODO : Set rotation
    mp_body = p_scene->CreateBody(body_def);

    // Check if the game object has a collider
    std::vector<CRigidBody*> colliders = mp_game_object->GetComponents<CRigidBody>();

    // TODO : Add collider

    CPhysicWorld::RegisterBody(this);
}

/* virtual */ void CRigidBody::_Destroy()
{
    // Destroy the body
    if(mp_body)
    {
        q3Scene*  p_scene = CPhysicWorld::GetScene();

        p_scene->RemoveBody(mp_body);
        mp_body = nullptr;
    }

    CPhysicWorld::UnregisterBody(this);
}

CRigidBody::EBodyType CRigidBody::GetBodyType() const
{
    int32_t flags = mp_body->GetFlags();

    if(flags & eStaticBody)    return Static;    // NOLINT
    if(flags & eDynamicBody)   return Dynamic;   // NOLINT
    if(flags & eKinematicBody) return Kinematic; // NOLINT

    return Unknown;
}

glm::vec3 CRigidBody::GetAngularVelocity() const
{
    q3Vec3 v = mp_body->GetAngularVelocity();
    return glm::vec3(v.x, v.z, v.y);
}

float CRigidBody::GetGravityScale() const
{
    return mp_body->GetGravityScale();
}

glm::vec3 CRigidBody::GetLinearVelocity() const
{
    q3Vec3 v = mp_body->GetLinearVelocity();
    return glm::vec3(v.x, v.z, v.y);
}

float CRigidBody::GetMass() const
{
    return mp_body->GetMass();
}

bool CRigidBody::IsAwake() const
{
    return mp_body->IsAwake();
}

int32_t CRigidBody::GetLayers() const
{
    return mp_body->GetLayers();
}

glm::vec3 CRigidBody::GetPosition() const
{
    q3Vec3 p = mp_body->GetTransform().position;
    return glm::vec3(p.x, p.z, p.y);
}

glm::vec3 CRigidBody::GetRotation() const
{
    q3Mat3 r = mp_body->GetTransform().rotation;

    glm::vec3 ret;
    glm::mat3 mat(r[0][0], r[0][1], r[0][2],
                  r[1][0], r[1][1], r[1][2],
                  r[2][0], r[2][1], r[2][2]);

    glm::extractEulerAngleXYZ(glm::mat4(mat), ret.x, ret.z, ret.y);
    return ret;
}

void CRigidBody::AddTorque(const glm::vec3& torque)
{
    mp_body->ApplyTorque(q3Vec3(torque.x, torque.z, torque.y));
}

void CRigidBody::AddLinearForce(const glm::vec3& force)
{
    mp_body->ApplyLinearForce(q3Vec3(force.x, force.z, force.y));
}

void CRigidBody::AddLinearImpulse(const glm::vec3 &impulse)
{
    mp_body->ApplyLinearImpulse(q3Vec3(impulse.x, impulse.z, impulse.y));
}

void CRigidBody::AddForceAtPosition(const glm::vec3& force, const glm::vec3& point)
{
    mp_body->ApplyForceAtWorldPoint(
            q3Vec3(force.x, force.z, force.y),
            q3Vec3(point.x, point.z, point.y));
}

void CRigidBody::AddLinearImpulseAtPosition(const glm::vec3& impulse,
                                            const glm::vec3& point)
{
    mp_body->ApplyLinearImpulseAtWorldPoint(
            q3Vec3(impulse.x, impulse.z, impulse.y),
            q3Vec3(point.x,   point.z,   point.y  ));
}

void CRigidBody::SetGravityScale(float gravity_scale)
{
    mp_body->SetGravityScale(gravity_scale);
}

void CRigidBody::SetLinearVelocity(const glm::vec3& velocity)
{
    mp_body->SetLinearVelocity(q3Vec3(velocity.x, velocity.z, velocity.y));
}

void CRigidBody::SetAngularVelocity(const glm::vec3& velocity)
{
    mp_body->SetAngularVelocity(q3Vec3(velocity.x, velocity.z, velocity.y));
}

void CRigidBody::SetLayers(int32_t layers)
{
    mp_body->SetLayers(layers);
}

void CRigidBody::Sleep()
{
    mp_body->SetToSleep();
}

void CRigidBody::Awake()
{
    mp_body->SetToAwake();
}

void CRigidBody::SetPosition(const glm::vec3& position)
{
    mp_body->SetTransform(q3Vec3(position.x, position.z, position.y));
}

void CRigidBody::SetRotation(const glm::vec3& rotation)
{
    q3Vec3 position = mp_body->GetTransform().position;

    q3Vec3 axis_x = (rotation.x != 0.0f) ? q3Vec3(1.0f, 0.0f, 0.0f): q3Vec3(0.0f, 0.0f, 0.0f);
    q3Vec3 axis_y = (rotation.z != 0.0f) ? q3Vec3(0.0f, 1.0f, 0.0f): q3Vec3(0.0f, 0.0f, 0.0f);
    q3Vec3 axis_z = (rotation.y != 0.0f) ? q3Vec3(0.0f, 0.0f, 1.0f): q3Vec3(0.0f, 0.0f, 0.0f);

    mp_body->SetTransform(position, axis_x, glm::radians(rotation.x));
    mp_body->SetTransform(position, axis_y, glm::radians(rotation.z));
    mp_body->SetTransform(position, axis_z, glm::radians(rotation.y));
}

}