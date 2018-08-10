/// \file       S_DoorController.cpp
/// \date       10/08/2018
/// \project    OOM-Engine
/// \package    Game/Floppy/Controller
/// \author     Vincent STEHLY--CALISTO

#include "Game/Floppy/Controller/S_DoorController.hpp"

/* virtual */ void S_DoorController::Awake()
{
	m_is_closed = false;
}

/* virtual */  void S_DoorController::Start()
{
	// Physics
	auto* p_body   = GetGameObject()->AddComponent<CRigidBody>();
	auto* p_box    = GetGameObject()->AddComponent<CBoxCollider>();
	mp_source_door = GetGameObject()->AddComponent<CAudioSource3D>();

	p_body->SetBodyType(CRigidBody::EBodyType::Kinematic);
	p_box->SetExtent(glm::vec3(4.0f, 4.0f, 20.0f));
	p_box->SetLocalOrientation(glm::vec3(0.0f, 0.0f, 90.0f));

	// Audio
	m_audio_buffer_door.LoadFromFile("Resources/Sound/sound_automatic_door_fast.ogg");
	mp_source_door->SetAudioBuffer(&m_audio_buffer_door);

	mp_source_door->SetMinDistance(15.0f);
	mp_source_door->SetMaxDistance(30.0f);
}

/* virtual */  void S_DoorController::Update()
{
	if(m_is_closed && GetTransform()->GetPosition().z < 9.5f)
		GetTransform()->Translate(0.0f, 0.0, 60.0f * CTime::delta_time);

	if(!m_is_closed && GetTransform()->GetPosition().z > -13.3f)
		GetTransform()->Translate(0.0f, 0.0, -60.0f * CTime::delta_time);
}

/* virtual */  void S_DoorController::OnDestroy()
{
	mp_source_door->Stop();
}

void S_DoorController::OpenDoor()
{
	m_is_closed = false;
	mp_source_door->Play();
}

 void S_DoorController::CloseDoor()
{
	 m_is_closed = true;
	 mp_source_door->Play();
}