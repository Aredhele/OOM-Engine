/// \file       CRayCast.cpp
/// \date       06/08/2018
/// \project    OOM-Engine
/// \package    Physics
/// \author     Vincent STEHLY--CALISTO

#include "Physics/CRayCast.hpp"
#include "Composite/CGameObject.hpp"

namespace Oom
{

CRayCast::CRayCast()
{
	Init(glm::vec3(0.0f), glm::vec3(0.0f));
}

CRayCast::CRayCast(const glm::vec3& start, const glm::vec3& dir)
{
	Init(start, dir);
}

void CRayCast::Init(const glm::vec3& start, const glm::vec3& dir)
{
	m_data.start  = q3Vec3(start.x, start.z, start.y);
	m_data.dir    = q3Normalize(q3Vec3(dir.x, dir.z, dir.y));

	m_data.t       = r32(10000.0);
	m_final        = FLT_MAX;
	m_data.toi     = m_data.t;
	mp_impact_body = nullptr;
}

/* virutal */ bool CRayCast::ReportShape(q3Box* p_shape)
{
	if (m_data.toi < m_final)
	{
		m_final        = m_data.toi;
		m_nfinal       = m_data.normal;
		mp_impact_body = p_shape->body;
	}

	m_data.toi = m_final;
	return true;
}

CGameObject* CRayCast::GetGameObject()
{
	if(mp_impact_body)
	{
		return (CGameObject*)mp_impact_body->GetUserData();
	}

	return nullptr;
}

q3RaycastData& CRayCast::GetRayCastData()
{
	return m_data;
}

}
