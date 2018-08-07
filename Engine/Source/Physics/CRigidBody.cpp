/// \file       CRigidBody.cpp
/// \date       24/07/2018
/// \project    OOM-Engine
/// \package    Physics
/// \author     Vincent STEHLY--CALISTO

#include "Render/Config.hpp"

#include <QU3E/q3.h>
#include <Glm/ext.hpp>
#include <GLM/gtx/euler_angles.hpp>

#include "Physics/CRigidBody.hpp"
#include "Physics/CPhysicWorld.hpp"
#include "Physics/CBoxCollider.hpp"

#include "Composite/CGameObject.hpp"

namespace Oom
{

void CRigidBody::CreateBody()
{
	DestroyBody();

	q3Scene* p_scene = CPhysicWorld::GetScene();

	// If there is no scene... what the hell ?
	if(p_scene)
	{
		q3BodyDef body_def {};

		// Getting the game object position
		const glm::vec3 position = mp_transform->GetPosition();

		switch(m_body_type)
		{
			case Static:     body_def.bodyType = eStaticBody;    break;
			case Dynamic:    body_def.bodyType = eDynamicBody;   break;
			case Kinematic:  body_def.bodyType = eKinematicBody; break;
		}

		body_def.position.x        = position.x;
		body_def.position.y        = position.z;
		body_def.position.z        = position.y;

		body_def.lockAxisX         = m_lock_x;
		body_def.lockAxisY         = m_lock_z;
		body_def.lockAxisZ         = m_lock_y;

		body_def.linearVelocity.x  = m_linear_velocity.x;
		body_def.linearVelocity.y  = m_linear_velocity.z;
		body_def.linearVelocity.z  = m_linear_velocity.y;

		body_def.angularVelocity.x = m_angular_velocity.x;
		body_def.angularVelocity.y = m_angular_velocity.z;
		body_def.angularVelocity.z = m_angular_velocity.y;

		body_def.layers            = m_layers;
		body_def.gravityScale      = m_gravity_scale;
		body_def.linearDamping     = m_linear_damping;
		body_def.angularDamping    = m_angular_damping;
		body_def.userData          = (void*)GetGameObject();

		mp_body = p_scene->CreateBody(body_def);

		for (auto* p_collider : mp_game_object->GetComponents<CBoxCollider>())
			p_collider->OnBodyAttached();
	}
}

void CRigidBody::DestroyBody()
{
	if (mp_body)
	{
		q3Scene* p_scene = CPhysicWorld::GetScene();

		if(p_scene)
		{
			for (auto* p_collider : mp_game_object->GetComponents<CBoxCollider>())
				p_collider->RemoveBoxHandle();

			p_scene->RemoveBody(mp_body);
			mp_body = nullptr;
		}
	}
}

/* virtual */ void CRigidBody::OnEnable()
{
    mp_body->SetToSleep();
}

/* virtual */ void CRigidBody::OnDisable()
{
    mp_body->SetToAwake();
}

/* virtual */ void CRigidBody::_Register()
{
	// Default values
	mp_body            = nullptr;
	m_lock_x           = false;
	m_lock_y           = false;
	m_lock_z           = false;
	m_linear_damping   = 0.0f;
	m_gravity_scale    = 1.0f;
	m_angular_damping  = 0.1f;
	m_layers           = 0x000000001;
	m_body_type        = EBodyType::Dynamic;
	m_linear_velocity  = glm::vec3(0.0f);
	m_angular_velocity = glm::vec3(0.0f);

	CreateBody();

	// Registering the body
    CPhysicWorld::RegisterBody(this);
}

/* virtual */ void CRigidBody::_Destroy()
{
	// Destroying the body
	DestroyBody();

	// Unregister the body
	CPhysicWorld::UnregisterBody(this);
}

bool CRigidBody::IsAwake() const
{
	return mp_body->IsAwake();
}

bool CRigidBody::IsXLocked() const
{
	return m_lock_x;
}

bool CRigidBody::IsYLocked() const
{
	return m_lock_y;
}

bool CRigidBody::IsZLocked() const
{
	return m_lock_z;
}

float CRigidBody::GetMass() const
{
	return mp_body->GetMass();
}

float CRigidBody::GetGravityScale() const
{
	return m_gravity_scale;
}

float CRigidBody::GetLinearDamping() const
{
	return m_linear_damping;
}

float CRigidBody::GetAngularDamping() const
{
	return m_angular_damping;
}

CRigidBody::EBodyType CRigidBody::GetBodyType() const
{
	const int32_t flags = mp_body->GetFlags();

	if (flags & eStaticBody)    return Static;    // NOLINT
	if (flags & eDynamicBody)   return Dynamic;   // NOLINT
	if (flags & eKinematicBody) return Kinematic; // NOLINT

	return Dynamic;
}

int32_t CRigidBody::GetLayers() const
{
	return m_layers;
}

glm::vec3 CRigidBody::GetPosition() const
{
	const q3Vec3 p = mp_body->GetTransform().position;
	return glm::vec3(p.x, p.z, p.y);
}

glm::vec3 CRigidBody::GetOrientation() const
{
	q3Mat3 r = mp_body->GetTransform().rotation;

	glm::vec3 ret;
	glm::mat3 mat3
	(
		r[0][0], r[1][0], r[2][0],
		r[0][1], r[1][1], r[2][1],
		r[0][2], r[1][2], r[2][2]
	);

	glm::extractEulerAngleXYZ(glm::mat4(mat3), ret.x, ret.z, ret.y);
	return ret;
}

glm::vec3 CRigidBody::GetAngularVelocity() const
{
	const q3Vec3 v = mp_body->GetAngularVelocity();
	return glm::vec3(v.x, v.z, v.y);
}

glm::vec3 CRigidBody::GetLinearVelocity() const
{
	const q3Vec3 v = mp_body->GetLinearVelocity();
	return glm::vec3(v.x, v.z, v.y);
}

void CRigidBody::Sleep()
{
	mp_body->SetToSleep();
}

void CRigidBody::Awake()
{
	mp_body->SetToAwake();
}

void CRigidBody::SetLockX(bool lock)
{
	m_lock_x = lock;
	DestroyBody();
	CreateBody ();
}

void CRigidBody::SetLockY(bool lock)
{
	m_lock_y = lock;
	DestroyBody();
	CreateBody ();
}

void CRigidBody::SetLockZ(bool lock)
{
	m_lock_z = lock;
	DestroyBody();
	CreateBody ();
}

void CRigidBody::SetLayers(int32_t layers)
{
	m_layers = layers;
	mp_body->SetLayers(m_layers);
}

void CRigidBody::SetBodyType(EBodyType body_type)
{
	m_body_type = body_type;
	DestroyBody();
	CreateBody ();
}

void CRigidBody::SetGravityScale(float gravity_scale)
{
	m_gravity_scale = gravity_scale;
	mp_body->SetGravityScale(m_gravity_scale);
}

void CRigidBody::SetLinearDamping(const float damping)
{
	m_linear_damping = damping;
	mp_body->SetLinearDamping(m_linear_damping);
}

void CRigidBody::SetAngularDamping(const float damping)
{
	m_angular_damping = damping;
	mp_body->SetAngularDamping(m_linear_damping);
}

void CRigidBody::SetPosition(const glm::vec3& position)
{
	mp_body->SetTransform(q3Vec3(position.x, position.z, position.y));
}

void CRigidBody::SetOrientation(const glm::vec3& rotation)
{
	const q3Vec3 position = mp_body->GetTransform().position;
	const q3Vec3 axis_x   = (rotation.x != 0.0f) ? q3Vec3(1.0f, 0.0f, 0.0f) : q3Vec3(0.0f, 0.0f, 0.0f);
	const q3Vec3 axis_y   = (rotation.z != 0.0f) ? q3Vec3(0.0f, 1.0f, 0.0f) : q3Vec3(0.0f, 0.0f, 0.0f);
	const q3Vec3 axis_z   = (rotation.y != 0.0f) ? q3Vec3(0.0f, 0.0f, 1.0f) : q3Vec3(0.0f, 0.0f, 0.0f);

	/*mp_body->SetTransform(position, axis_x, rotation.x);
	mp_body->SetTransform(position, axis_y, rotation.z);
	mp_body->SetTransform(position, axis_z, rotation.y);*/

	mp_body->SetTransform(position, q3Vec3(0.0f, 0.0f, 1.0f), 45.0f);
}

void CRigidBody::SetLinearVelocity(const glm::vec3& velocity)
{
	m_linear_velocity = velocity;
	mp_body->SetLinearVelocity(q3Vec3
	(
		m_linear_velocity.x,
		m_linear_velocity.z,
		m_linear_velocity.y
	));
}

void CRigidBody::SetAngularVelocity(const glm::vec3& velocity)
{
	m_angular_velocity = velocity;
	mp_body->SetAngularVelocity(q3Vec3(
		m_angular_velocity.x,
		m_angular_velocity.z,
		m_angular_velocity.y
	));
}

void CRigidBody::AddTorque(const glm::vec3& torque)
{
	mp_body->ApplyTorque(q3Vec3(torque.x, torque.z, torque.y));
}

void CRigidBody::AddLinearForce(const glm::vec3& force)
{
	mp_body->ApplyLinearForce(q3Vec3(force.x, force.z, force.y));
}

void CRigidBody::AddLinearImpulse(const glm::vec3& impulse)
{
	mp_body->ApplyLinearImpulse(q3Vec3(impulse.x, impulse.z, impulse.y));
}

void CRigidBody::AddForceAtPosition(const glm::vec3& force, const glm::vec3& point)
{
	mp_body->ApplyForceAtWorldPoint(
		q3Vec3(force.x, force.z, force.y),
		q3Vec3(point.x, point.z, point.y));
}

void CRigidBody::AddLinearImpulseAtPosition(const glm::vec3& impulse, const glm::vec3& point)
{
	mp_body->ApplyLinearImpulseAtWorldPoint(
		q3Vec3(impulse.x, impulse.z, impulse.y),
		q3Vec3(point.x,   point.z,   point.y  ));
}

}
