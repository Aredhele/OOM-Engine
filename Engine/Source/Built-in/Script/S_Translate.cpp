/// \file       S_Translate.cpp
/// \date       06/08/2018
/// \project    OOM-Engine
/// \package    Built-in/SCirpt
/// \author     Vincent STEHLY--CALISTO

#include "SDK/SDK.hpp"

/*virtual */ void S_Translate::Start()
{
	// None
}

/*virtual */ void S_Translate::Update()
{
	GetTransform()->Translate(glm::vec3(0.0f, 0.0f, glm::sin(CTime::time) * CTime::delta_time));
}
