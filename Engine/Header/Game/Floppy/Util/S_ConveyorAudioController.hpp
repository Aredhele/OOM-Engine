/// \file       S_ConveyorAudioController.hpp
/// \date       00/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_S_CONVEYOR_AUDIO_CONTROLLER_HPP__
#define OOM_ENGINE_S_CONVEYOR_AUDIO_CONTROLLER_HPP__

#include "SDK/SDK.hpp"

class S_ConveyorAudioController : public CBehavior
{
public:

	void Awake     () final;
	void Start     () final;
	void OnDestroy () final;

	void ActivateConveyor	 ();
	void DesactivateConveyor ();

private:

	CAudioSource3D* mp_source_switch_on;
	CAudioSource3D* mp_source_switch_off;
	CAudioBuffer    m_audio_buffer_switch_on;
	CAudioBuffer    m_audio_buffer_shutdown;
};

#endif // !OOM_ENGINE_S_CONVEYOR_AUDIO_CONTROLLER_HPP__