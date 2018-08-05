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
    m_scale        = glm::vec3(1.0f);
    m_position     = glm::vec3(0.0f);
    m_orientation  = glm::vec3(0.0f);
    m_up           = glm::vec3(0.0f, 0.0f, 1.0f);
    m_right        = glm::vec3(1.0f, 0.0f, 0.0f);
    m_forward      = glm::vec3(0.0f, 1.0f, 0.0f);
    mp_game_object = nullptr;

	UpdateVectors();
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
    m_position = position;
    UpdateVectors();
}

void CTransform::SetOrientation(float x, float y, float z)
{
    SetOrientation(glm::vec3(x, y, z));
}

void CTransform::SetOrientation(const glm::vec3& orientation)
{
    m_orientation = orientation;
    UpdateVectors();
}

void CTransform::LookAt(float x, float y, float z)
{
	LookAt(glm::vec3(x, y, z));
}

void CTransform::LookAt(const glm::vec3& target)
{
	m_forward = target;
	UpdateVectors();
}

void CTransform::LookAt(const CTransform& target)
{
    m_forward = target.m_position;
    UpdateVectors();
}

void CTransform::Rotate(float x, float y, float z)
{
    Rotate(glm::vec3(x, y, z));
}

void CTransform::Rotate(const glm::vec3& point)
{
    m_orientation += point;
    m_test        += point;
    UpdateVectors();
}

void CTransform::RotateAround(const glm::vec3& point, const glm::vec3& axis, float angle)
{
    m_forward -= m_position;
    m_forward  = glm::rotate(point, angle, axis);
    m_forward += m_position;
    UpdateVectors();
}

void CTransform::Translate(float x, float y, float z)
{
    Translate(glm::vec3(x, y, z));
}

void CTransform::Translate(const glm::vec3& translation)
{
    m_position += translation;
    m_forward  += translation;
    UpdateVectors();
}

void CTransform::UpdateVectors()
{
    m_orientation  = m_forward;
    m_orientation -= m_position;
    m_orientation  = glm::normalize(m_orientation);

    m_up    = glm::vec3     (0.0f, 0.0f, 1.0f);
    m_right = glm::cross    (m_orientation, m_up);
    m_right = glm::normalize(m_right);
    m_up    = glm::cross    (m_right, m_orientation);
    m_up    = glm::normalize(m_up);
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
	// Identity matrix
    glm::mat4 model(1.0f);

    model  = glm::orientate4(m_test);
    model *= glm::translate (model, GetPosition());
    model *= glm::scale     (model, m_scale);

    return model;
}

/*
	glm::vec3 direction = m_forward;
	direction -= m_position;
	direction  = glm::normalize(direction);

	m_up    = glm::vec3     (0.0f, 0.0f, 1.0f);
	m_right = glm::cross    (direction, m_up);
	m_right = glm::normalize(m_right);
	m_up    = glm::cross    (m_right, direction);
	m_up    = glm::normalize(m_up);
 */

}