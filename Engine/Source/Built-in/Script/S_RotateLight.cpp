/// \file       S_RotateLight.cpp
/// \date       08/08/2018
/// \project    OOM-Engine
/// \package    Built-in/SCirpt
/// \author     Vincent STEHLY--CALISTO

#include "SDK/SDK.hpp"

/*virtual */ void S_RotateLight::Awake()
{
	// None
}

/*virtual */ void S_RotateLight::Start()
{
	mp_p_light = GetGameObject()->GetComponent<S_PointLight>();
	mp_d_light = GetGameObject()->GetComponent<S_DirectionalLight>();

	if (mp_d_light)
	{
		mp_d_light->SetLightIntensity(0.4f);
		mp_d_light->SetAmbientIntensity(0.2f);
		mp_d_light->SetDirection(glm::vec3(0.1f, 0.5f, 0.1f));
	}
}

/*virtual */ void S_RotateLight::Update()
{
	if (mp_d_light)
	{
		const glm::vec3 direction = glm::rotate(mp_d_light->GetDirection(), 1.0f * CTime::delta_time, glm::vec3(0.0f, 0.0f, 1.0f));
		mp_d_light->SetDirection(direction);
	}

	if(mp_p_light)
	{
		mp_p_light->GetTransform()->RotateAround(glm::vec3(0.0f), glm::vec3(0.0f, 0.0f, 1.0f), 2.0f * CTime::delta_time);
		Sdk::Debug::DrawTransform(*mp_p_light->GetTransform());
	}
}
