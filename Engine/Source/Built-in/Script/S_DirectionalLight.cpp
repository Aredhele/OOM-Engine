/// \file       S_DirectionalLight.cpp
/// \date       03/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#include "Built-in/Script/S_DirectionalLight.hpp"

/* virtual */ void S_DirectionalLight::Awake()
{
	SetLightIntensity  (0.8f);
	SetAmbientIntensity(0.3f);
	SetLightColor  (glm::vec3( 1.0f,  1.0f,  1.0f));
	SetDirection   (glm::vec3(-0.5f, -0.5f, -0.5f));
	SetAmbientColor(glm::vec3( 1.0f,  1.0f,  1.0f));
}

/* virtual */ void S_DirectionalLight::Start()
{
   // None
}

/* virtual */ void S_DirectionalLight::Update()
{
    // None
}

void S_DirectionalLight::SetLightIntensity(float intensity)
{
    m_light_intensity = intensity;
}

void S_DirectionalLight::SetAmbientIntensity(float intensity)
{
    m_ambient_intensity = intensity;
}

void S_DirectionalLight::SetDirection(glm::vec3 const& direction)
{
    m_direction = direction;
}

void S_DirectionalLight::SetLightColor(glm::vec3 const& color)
{
    m_light_color = color;
}

void S_DirectionalLight::SetAmbientColor(glm::vec3 const& color)
{
    m_ambient_color = color;
}

float S_DirectionalLight::GetLightIntensity() const
{
    return m_light_intensity;
}

float S_DirectionalLight::GetAmbientIntensity() const
{
    return m_ambient_intensity;
}

glm::vec3 const& S_DirectionalLight::GetDirection() const
{
    return m_direction;
}

glm::vec3 const& S_DirectionalLight::GetLightColor() const
{
    return m_light_color;
}

glm::vec3 const& S_DirectionalLight::GetAmbientColor() const
{
    return m_ambient_color;
}
