/// \file       CBoxCollider.cpp
/// \date       01/08/2018
/// \project    OOM-Engine
/// \package    Physics
/// \author     Vincent STEHLY--CALISTO

#include <QU3E/q3.h>

#include "Physics/CRigidBody.hpp"
#include "Physics/CBoxCollider.hpp"
#include "Composite/CGameObject.hpp"

namespace Oom
{

void CBoxCollider::CreateBox()
{
	// If there is already a box, destroys it
	DestroyBox();

	// Check if there is a body, else nothing to do
	auto* p_body = GetGameObject()->GetComponent<CRigidBody>();

	if(p_body)
	{
		q3BoxDef box_def {};
		box_def.SetSensor     (m_sensor);
		box_def.SetDensity    (m_density);
		box_def.SetFriction   (m_friction);
		box_def.SetRestitution(m_restitution);

		// Setting the local space
		// Position
		q3Transform local_space;
		q3Identity (local_space);

		local_space.position.x = m_local_position.x;
		local_space.position.y = m_local_position.z;
		local_space.position.z = m_local_position.y;

		// Rotation
		glm::vec3 euler_qu3e;
		euler_qu3e.x = m_local_orientation.x;
		euler_qu3e.y = m_local_orientation.z;
		euler_qu3e.z = m_local_orientation.y;

		// Create the rotation matrix
		glm::mat3 rot = glm::orientate3(euler_qu3e);

		// Setting the rotation
		local_space.rotation.Set
		(
			rot[0].x, rot[1].x, rot[2].x,
			rot[0].y, rot[1].y, rot[2].y,
			rot[0].z, rot[1].z, rot[2].z
		);

		// Setting the box def
		box_def.Set(local_space, q3Vec3(m_extent.x, m_extent.z, m_extent.y));

		// Creating the box
		mp_box = p_body->mp_body->AddBox(box_def);
		mp_box->SetUserdata((void*)GetGameObject());
	}
}

void CBoxCollider::DestroyBox()
{
	// If the box is already nullptr,
	// nothing to do
	if(mp_box)
	{
		// Check if there is a body ... 
		auto* p_body = GetGameObject()->GetComponent<CRigidBody>();

		if(p_body)
		{
			p_body->mp_body->RemoveBox(mp_box);
			mp_box = nullptr;
		}
	}
}

void CBoxCollider::SetSensor(const bool sensor)
{
	m_sensor = sensor;
	DestroyBox();
	CreateBox ();
}

void CBoxCollider::SetDensity(const float density)
{
	m_density = density;
	DestroyBox();
	CreateBox ();
}

void CBoxCollider::SetFriction(const float friction)
{
	m_friction = friction;
	DestroyBox();
	CreateBox ();
}

void CBoxCollider::SetRestitution(const float restitution)
{
	m_restitution = restitution;
	DestroyBox();
	CreateBox ();
}

void CBoxCollider::SetExtent(const glm::vec3& extent)
{
	m_extent = extent;
	DestroyBox();
	CreateBox ();
}

void CBoxCollider::SetLocalPosition(const glm::vec3& position)
{
	m_local_position = position;
	DestroyBox();
	CreateBox ();
}

void CBoxCollider::SetLocalOrientation(const glm::vec3& orientation)
{
	m_local_orientation = orientation;
	DestroyBox();
	CreateBox ();
}

void CBoxCollider::IsSensor() const
{
	return m_sensor;
}

float CBoxCollider::GetDensity() const
{
	return m_density;
}

float CBoxCollider::GetFriction() const
{
	return m_friction;
}

float CBoxCollider::GetRestution() const
{
	return m_restitution;
}

const glm::vec3& CBoxCollider::GetExtent() const
{
	return m_extent;
}

const glm::vec3& CBoxCollider::GetLocalPosition() const
{
	return m_local_position;
}

const glm::vec3& CBoxCollider::GetLocalOrientation() const
{
	return m_local_orientation;
}

void Oom::CBoxCollider::OnEnable()
{
	// None
}

void Oom::CBoxCollider::OnDisable()
{
	// None
}

void Oom::CBoxCollider::_Register()
{
	mp_box              = nullptr;
	m_sensor            = false;
	m_density           = 1.0f;
	m_friction          = 0.4f;
	m_restitution       = 0.2f;
	m_extent            = glm::vec3(0.0f);
	m_local_position    = glm::vec3(0.0f);
	m_local_orientation = glm::vec3(0.0f);

	CreateBox();
}

void Oom::CBoxCollider::_Destroy()
{
	DestroyBox();
}

void CBoxCollider::OnBodyAttached()
{
	CreateBox();
}

void CBoxCollider::RemoveBoxHandle()
{
    mp_box = nullptr;
}

}
