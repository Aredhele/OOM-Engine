/// \file       CCamera.cpp
/// \date       21/07/2018
/// \project    OOM-Engine
/// \package    Render
/// \author     Vincent STEHLY--CALISTO

#include "Render/CCamera.hpp"

#include <GLM/gtx/rotate_vector.hpp>
#include <GLM/gtc/matrix_transform.hpp>

namespace Oom
{

/* explicit */ CCamera::CCamera()
{
    m_up        = glm::vec3(   0.0f,   0.0f,    1.0f);
    m_right     = glm::vec3(   1.0f,   0.0f,    0.0f);
    m_look_at   = glm::vec3(   0.0f,   0.0f,    0.0f);
    m_position  = glm::vec3(  10.0f,  10.0f,   10.0f);
    m_direction = glm::vec3(   0.0f,   0.0f,    1.0f);

    m_view_matrix       = glm::lookAt(m_position, m_look_at, m_up);
    m_projection_matrix = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 2000.0f);
}

void CCamera::UpdateVectors()
{
    m_direction  = m_look_at;
    m_direction -= m_position;
    m_direction  = glm::normalize(m_direction);

    m_up    = glm::vec3     (0.0f, 0.0f, 1.0f);
    m_right = glm::cross    (m_direction, m_up);
    m_right = glm::normalize(m_right);
    m_up    = glm::cross    (m_right, m_direction);
    m_up    = glm::normalize(m_up);

    m_view_matrix = glm::lookAt(m_position, m_look_at + m_direction, m_up);
}

void CCamera::LookAt(const glm::vec3& target)
{
    m_look_at = target;
    UpdateVectors();
}

void CCamera::Translate(const glm::vec3& translation)
{
    m_position += translation;
    m_look_at  += translation;
    UpdateVectors();
}

void CCamera::Rotate(float angle)
{
    m_look_at -= m_position;
    m_look_at  = glm::rotate(m_look_at, angle, m_up);
    m_look_at += m_position;
    UpdateVectors();
}

void CCamera::RotateUp(float angle)
{
    m_look_at -= m_position;
    m_look_at  = glm::rotate(m_look_at, angle, m_right);
    m_look_at += m_position;
    UpdateVectors();
}

void CCamera::RotateAround(float angle)
{
    m_position -= m_look_at;
    m_position  = glm::rotate(m_position, angle, m_up);
    m_position += m_look_at;
    UpdateVectors();
}

void CCamera::RotateUpAround(float angle)
{
    m_position -= m_look_at;
    m_position  = glm::rotate(m_position, angle, m_up);
    m_position += m_look_at;
    UpdateVectors();
}

void CCamera::SetPosition(const glm::vec3 &position)
{
    m_position = position;
    UpdateVectors();
}

void CCamera::SetDirection(const glm::vec3 &direction)
{
    m_direction = direction;
    UpdateVectors();
}

const glm::vec3& CCamera::GetPosition() const
{ return m_position; }

const glm::vec3& CCamera::GetDirection() const
{ return m_direction; }

const glm::vec3& CCamera::GetRight() const
{ return m_right; }

const glm::vec3& CCamera::GetUp() const
{ return m_up; }

const glm::mat4& CCamera::GetViewMatrix() const
{ return m_view_matrix; }

const glm::mat4& CCamera::GetProjectionMatrix() const
{ return m_projection_matrix; }

}