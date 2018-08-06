/// \file       S_Rotate.cpp
/// \date       06/08/2018
/// \project    OOM-Engine
/// \package    Built-in/SCirpt
/// \author     Vincent STEHLY--CALISTO

#include "SDK/SDK.hpp"

/*virtual */ void S_Rotate::Start()
{
	// None
}

/*virtual */ void S_Rotate::Update()
{
	GetTransform()->Rotate(m_axis * 10.0f * CTime::delta_time);
}

void S_Rotate::SetAxis(const glm::vec3& axis)
{
	m_axis = axis;
}
