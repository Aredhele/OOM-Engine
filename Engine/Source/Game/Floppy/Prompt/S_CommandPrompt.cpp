/// \file       S_CommandPrompt.cpp
/// \date       09/08/2018
/// \project    OOM-Engine
/// \package    Game/Floppy/Prompt/Script
/// \author     Vincent STEHLY--CALISTO

#include "Game/Floppy/Prompt/S_CommandPrompt.hpp"

#include "Render/CWindow.hpp"
#include "Render/CRenderer.hpp"

/* static */ S_CommandPrompt* S_CommandPrompt::sp_instance = nullptr;

/// \brief GLFW character callback
void character_callback(GLFWwindow* window, unsigned int codepoint)
{
	S_CommandPrompt::OnCharacterCallback(codepoint);
}

/* virtual */ void S_CommandPrompt::Awake()
{
	m_command_position      = glm::tvec2<int>(50, 220);
	m_prompt_scale_open     = glm::vec3(6.0f, 7.0f, 1.0f);
	m_prompt_scale_close    = glm::vec3(6.0f, 1.3f, 1.0f);

	m_prompt_position_open  = glm::vec3(0.195f, 0.598f,   0.0f);
	m_prompt_position_close = glm::vec3(0.195f, 0.915f, 0.0f);

	m_key_delay   = 0.1f;
	m_key_elapsed = 0.0f;
}	

/* virtual */ void S_CommandPrompt::Start()
{
	mp_prompt = Sdk::GameObject::CreateUISprite();

	auto* p_material = mp_prompt->GetComponent<CMaterial>();
	auto* p_renderer = mp_prompt->GetComponent<CUISpriteRenderer>();

	p_renderer->SetSortingLayer(0);
	p_material->SetTexture(Sdk::Import::ImportTexture("Resources/Texture/Prompt.png"));

	m_command_text = Sdk::GameObject::CreateUIText();
	auto* p_text   = m_command_text->GetComponent<S_Text>();

	m_command = "> ";
	UpdateCommandText();
	
	sp_instance = this;
	glfwSetCharCallback(CRenderer::GetRenderWindow()->GetHandle(), character_callback);

	// Initializing prompt texts
	for(int i = 0; i < 10; ++i)
	{
		auto* p_text_go = Sdk::GameObject::CreateUIText();
		p_text_go->GetComponent<CTextRenderer>()->SetVisible(false);

		m_free_texts.push_back(p_text_go);
	}

	ClosePrompt();
}

/* virtual */ void S_CommandPrompt::Update()
{
	m_key_elapsed += CTime::delta_time;

	if(IsOpen())
	{
		if(Sdk::Input::IsKeyPressed(GLFW_KEY_BACKSPACE) && m_key_elapsed >= m_key_delay)
		{
			m_key_elapsed = 0.0f;

			if(m_command.Size() > 2)
			{
				m_command.PopBack();
				UpdateCommandText();
			}
		}

		if (Sdk::Input::IsKeyPressed(GLFW_KEY_ENTER) && m_key_elapsed >= m_key_delay)
		{
			m_key_elapsed = 0.0f;
			LogMessage(m_command);

			m_command = "> ";
			UpdateCommandText();
		}

		if (Sdk::Input::IsKeyPressed(GLFW_KEY_X) && m_key_elapsed >= m_key_delay)
		{
			m_key_elapsed = 0.0f;
			ClosePrompt();
		}
	}
}

/* virtual */ void S_CommandPrompt::OnDestroy()
{
	sp_instance = nullptr;
	glfwSetCharCallback(CRenderer::GetRenderWindow()->GetHandle(), nullptr);
}

/* virtual */ void S_CommandPrompt::OnDrawGizmos()
{
	// None
}

void S_CommandPrompt::ProcessCharacter(unsigned int codepoint)
{
	if(IsOpen())
	{
		m_command += (char)codepoint;
		UpdateCommandText();
	}
}

void S_CommandPrompt::OpenPrompt()
{
	m_state = EPromptState::Open;
	ShowLogText();
	MaximizePrompt();
	ShowCommandText();
}

void S_CommandPrompt::ClosePrompt()
{
	m_state = EPromptState::Close;
	HideLogText();
	MinimizePrompt();
	HideCommandText();
}

bool S_CommandPrompt::IsOpen() const
{
	return (m_state == EPromptState::Open);
}

void S_CommandPrompt::LogMessage(const CString& message)
{
	if(m_free_texts.empty())
	{
		printf("Empty\n");
		auto* p_front_go       = m_used_texts.front();
		auto* p_text_component = p_front_go->GetComponent<S_Text>();

		for (auto i = 0; i < m_used_texts.size() - 1; ++i)
			m_used_texts[i] = m_used_texts[i + 1];

		p_text_component->SetSize(40);
		p_text_component->SetText(message.Data());
		p_text_component->SetColor(glm::vec3(0.0f, 1.0f, 0.0f));

		m_used_texts.pop_back();
		m_used_texts.push_back(p_front_go);
	}
	else
	{
		auto* p_go             = m_free_texts.back();
		auto* p_text_component = p_go->GetComponent<S_Text>();

		p_text_component->SetSize(40);
		p_text_component->SetText(message.Data());
		p_text_component->SetColor(glm::vec3(0.0f, 1.0f, 0.0f));

		m_used_texts.push_back(p_go);
		m_free_texts.pop_back();
	}

	UpdatePromptLogs();
}

/* static */ void S_CommandPrompt::OnCharacterCallback(unsigned int codepoint)
{
	sp_instance->ProcessCharacter(codepoint);
}

void S_CommandPrompt::HideLogText()
{
	for(auto* p_text : m_used_texts)
		p_text->GetComponent<CTextRenderer>()->SetVisible(false);
}

void S_CommandPrompt::ShowLogText()
{
	for (auto* p_text : m_used_texts)
		p_text->GetComponent<CTextRenderer>()->SetVisible(true);
}

void S_CommandPrompt::MinimizePrompt()
{
	mp_prompt->GetTransform().SetScale(m_prompt_scale_close);
	mp_prompt->GetTransform().SetPosition(m_prompt_position_close);
}

void S_CommandPrompt::MaximizePrompt()
{
	mp_prompt->GetTransform().SetScale(m_prompt_scale_open);
	mp_prompt->GetTransform().SetPosition(m_prompt_position_open);
}

void S_CommandPrompt::HideCommandText()
{
	auto* p_renderer = m_command_text->GetComponent<CTextRenderer>();
	p_renderer->SetVisible(false);
}

void S_CommandPrompt::ShowCommandText()
{
	auto* p_renderer = m_command_text->GetComponent<CTextRenderer>();
	p_renderer->SetVisible(true);
}

void S_CommandPrompt::UpdatePromptLogs()
{
	uint32_t n_pos = 0;
	for (auto* p_text : m_used_texts)
	{
		auto* p_text_component = p_text->GetComponent<S_Text>();
		auto* p_renderer       = p_text->GetComponent<CTextRenderer>();

		p_renderer->SetVisible(true);
		p_text_component->SetPosition(glm::tvec2<int>(50, 800 - n_pos * 50));

		n_pos++;
	}
}

void S_CommandPrompt::UpdateCommandText()
{
	auto* p_text = m_command_text->GetComponent<S_Text>();
	p_text->Set(m_command.Data(), m_command_position, 35, glm::vec3(1.0f));
}
