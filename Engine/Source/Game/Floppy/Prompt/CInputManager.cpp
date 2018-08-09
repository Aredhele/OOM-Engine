/// \file       CInputManager.cpp
/// \date       09/08/2018
/// \project    OOM-Engine
/// \package    Game/Floppy/Prompt/Script
/// \author     Vincent STEHLY--CALISTO

#include "Game/Floppy/Prompt/CInputManager.hpp"

/* static */ std::vector<CInputManager::SKeyState> CInputManager::s_inputs;

void CInputManager::Initialize()
{
	s_inputs.reserve(GLFW_KEY_LAST);

	for(int i = 0; i <= GLFW_KEY_LAST; ++i)
	{
		// Adding useless key to be able to use
		// the subscript array operator
		s_inputs.push_back({ i, false, true });
	}
}

void CInputManager::Update()
{
	for (int i = GLFW_KEY_SPACE; i <= GLFW_KEY_LAST; ++i)
	{
		if(s_inputs[i].IsReleased)
		{
			s_inputs[i].IsPressed = Sdk::Input::IsKeyPressed(i);
		}
		else
		{
			s_inputs[i].IsPressed = false;
			if(Sdk::Input::IsKeyReleased(i))
			{
				s_inputs[i].IsReleased = true;
			}
		}
	}
}


bool CInputManager::IsKeyPressed(int key)
{
	return s_inputs[key].IsPressed;
}

