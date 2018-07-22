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
    Oom::CTransform& p_transform = mp_game_object->GetTransform();

    m_view_matrix = glm::lookAt(
            p_transform.GetWorldPosition(),
            p_transform.GetForward(),
            p_transform.GetUp());
}

void S_Camera::UpdateProjectionMatrix()
{
    // TODO : Orthographic camera
    m_projection_matrix = glm::perspective(glm::radians(m_field_of_view),
            16.0f / 9.0f,
            m_clipping_plane_near,
            m_clipping_plane_far);
}
