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
	mp_game_object = nullptr;
    m_scale        = glm::vec3(1.0f);
    m_position     = glm::vec3(0.0f);
    m_orientation  = glm::vec3(0.0f);
    m_up           = glm::vec3(0.0f, 0.0f, 1.0f);
    m_right        = glm::vec3(1.0f, 0.0f, 0.0f);
    m_forward      = glm::vec3(0.0f, 1.0f, 0.0f);
	m_target       = glm::vec3(0.0f, 5.0f, 0.0f);
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

const glm::vec3& CTransform::GetOrientation() const 
{
    return m_orientation;
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
	const glm::vec3 old = m_orientation;
    m_orientation = orientation;

	RotateTarget(m_orientation - old);
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
	glm::vec3 a = glm::normalize(target   - m_position);
	glm::vec3 b = glm::normalize(m_target - m_position);

	const auto quaternion = glm::rotation(b, a);
	const glm::vec3 euler = glm::eulerAngles(quaternion);

	m_orientation.x += euler.x;
	m_orientation.y += euler.z;
	m_orientation.z += euler.y;

	RotateTarget(euler);
}

void CTransform::Rotate(float x, float y, float z)
{
    Rotate(glm::vec3(x, y, z));
}

void CTransform::Rotate(const glm::vec3& rotation)
{
	m_orientation.x += rotation.x;
	m_orientation.y += rotation.z;
	m_orientation.z += rotation.y;

	RotateTarget (rotation);
}

void CTransform::RotateAround(const glm::vec3& point, const glm::vec3& axis, float angle)
{
	const glm::vec3 old = m_position;

	m_position -= point;
	m_position  = glm::rotate(m_position, angle, axis);
	m_position += point;

	TranslateTarget(m_position - old);
}

void CTransform::Translate(float x, float y, float z)
{
    Translate(glm::vec3(x, y, z));
}

void CTransform::Translate(const glm::vec3& translation)
{
    m_position += translation;
	TranslateTarget(translation);
}

void CTransform::RotateTarget(const glm::vec3& rotation)
{
	m_target -= m_position;
	m_target  = glm::rotateX(m_target, rotation.x);
	m_target  = glm::rotateY(m_target, rotation.y);
	m_target  = glm::rotateZ(m_target, rotation.z);
	m_target += m_position;

	m_up      = glm::rotateX(m_up, rotation.x);
	m_up      = glm::rotateY(m_up, rotation.y);
	m_up      = glm::rotateZ(m_up, rotation.z);
	m_right   = glm::rotateX(m_right, rotation.x);
	m_right   = glm::rotateY(m_right, rotation.y);
	m_right   = glm::rotateZ(m_right, rotation.z);
	m_forward = glm::rotateX(m_forward, rotation.x);
	m_forward = glm::rotateY(m_forward, rotation.y);
	m_forward = glm::rotateZ(m_forward, rotation.z);
}

void CTransform::TranslateTarget(const glm::vec3& translation)
{
	m_target      += translation;
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
	const glm::mat4 rotation_matrix    = glm::orientate4(m_orientation);
	const glm::mat4 scale_maxtrix      = glm::scale     (m_scale);

	// The order is IMPORTANT
    return translation_matrix * rotation_matrix * scale_maxtrix;
}

void CTransform::SetUp(const glm::vec3& up)
{
	m_up = up;
}

void CTransform::SetRight(const glm::vec3& right)
{
	m_right = right;
}

void CTransform::SetForward(const glm::vec3& forward)
{
	m_forward = forward;
}

}
