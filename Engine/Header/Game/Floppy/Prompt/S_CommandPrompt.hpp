/// \file       S_CommandPrompt.hpp
/// \date       09/08/2018
/// \project    OOM-Engine
/// \package    Game/Floppy/Prompt/Script
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_S_COMMAND_PROMPT_HPP__
#define OOM_ENGINE_S_COMMAND_PROMPT_HPP__

#include "SDK/SDK.hpp"

class S_CommandPrompt : public CBehavior
{
public:

	enum EPromptState
	{
		Open,
		Close
	};

	void Awake       () final;
	void Start       () final;
	void Update      () final;
	void OnDestroy   () final;
	void OnDrawGizmos() final;

public:

	void OpenPrompt  ();
	void ClosePrompt ();
	 
	bool IsOpen      () const;

private:

	EPromptState m_state;

	glm::vec3	 m_prompt_scale_open;
	glm::vec3	 m_prompt_scale_close;
	glm::vec3	 m_prompt_position_open;
	glm::vec3	 m_prompt_position_close;
	
	CGameObject* mp_prompt_background;
};


#endif // !OOM_ENGINE_S_COMMAND_PROMPT_HPP__