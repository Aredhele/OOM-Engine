/// \file       S_AlarmController.hpp
/// \date       11/08/2018
/// \project    OOM-Engine
/// \package    Game/Floppy/Controller
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_S_ALARM_CONTROLLER_HPP__
#define OOM_ENGINE_S_ALARM_CONTROLLER_HPP__

#include "SDK/SDK.hpp"

class S_AlarmController : public CBehavior
{
public:

	// Behavior
	void Awake    () final;
	void Start    () final;
	void Update   () final;
	void OnDestroy() final;

public:

	void TriggerAlarm	  ();
	void SetTargetRenderer(CMeshRenderer* p_on, CMeshRenderer* p_off);

private:

	float		   m_elapsed;
	float		   m_duration;
	bool		   m_triggered;
	S_PointLight*  mp_point_light;
	CMeshRenderer* mp_renderer_on;
	CMeshRenderer* mp_renderer_off;
};

#endif // !OOM_ENGINE_S_ALARM_CONTROLLER_HPP__
