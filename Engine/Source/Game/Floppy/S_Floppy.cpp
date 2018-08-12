/// \file       S_Floppy.cpp
/// \date       08/08/2018
/// \project    OOM-Engine
/// \package    Built-in/Script
/// \author     Vincent STEHLY--CALISTO

#include "Game/Floppy/S_Floppy.hpp"

/*virtual */ void S_Floppy::Awake()
{
	m_limit_size   = 1440;
	m_current_size = 0;

	mp_text		     = nullptr;
	mp_floppy_text   = nullptr;
	mp_floppy_sprite = nullptr;
	mp_source_floppy = nullptr;
}

/*virtual */ void S_Floppy::Start()
{
	mp_floppy_text    = Sdk::GameObject::CreateUIText  ();
	mp_floppy_sprite  = Sdk::GameObject::CreateUISprite();

	mp_text          = mp_floppy_text->GetComponent  <S_Text>();
	auto* p_material = mp_floppy_sprite->GetComponent<CMaterial>();
	auto* p_renderer = mp_floppy_sprite->GetComponent<CUISpriteRenderer>();
	mp_source_floppy = GetGameObject()->AddComponent<CAudioSource3D>();

	p_renderer->SetSortingLayer(0);
	p_material->SetTexture(Sdk::Import::ImportTexture("Resources/Texture/T_Floppy_UI.png"));

	mp_floppy_sprite->GetTransform().SetScale(0.8f, 0.8f, 0.8f);
	mp_floppy_sprite->GetTransform().SetPosition(0.96f, 0.06f, 0.0f);
	
	mp_text->SetText("0 / 1440 KB");
	mp_floppy_text->GetTransform().SetScale(0.4f, 0.4f, 0.4f);
	mp_floppy_text->GetTransform().SetPosition(0.75f, 0.04f, 0.0f);

	// Audio
	m_audio_buffer_floppy.LoadFromFile("Resources/Sound/sound_floppy_filling.ogg");
	mp_source_floppy->SetAudioBuffer(&m_audio_buffer_floppy);

	mp_source_floppy->SetMinDistance(15.0f);
	mp_source_floppy->SetMaxDistance(30.0f);

	// Moving away this anoying floppy
	GetTransform()->Translate(-20.0f, 0.0f, 0.0f);
}

/*virtual */ void S_Floppy::Update()
{
	GetTransform()->Rotate(0.0f, 0.0f, 1.0f * CTime::delta_time);
}

/*virtual */ void S_Floppy::OnDestroy()
{
	// None
}

void S_Floppy::AddKiloByte(uint32_t kilo_bytes)
{
	m_current_size += kilo_bytes;

	char text_buffer[32] = { '\0' };
	sprintf(text_buffer, "%d / 1440 KB", m_current_size);

	mp_text->SetText(text_buffer);
	mp_source_floppy->Play();
}

uint32_t S_Floppy::GetLimitSize() const
{
	return m_limit_size;
}

uint32_t S_Floppy::GetCurrentSize() const
{
	return m_current_size;
}
