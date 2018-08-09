/// \file       CInputManager.hpp
/// \date       09/08/2018
/// \project    OOM-Engine
/// \package    Game/Floppy/Prompt/Script
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_INPUT_MANAGER_HPP__
#define OOM_ENGINE_C_INPUT_MANAGER_HPP__

#include "SDK/SDK.hpp"

class CInputManager
{
public:

	struct SKeyState
	{
		int  key;
		bool IsPressed;
		bool IsReleased;
	};

	static void Update		();
	static void Initialize	();
	static bool IsKeyPressed(int key);

private:

	static std::vector<SKeyState> s_inputs;
	
};


#endif // !OOM_ENGINE_C_INPUT_MANAGER_HPP__