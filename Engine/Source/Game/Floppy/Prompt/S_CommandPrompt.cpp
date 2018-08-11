/// \file       S_CommandPrompt.cpp
/// \date       09/08/2018
/// \project    OOM-Engine
/// \package    Game/Floppy/Prompt/Script
/// \author     Vincent STEHLY--CALISTO

#include "Game/Floppy/S_GameManager.hpp"
#include "Game/Floppy/Asset/S_AssetSpawner.hpp"
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
	m_prompt_scale_open     = glm::vec3(6.5f, 7.0f,  1.0f);
	m_prompt_scale_close    = glm::vec3(6.5f, 1.35f, 1.0f);

	m_prompt_position_open  = glm::vec3(0.208f, 0.598f, 0.0f);
	m_prompt_position_close = glm::vec3(0.208f, 0.915f, 0.0f);

	m_text_scale            = glm::vec3(0.2f,  0.2f,  0.2f);
	m_command_scale         = glm::vec3(0.25f, 0.25f, 0.25f);
	m_command_position      = glm::vec3(0.02f, 0.25f, 0.0f);
	m_log_count             = 20;
	m_max_char				= 42;

	m_key_delay   = 0.2f;
	m_key_elapsed = 0.0f;
}	

/* virtual */ void S_CommandPrompt::Start()
{
	mp_prompt = Sdk::GameObject::CreateUISprite();

	auto* p_material = mp_prompt->GetComponent<CMaterial>();
	auto* p_renderer = mp_prompt->GetComponent<CUISpriteRenderer>();

	p_renderer->SetSortingLayer(0);
	p_material->SetTexture(Sdk::Import::ImportTexture("Resources/Texture/T_Prompt.png"));

	m_command_text = Sdk::GameObject::CreateUIText();
	auto* p_text   = m_command_text->GetComponent<S_Text>();

	m_command_text->GetTransform().SetScale   (m_command_scale);
	m_command_text->GetTransform().SetPosition(m_command_position);

	m_username = getenv("USERNAME");
	m_username.Resize(10);
	m_command = m_username + " > ";
	UpdateCommandText();
	
	sp_instance = this;
	glfwSetCharCallback(CRenderer::GetRenderWindow()->GetHandle(), character_callback);

	// Initializing prompt texts
	for(uint32_t i = 0; i < m_log_count; ++i)
	{
		auto* p_text_go = Sdk::GameObject::CreateUIText();

		p_text_go->GetTransform().SetScale(m_text_scale);
		p_text_go->GetComponent<CTextRenderer>()->SetVisible(false);
		p_text_go->GetComponent<CMaterial>()->SetColor(glm::vec3(0.0f, 1.0f, 0.0f));

		m_free_texts.push_back(p_text_go);
	}

	auto* p_go = CGameObject::FindWithTag("Game_Manager");

	if(p_go)
		mp_game_manager = p_go->GetComponent<S_GameManager>();
	ShowStartingText();
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

			if(m_command.Size() > m_username.Size() + 3)
			{
				m_command.PopBack();
				UpdateCommandText();
			}
		}

		if (Sdk::Input::IsKeyPressed(GLFW_KEY_ENTER) && m_key_elapsed >= m_key_delay)
		{
			m_key_elapsed = 0.0f;
			LogMessage    (m_command, false);
			ProcessCommand(m_command);
			m_command = m_username + " > ";
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
		if(m_command.Size() < m_max_char)
		{
			m_command += toupper((char)codepoint);
			UpdateCommandText();
		}
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

void S_CommandPrompt::LogMessage(const CString& _message, bool isSystem)
{
	CString message = CString(_message.Data());
	message.toUpper();
	if (isSystem)
	{
		message = "SYSTEM > " + message;
	}
	if(m_free_texts.empty())
	{
		auto* p_front_go       = m_used_texts.front();
		auto* p_text_component = p_front_go->GetComponent<S_Text>();

		for (auto i = 0; i < m_used_texts.size() - 1; ++i)
			m_used_texts[i] = m_used_texts[i + 1];

		p_text_component->SetText(message.Data());
		
		m_used_texts.pop_back();
		m_used_texts.push_back(p_front_go);
	}
	else
	{
		auto* p_go             = m_free_texts.back();
		auto* p_text_component = p_go->GetComponent<S_Text>();

		p_text_component->SetText(message.Data());

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
	for (auto i = 4; i < m_used_texts.size(); ++i)
	{
		m_used_texts[i]->GetComponent<CTextRenderer>()->SetVisible(false);
	}	
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
		p_text->GetTransform().SetPosition(0.02f, 0.95f - n_pos * 0.03f, 0.0f);

		n_pos++;
	}
}

void S_CommandPrompt::UpdateCommandText()
{
	auto* p_text = m_command_text->GetComponent<S_Text>();
	p_text->SetText(m_command.Data());
}

void S_CommandPrompt::ProcessCommand(const CString& _command)
{
	CString command = CString(_command.Data());
	command.toUpper();
	if (command.Size() < 3)
		return;

	const CString true_command = &command[3 + m_username.Size()];
	if		(true_command == "START CB1") { mp_game_manager->StartConveyorBelt(ESpawnZone::C1); }
	else if (true_command == "START CB2") { mp_game_manager->StartConveyorBelt(ESpawnZone::C2); }
	else if (true_command == "START CB3") { mp_game_manager->StartConveyorBelt(ESpawnZone::C3); }
	else if (true_command == "START CB4") { mp_game_manager->StartConveyorBelt(ESpawnZone::C4); }
	else if (true_command == "STOP CB1" ) { mp_game_manager->StopConveyorBelt (ESpawnZone::C1); }
	else if (true_command == "STOP CB2" ) { mp_game_manager->StopConveyorBelt (ESpawnZone::C2); }
	else if (true_command == "STOP CB3" ) { mp_game_manager->StopConveyorBelt (ESpawnZone::C3); }
	else if (true_command == "STOP CB4" ) { mp_game_manager->StopConveyorBelt (ESpawnZone::C4); }

	else if (true_command == "OPEN D1" ) { mp_game_manager->OpenDoor (ESpawnZone::R1); }
	else if (true_command == "OPEN D2" ) { mp_game_manager->OpenDoor (ESpawnZone::R2); }
	else if (true_command == "OPEN D3" ) { mp_game_manager->OpenDoor (ESpawnZone::R3); }
	else if (true_command == "CLOSE D1") { mp_game_manager->CloseDoor(ESpawnZone::R1); }
	else if (true_command == "CLOSE D2") { mp_game_manager->CloseDoor(ESpawnZone::R2); }
	else if (true_command == "CLOSE D3") { mp_game_manager->CloseDoor(ESpawnZone::R3); }

	else if (true_command == "ACTIVATE FIREWALL") { mp_game_manager->TryActivateFirewall(); }
	else if (true_command == "CLEAN ALL CB") { mp_game_manager->TryCleanAllCB(); }
	else if (true_command == "HELP") { mp_game_manager->ShowHelp(); }
	else if (true_command == "START HACKING") { mp_game_manager->StartHacking(); }
	else if (true_command == "LOGOUT") { mp_game_manager->Logout(); }

	else
	{
		mp_game_manager->ProcessUnknownCommand(true_command);		
	}
}

void S_CommandPrompt::ShowStartingText()
{
	CString username = getenv("USERNAME");
	LogMessage(username + " CONNECTED WITH SUCCESS");
	LogMessage("RIGHT CLICK TO SHOOT");
	LogMessage("PRESS WASD or ARROW KEYS TO MOVE AROUND");
	LogMessage("PRESS CTRL KEY TO OPEN OR CLOSE THE TERMINAL");
	LogMessage("INCOMING EXTERNAL MESSAGE :");
	LogMessage("HEY ! IT'S JEAN HENRI.");
	LogMessage("YOU HAVE TO DESTROY THE ARTISTS ASSETS");
	LogMessage("IF YOU DON'T THE FLOPPY WILL OVERTROW");
	LogMessage("YOU CAN TYPE IN COMMANDS IN THE TERMINAL");
	LogMessage("USE THE \"HELP\" COMMAND TO SHOW ALL COMMANDS");
	LogMessage("THE STUDIO'S FUTURE IS IN YOUR HANDS");
	LogMessage("[END OF MESSAGE]");
}
