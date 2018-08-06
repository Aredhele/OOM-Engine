/// \file       S_Rotate.cpp
/// \date       06/08/2018
/// \project    OOM-Engine
/// \package    Built-in/SCirpt
/// \author     Vincent STEHLY--CALISTO

#include "SDK/SDK.hpp"

/*virtual */ void S_Rotate::Awake()
{
	m_around = false;
	m_axis   = glm::vec3(0.0f);
}

/*virtual */ void S_Rotate::Start()
{
	// None
}

/*virtual */ void S_Rotate::Update()
{
	if(m_around)
	{
		GetTransform()->RotateAround(glm::vec3(0.0f), m_axis, 1.0f * CTime::delta_time);
	}
	else
	{
		GetTransform()->Rotate(m_axis * 1.0f * CTime::delta_time);
	}
}

void S_Rotate::IsAround()
{
	m_around = true;
}

void S_Rotate::SetAxis(const glm::vec3& axis)
{
	m_axis = axis;
}
