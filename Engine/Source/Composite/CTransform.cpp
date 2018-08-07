/// \file       CTransform.cpp
/// \date       22/07/2018
/// \project    OOM-Engine
/// \package    Composite
/// \author     Vincent STEHLY--CALISTO

#include "Composite/CGameObject.hpp"
#include "Composite/Component/CTransform.hpp"

namespace Oom
{

CTransform::CTransform()
{
	mp_game_object  = nullptr;
	m_scale         = glm::vec3(1.0f);
	m_position      = glm::vec3(0.0f);
	m_orientation   = glm::vec3(0.0f);
	m_up            = glm::vec3(0.0f, 0.0f, 1.0f);
	m_right         = glm::vec3(1.0f, 0.0f, 0.0f);
	m_forward       = glm::vec3(0.0f, 1.0f, 0.0f);
	m_target        = glm::vec3(0.0f, 5.0f, 0.0f);
	m_q_orientation = glm::quat(glm::vec3(0.0f, 0.0f, 0.0f));
}

const glm::vec3& CTransform::GetUp() const
{
	return m_up;
}

const glm::vec3& CTransform::GetRight() const
{
	return m_right;
}

const glm::vec3 &CTransform::GetForward() const
{

	return m_forward;
}

const glm::vec3& CTransform::GetTarget() const
{
	return m_target;
}

const glm::vec3& CTransform::GetPosition() const
{
	return m_position;
}

const glm::vec3& CTransform::GetScale() const
{
	return m_scale;
}

glm::vec3 CTransform::GetEulerAngles() const
{
	return glm::degrees(glm::eulerAngles(m_q_orientation));
}

const glm::quat& CTransform::GetOrientation() const
{
	return m_q_orientation;
}

void CTransform::SetScale(float x, float y, float z)
{
	SetScale(glm::vec3(x, y, z));
}

void CTransform::SetScale(const glm::vec3& scale)
{
	m_scale = scale;
}

void CTransform::SetPosition(float x, float y, float z)
{
	SetPosition(glm::vec3(x, y, z));
}

void CTransform::SetPosition(const glm::vec3& position)
{
	Translate(position - m_position);
}

void CTransform::SetOrientation(float x, float y, float z)
{
	SetOrientation(glm::vec3(x, y, z));
}

void CTransform::SetOrientation(const glm::vec3& orientation)
{
	m_q_orientation = glm::quat(orientation);
	UpdateVectors();
}

void CTransform::LookAt(float x, float y, float z)
{
	LookAt(glm::vec3(x, y, z));
}

void CTransform::LookAt(const CTransform& target)
{
	LookAt(target.m_position);
}

void CTransform::LookAt(const glm::vec3& target)
{
	// Safe look at
	glm::vec3   direction        = target - m_position;
	const float direction_length = glm::length(direction);

	// Normalizing
	direction /= direction_length;
	m_q_orientation = glm::quatLookAt(direction, glm::vec3(0.0f, 0.0f, 1.0f));

	UpdateVectors();
}

void CTransform::Rotate(float x, float y, float z)
{
	Rotate(glm::vec3(x, y, z));
}

void CTransform::Rotate(const glm::vec3& rotation)
{
	m_q_orientation = glm::normalize(m_q_orientation * glm::quat(rotation));
	UpdateVectors();
}

void CTransform::RotateAround(const glm::vec3& point, const glm::vec3& axis, float angle)
{
	const glm::vec3 old = m_position;

	m_position -= point;
	m_position  = glm::rotate(m_position, angle, axis);
	m_position += point;
	UpdateVectors();
}

void CTransform::Translate(float x, float y, float z)
{
	Translate(glm::vec3(x, y, z));
}

void CTransform::Translate(const glm::vec3& translation)
{
	m_position += translation;
}

void CTransform::UpdateVectors()
{
	// It's possible to do that since quaternion store
	// the rotation from their initial states
	m_up      = glm::normalize(m_q_orientation * glm::vec3(0.0f, 0.0f, 1.0f));
	m_right   = glm::normalize(m_q_orientation * glm::vec3(1.0f, 0.0f, 0.0f));
	m_forward = glm::normalize(m_q_orientation * glm::vec3(0.0f, 1.0f, 0.0f));
}

/* virtual */ void CTransform::_Register()
{
	// None
}

/* virtual */ void CTransform::_Destroy()
{
	// None
}

glm::mat4 CTransform::GetLocalToWorldMatrix() const
{
	const glm::mat4 translation_matrix = glm::translate (m_position);
	const glm::mat4 rotation_matrix    = glm::toMat4    (m_q_orientation);
	const glm::mat4 scale_maxtrix      = glm::scale     (m_scale);

	// The order is IMPORTANT
	return translation_matrix * rotation_matrix * scale_maxtrix;
}

}
