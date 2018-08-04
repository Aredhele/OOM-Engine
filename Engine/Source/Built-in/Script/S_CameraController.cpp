/// \file       S_CameraController.cpp
/// \date       22/07/2018
/// \project    OOM-Engine
/// \package    Built-in Script
/// \author     Vincent STEHLY--CALISTO

#include "SDK/SDK.hpp"
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

    float maxMousePosRadius = min(windowSize.x, windowSize.y) / 2.0f;
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

    mp_transform->RotateAround(mp_transform->GetForward(), mp_transform->GetUp(),    angleX);
    mp_transform->RotateAround(mp_transform->GetForward(), mp_transform->GetRight(), angleY);
    mp_transform->Translate  ((mp_transform->GetLocalOrientation() * (float)y_direction + mp_transform->GetRight() * (float)x_direction) * 0.016f * m_speed * speed_coefficient);
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