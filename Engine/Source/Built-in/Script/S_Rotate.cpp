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

/*virtual */ void S_Rotate::OnDrawGizmos()
{
	Sdk::Debug::DrawBox(GetTransform()->GetTarget(), 0.2f, 0.2f, glm::vec3(0.0f, 0.0f, 1.0f));
	Sdk::Debug::DrawRay(GetTransform()->GetPosition(), GetTransform()->GetUp()      * 5.0, glm::vec3(0.0f, 1.0f, 0.0f));
	Sdk::Debug::DrawRay(GetTransform()->GetPosition(), GetTransform()->GetRight()   * 5.0, glm::vec3(0.0f, 0.0f, 1.0f));
	Sdk::Debug::DrawRay(GetTransform()->GetPosition(), GetTransform()->GetForward() * 5.0, glm::vec3(1.0f, 0.0f, 0.0f));
}

void S_Rotate::IsAround()
{
	m_around = true;
}

void S_Rotate::SetAxis(const glm::vec3& axis)
{
	m_axis = axis;
}
