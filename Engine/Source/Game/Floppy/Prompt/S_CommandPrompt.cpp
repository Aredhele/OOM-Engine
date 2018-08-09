/// \file       S_CommandPrompt.cpp
/// \date       09/08/2018
/// \project    OOM-Engine
/// \package    Game/Floppy/Prompt/Script
/// \author     Vincent STEHLY--CALISTO

#include "Game/Floppy/Prompt/S_CommandPrompt.hpp"

/* virtual */ void S_CommandPrompt::Awake()
{
	m_prompt_scale_open     = glm::vec3(6.0f, 7.0f, 1.0f);
	m_prompt_scale_close    = glm::vec3(6.0f, 1.3f, 1.0f);

	m_prompt_position_open  = glm::vec3(0.195f, 0.6f,   0.0f);
	m_prompt_position_close = glm::vec3(0.195f, 0.915f, 0.0f);
}	

/* virtual */ void S_CommandPrompt::Start()
{
	mp_prompt_background = Sdk::GameObject::CreateUISprite();

	auto* p_material = mp_prompt_background->GetComponent<CMaterial>();
	auto* p_renderer = mp_prompt_background->GetComponent<CUISpriteRenderer>();

	p_renderer->SetSortingLayer(0);
	p_material->SetTexture(Sdk::Import::ImportTexture("Resources/Texture/Prompt.png"));

	mp_prompt_background->GetTransform().SetScale(m_prompt_scale_open);
	mp_prompt_background->GetTransform().SetPosition(m_prompt_position_open);
}

/* virtual */ void S_CommandPrompt::Update()
{
	// None
}

/* virtual */ void S_CommandPrompt::OnDestroy()
{
	// None
}

/* virtual */ void S_CommandPrompt::OnDrawGizmos()
{
	// None
}

void S_CommandPrompt::OpenPrompt()
{
	m_state = EPromptState::Open;
}

void S_CommandPrompt::ClosePrompt()
{
	m_state = EPromptState::Close;
}

bool S_CommandPrompt::IsOpen() const
{
	return (m_state == EPromptState::Open);
}
