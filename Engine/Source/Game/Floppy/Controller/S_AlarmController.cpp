/// \file       S_AlarmController.cpp
/// \date       11/08/2018
/// \project    OOM-Engine
/// \package    Game/Floppy/Controller
/// \author     Vincent STEHLY--CALISTO

#include "Game/Floppy/Controller/S_AlarmController.hpp"

/* virtual */ void S_AlarmController::Awake()
{
	mp_renderer_on  = nullptr;
	mp_renderer_off = nullptr;
	m_elapsed	    = 0.0f;
	m_duration		= 7.0f;
	m_triggered     = false;
}

/* virtual */ void S_AlarmController::Start()
{
	mp_renderer_on->SetVisible (false);
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
}

void S_AlarmController::SetTargetRenderer(CMeshRenderer* p_on, CMeshRenderer* p_off)
{
	mp_renderer_on  = p_on;
	mp_renderer_off = p_off;
}
