/// \file       S_CameraController.cpp
/// \date       22/07/2018
/// \project    OOM-Engine
/// \package    Built-in Script
/// \author     Vincent STEHLY--CALISTO

#include "Built-in/Script/S_CameraController.hpp"

/* virtual */ void S_CameraController::Start()
{
    // TODO
}

/* virtual */ void S_CameraController::Update()
{
    // TODO
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