/// \file       S_PointLight.cpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#include "Built-in/Script/S_PointLight.hpp"

/* virtual */ void S_PointLight::Awake()
{
	m_range       = 2.0f;
	m_intensity   = 1.0f;
	m_color       = glm::vec3(1.0f);
}

/* virtual */ void S_PointLight::Start()
{
	// None
}

/* virtual */ void S_PointLight::Update()
{
    // None
}

void S_PointLight::SetRange(float range)
{
    m_range = range;
}

void S_PointLight::SetIntensity(float intensity)
{
    m_intensity = intensity;
}

void S_PointLight::SetColor(glm::vec3 const& color)
{
    m_color = color;
}

float S_PointLight::GetRange() const
{
    return m_range;
}

float S_PointLight::GetIntensity() const
{
    return m_intensity;
}

glm::vec3 const& S_PointLight::GetColor() const
{
    return m_color;
}

