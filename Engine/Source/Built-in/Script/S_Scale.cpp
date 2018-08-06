/// \file       S_Scale.cpp
/// \date       06/08/2018
/// \project    OOM-Engine
/// \package    Built-in/SCirpt
/// \author     Vincent STEHLY--CALISTO

#include "SDK/SDK.hpp"

/*virtual */ void S_Scale::Start()
{
	// None
}

/*virtual */ void S_Scale::Update()
{
	GetTransform()->SetScale(glm::vec3(1.0f) + glm::vec3(1.0f) * glm::sin(CTime::time) * 0.6f);
}
