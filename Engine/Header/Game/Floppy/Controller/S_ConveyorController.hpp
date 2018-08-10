/// \file       S_ConveyorController.hpp
/// \date       10/08/2018
/// \project    OOM-Engine
/// \package    Game/Floppy/Controller
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_S_CONVEYOR_CONTROLLER_HPP__
#define OOM_ENGINE_S_CONVEYOR_CONTROLLER_HPP__

#include "SDK/SDK.hpp"

class S_ConveyorController : public CBehavior
{
public:

	void Awake     () final;
	void Start     () final;
	void Update    () final;
	void OnDestroy () final;

	void ActivateConveyor	 ();
	void DesactivateConveyor ();

private:

	// State
	bool			m_is_activated;
	float			m_uv_offset;
	GLuint			m_activated_texture;
	GLuint			m_desactivated_texture;

	CMaterial *		mp_material;
	CAudioSource3D* mp_source_switch_on;
	CAudioSource3D* mp_source_switch_off;
	CAudioBuffer    m_audio_buffer_switch_on;
	CAudioBuffer    m_audio_buffer_shutdown;
};

#endif // !OOM_ENGINE_S_CONVEYOR_AUDIO_CONTROLLER_HPP__
