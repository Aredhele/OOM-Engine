/// \file       S_AlarmController.cpp
/// \date       11/08/2018
/// \project    OOM-Engine
/// \package    Game/Floppy/Controller
/// \author     Vincent STEHLY--CALISTO

#include "Game/Floppy/Util/S_SoundSource.hpp"
#include "Game/Floppy/Controller/S_AlarmController.hpp"

/* virtual */ void S_AlarmController::Awake()
{
	mp_renderer_on  = nullptr;
	mp_renderer_off = nullptr;
	mp_point_light  = nullptr;
	m_elapsed	    = 0.0f;
	m_duration		= 7.0f;
	m_triggered     = false;
}

/* virtual */ void S_AlarmController::Start()
{
	mp_renderer_on->SetVisible(false);

	if(GetGameObject()->GetTag() != "Super_alarm_controller")
	{
		mp_point_light = GetGameObject()->AddComponent<S_PointLight>();

		mp_point_light->SetRange(10.0f);
		mp_point_light->SetIntensity(2.0f);
		mp_point_light->SetColor(glm::vec3(0.8f, 0.6f, 0.1f));
		mp_point_light->SetEnabled(false);
	}
}

/* virtual */ void S_AlarmController::Update()
{
	if(m_triggered)
	{
		m_elapsed += CTime::delta_time;

		if(m_elapsed >= m_duration)
		{
			m_triggered = false;
			m_elapsed   = 0.0f;

			mp_renderer_on->SetVisible(false);
			mp_renderer_off->SetVisible(true);

			if (mp_point_light)
				mp_point_light->SetEnabled(false);
		}
	}
}

/* virtual */ void S_AlarmController::OnDestroy()
{
	// None
}

void S_AlarmController::TriggerAlarm()
{
	m_triggered = true;
	m_elapsed   = 0.0f;

	mp_renderer_on->SetVisible(true);
	mp_renderer_off->SetVisible(false);

	if (mp_point_light)
		mp_point_light->SetEnabled(true);

	// Sound
	auto* p_alarm  = Instantiate(GetTransform());
	auto* p_source = p_alarm->AddComponent<S_SoundSource>();

	if (GetGameObject()->GetTag() != "Super_alarm_controller")
		p_source->SetSound("Resources/Sound/sound_small_alarm.ogg");
	else
		p_source->SetSound("Resources/Sound/sound_big_alarm.ogg");

	Destroy(p_alarm, 5.0f);
}

void S_AlarmController::SetTargetRenderer(CMeshRenderer* p_on, CMeshRenderer* p_off)
{
	mp_renderer_on  = p_on;
	mp_renderer_off = p_off;
}
