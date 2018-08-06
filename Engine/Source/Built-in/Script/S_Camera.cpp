/// \file       S_Camera.cpp
/// \date       22/07/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#include <GLM/gtc/matrix_transform.hpp>

#include "Composite/CGameObject.hpp"
#include "Built-in/Script/S_Camera.hpp"

void S_Camera::Start()
{
    m_clear_color         = glm::vec3(0.51f, 0.56, 0.60f);
    m_projection_mode     = EProjectionMode::Perspective;
    m_field_of_view       = 45;
    m_clipping_plane_near = 0.3f;
    m_clipping_plane_far  = 1000;

	// TMP
	m_test        = glm::vec3(0.0f);
	m_scale       = glm::vec3(1.0f);
	m_position    = glm::vec3(0.0f);
	m_orientation = glm::vec3(0.0f);
	m_up          = glm::vec3(0.0f, 0.0f, 1.0f);
	m_right       = glm::vec3(1.0f, 0.0f, 0.0f);
	m_forward     = glm::vec3(0.0f, 1.0f, 0.0f);
	UpdateVector();

    UpdateViewMatrix();
    UpdateProjectionMatrix();
}

void S_Camera::Update()
{
    // None
}

const glm::vec3& S_Camera::GetClearColor() const
{ return m_clear_color; }

S_Camera::EProjectionMode S_Camera::GetProjectionMode() const
{ return m_projection_mode; }

float S_Camera::GetFieldOfView() const
{ return m_field_of_view; }

float S_Camera::GetClippingPlaneNear() const
{ return m_clipping_plane_near; }

float S_Camera::GetClipplingPlaneFar() const
{ return m_clipping_plane_far; }

const glm::mat4& S_Camera::GetProjectionMatrix() const
{ return m_projection_matrix; }

const glm::mat4& S_Camera::GetViewMatrix()
{
    UpdateViewMatrix();
    return m_view_matrix;
}

void S_Camera::SetClearColor(const glm::vec3& color)
{ m_clear_color = color; }

void S_Camera::SetProjectionMode(S_Camera::EProjectionMode mode)
{
    m_projection_mode = mode;
    UpdateProjectionMatrix();
}

void S_Camera::SetFieldOfView(float field_of_view)
{
    m_field_of_view = field_of_view;
    UpdateProjectionMatrix();
}

void S_Camera::SetClippingPlaneNear(float near)
{
    m_clipping_plane_near = near;
    UpdateProjectionMatrix();
}

void S_Camera::SetClippingPlaneFar(float far)
{
    m_clipping_plane_far = far;
    UpdateProjectionMatrix();
}

void S_Camera::UpdateViewMatrix()
{
  //  const auto& p_transform = mp_game_object->GetTransform();
	UpdateVector();

	m_view_matrix = glm::lookAt(
		m_position,
		m_forward,
		m_up);

	/*m_view_matrix = glm::lookAt(
        p_transform.GetPosition(),
        p_transform.GetTarget(),
        p_transform.GetUp());*/
}

void S_Camera::UpdateProjectionMatrix()
{
    // TODO : Orthographic camera
    m_projection_matrix = glm::perspective(glm::radians(m_field_of_view),
            16.0f / 9.0f,
            m_clipping_plane_near,
            m_clipping_plane_far);
}

/// TMP
void S_Camera::LookAt(float x, float y, float z)
{
	LookAt(glm::vec3(x, y, z));
}

void S_Camera::LookAt(const glm::vec3& target)
{
	m_forward = target;
	UpdateVector();
}

void S_Camera::Rotate(float x, float y, float z)
{
	Rotate(glm::vec3(x, y, z));
}

void S_Camera::Rotate(const glm::vec3& point)
{
	m_orientation += point;
	m_test += point;
	UpdateVector();
}

void S_Camera::RotateAround(const glm::vec3& point, const glm::vec3& axis, float angle)
{
	m_forward -= m_position;
	m_forward = glm::rotate(point, angle, axis);
	m_forward += m_position;
	UpdateVector();
}

void S_Camera::Translate(float x, float y, float z)
{
	Translate(glm::vec3(x, y, z));
}

void S_Camera::Translate(const glm::vec3& translation)
{
	m_position += translation;
	m_forward += translation;
	UpdateVector();
}

const glm::vec3& S_Camera::GetUp() const
{
	return m_up;
}

const glm::vec3& S_Camera::GetRight() const
{
	return m_right;
}

const glm::vec3& S_Camera::GetForward() const
{
	return m_forward;
}

const glm::vec3& S_Camera::GetPosition() const
{
	return m_position;
}

const glm::vec3& S_Camera::GetOrientation() const
{
	return m_orientation;
}

void S_Camera::UpdateVector()
{
	m_orientation = m_forward;
	m_orientation -= m_position;
	m_orientation = glm::normalize(m_orientation);

	m_up = glm::vec3(0.0f, 0.0f, 1.0f);
	m_right = glm::cross(m_orientation, m_up);
	m_right = glm::normalize(m_right);
	m_up = glm::cross(m_right, m_orientation);
	m_up = glm::normalize(m_up);
}
