/// \file       S_Player.cpp
/// \date       09/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#include "Game/Floppy/Player/S_Player.hpp"
#include "Game/Floppy/Util/S_DestroySound.hpp"

/* virtual */ void S_Player::Awake()
{
	// None
}

 /* virtual */ void S_Player::Start()
{
	 // Audio
	 // Loads shoot sounds
	 m_music_buffer.LoadFromFile("resources/Music/music_floppy_jam.ogg");
	 m_shoot_buffer.LoadFromFile("resources/Sound/sound_player_shoot.ogg");
	 
	 mp_music_source  = GetGameObject()->AddComponent<CAudioSource3D>();
	 mp_shoot_source  = GetGameObject()->AddComponent<CAudioSource3D>();

	 mp_music_source->SetAudioBuffer(&m_music_buffer);
	 mp_shoot_source->SetAudioBuffer(&m_shoot_buffer);

	 mp_shoot_source->SetMinDistance(2.0f);
	 mp_music_source->SetMinDistance(2.0f);
	 mp_shoot_source->SetMaxDistance(10.0f);
	 mp_music_source->SetMaxDistance(10.0f);

	 mp_music_source->Play(true);
}

 /* virtual */ void S_Player::Update()
{
	 if(Sdk::Input::IsMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
	 {
		 const auto& transform = *GetTransform();
		 mp_shoot_source->Play();
		 CRayCast ray_cast = Sdk::Physic::RayCast(transform.GetPosition(), transform.GetForward() * 100.0f);
		 if (ray_cast.GetGameObject())
		 {
			 // Creates the GO containing the audio source
			 auto* p_sound_go = Instantiate(ray_cast.GetGameObject()->GetTransform().GetPosition());

			 // Adds the audio controller
			 p_sound_go->AddComponent<S_DestroySound>();

			 // Delayed destroy
			 Destroy(p_sound_go, 2.0f);

			 Destroy(ray_cast.GetGameObject());
		 }
	 }
}

 /* virtual */ void S_Player::OnDestroy()
{
	 // None
}

/* virtual */ void S_Player::OnDrawGizmos()
{
	const auto& transform = *GetTransform();

	// Camera to forward ray
	Sdk::Debug::DrawRay(
		transform.GetPosition() - 
		(transform.GetUp()      * 0.5f) + 
		(transform.GetRight()   * 2.0f) + 
		(transform.GetForward() * 2.0f),
		 transform.GetForward() * 100.0f, glm::vec3(1.0f, 0.0f, 0.5f));
}