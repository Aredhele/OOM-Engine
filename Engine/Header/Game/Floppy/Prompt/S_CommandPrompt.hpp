/// \file       S_CommandPrompt.hpp
/// \date       09/08/2018
/// \project    OOM-Engine
/// \package    Game/Floppy/Prompt/Script
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_S_COMMAND_PROMPT_HPP__
#define OOM_ENGINE_S_COMMAND_PROMPT_HPP__

#include "SDK/SDK.hpp"

// Forward declaration
class S_GameManager;

class S_CommandPrompt : public CBehavior
{
public:

	enum EPromptState
	{
		Open,
		Close
	};

	using Text  = CGameObject*;
	using Texts = std::vector<CGameObject*>;

public:

	void Awake       () final;
	void Start       () final;
	void Update      () final;
	void OnDestroy   () final;
	void OnDrawGizmos() final;

public:

	void OpenPrompt  ();
	void ClosePrompt ();
	bool IsOpen      () const;
	void LogMessage	 (const CString& message);

public:

	       void ProcessCharacter   (unsigned int codepoint);
	static void OnCharacterCallback(unsigned int codepoint);

private:

	void HideLogText();
	void ShowLogText();
	void MinimizePrompt();
	void MaximizePrompt();
	void HideCommandText();
	void ShowCommandText();

	void UpdatePromptLogs ();
	void UpdateCommandText();

	void ProcessCommand   (const CString& command);

private:

	EPromptState	m_state;

	float			m_key_delay;
	float			m_key_elapsed;

	glm::tvec2<int> m_command_position;
	glm::vec3		m_prompt_scale_open;
	glm::vec3		m_prompt_scale_close;
	glm::vec3		m_prompt_position_open;
	glm::vec3		m_prompt_position_close;

	
	Texts	       m_used_texts;
	Texts	       m_free_texts;
	CString        m_command;
	Text		   m_command_text  = nullptr;
	CGameObject*   mp_prompt       = nullptr;

	// Buffer
	S_GameManager* mp_game_manager = nullptr;

private:

	static S_CommandPrompt* sp_instance;
};


#endif // !OOM_ENGINE_S_COMMAND_PROMPT_HPP__