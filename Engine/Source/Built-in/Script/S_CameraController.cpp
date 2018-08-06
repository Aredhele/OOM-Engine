/// \file       S_CameraController.cpp
/// \date       22/07/2018
/// \project    OOM-Engine
/// \package    Built-in Script
/// \author     Vincent STEHLY--CALISTO

#include "SDK/SDK.hpp"

#include "Render/Gizmos/CGizmosLine.hpp"
#include "Built-in/Script/S_CameraController.hpp"

/* virtual */ void S_CameraController::Start()
{
    m_speed                = 5.0f;
    m_sensitivity          = 0.0008f;
    m_run_speed_multiplier = 2.0f;
    m_last_mouse_position  = glm::tvec3<double>(0.0f);
}

/* virtual */ void S_CameraController::Update()
{
    glm::vec2          windowSize = Sdk::Window::GetWindowSize();
    glm::tvec3<double> mouse      = Sdk::Mouse::GetMousePosition();
    glm::tvec3<double> deltaMouse;

    deltaMouse = mouse - m_last_mouse_position;

    glm::vec2 mousePos    (mouse.x, mouse.y);
    glm::vec2 windowCenter(windowSize.x / 2, windowSize.y / 2);

    float maxMousePosRadius = glm::min(windowSize.x, windowSize.y) / 2.0f;
    if (glm::distance(mousePos, windowCenter) > maxMousePosRadius)
    {
        // Re-center the mouse
        Sdk::Mouse::SetMousePosition(windowCenter);
        m_last_mouse_position.x = windowCenter.x;
        m_last_mouse_position.y = windowCenter.y;
    }
    else
    {
        m_last_mouse_position.x = mousePos.x;
        m_last_mouse_position.y = mousePos.y;
    }

    // Keyboard Inputs
    int y_direction   = (Sdk::Input::IsKeyPressed(GLFW_KEY_W)) ? 1 : 0;
        y_direction  -= (Sdk::Input::IsKeyPressed(GLFW_KEY_S)) ? 1 : 0;
    int x_direction   = (Sdk::Input::IsKeyPressed(GLFW_KEY_D)) ? 1 : 0;
        x_direction  -= (Sdk::Input::IsKeyPressed(GLFW_KEY_A)) ? 1 : 0;

    auto angleX = static_cast<float>(-deltaMouse.x * m_sensitivity);
    auto angleY = static_cast<float>(-deltaMouse.y * m_sensitivity);
    float speed_coefficient = (Sdk::Input::IsKeyPressed(GLFW_KEY_LEFT_SHIFT)) ? m_run_speed_multiplier : 1.0f;

	auto* p_cam = GetGameObject()->GetComponent<S_Camera>();

	p_cam->RotateAround(p_cam->GetForward(), p_cam->GetUp(),    angleX);
	p_cam->RotateAround(p_cam->GetForward(), p_cam->GetRight(), angleY);
	p_cam->Translate  ((p_cam->GetOrientation() * (float)y_direction + p_cam->GetRight() * (float)x_direction) * 0.016f * m_speed * speed_coefficient);

	GetTransform()->SetPosition(p_cam->GetPosition());
	
	/*auto view_matrix = p_cam->GetViewMatrix();
	glm::vec3 right  = glm::row(view_matrix, 0);
	glm::vec3 up     = glm::row(view_matrix, 1);
	glm::vec3 foward = glm::row(view_matrix, 2);

	GetTransform()->SetUp(up);
	GetTransform()->SetRight(right);
	GetTransform()->SetForward(foward);*/
}

float S_CameraController::GetSpeed() const
{ return m_speed; }

float S_CameraController::GetSensitivirt() const
{ return m_sensitivity; }

float S_CameraController::GetRunSpeedMultiplier() const
{ return m_run_speed_multiplier; }

void S_CameraController::SetSpeed(float speed)
{ m_speed = speed; }

void S_CameraController::SetSensitivity(float sensitivity)
{ m_sensitivity = sensitivity; }

void S_CameraController::SetRunSpeedMultiplier(float multiplier)
{ m_run_speed_multiplier = multiplier; }