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
}

/*virtual */ void S_Floppy::Start()
{
	mp_floppy_text    = Sdk::GameObject::CreateUIText  ();
	mp_floppy_sprite  = Sdk::GameObject::CreateUISprite();

	mp_text          = mp_floppy_text->GetComponent  <S_Text>();
	auto* p_material = mp_floppy_sprite->GetComponent<CMaterial>();
	auto* p_renderer = mp_floppy_sprite->GetComponent<CUISpriteRenderer>();
	
	p_renderer->SetSortingLayer(0);
	p_material->SetTexture(Sdk::Import::ImportTexture("Resources/Texture/Floppy_ui.jpg"));

	mp_floppy_sprite->GetTransform().SetPosition(0.96f, 0.06f, 0.0f);
	mp_text->Set("0 / 1.44 M B", glm::tvec2<int>(1430, 35), 45, glm::vec3(1.0f));
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

	// TODO : To string function ?
	char text_buffer[128] = { '\0' };
	sprintf(text_buffer, "%d / 1.44 M B", m_current_size);

	mp_text->Set(text_buffer, glm::tvec2<int>(1440, 35), 45, glm::vec3(1.0f));
}

uint32_t S_Floppy::GetLimitSize() const
{
	return m_limit_size;
}

uint32_t S_Floppy::GetCurrentSize() const
{
	return m_current_size;
}
