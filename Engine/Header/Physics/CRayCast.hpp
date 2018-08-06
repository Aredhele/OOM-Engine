/// \file       CRayCast.hpp
/// \date       06/08/2018
/// \project    OOM-Engine
/// \package    Physics
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_RAY_CAST_HPP__
#define OOM_ENGINE_C_RAY_CAST_HPP__

#include <QU3E/q3.h>
#include <GLM/glm.hpp>

namespace Oom
{

class CGameObject;
	
class CRayCast : public q3QueryCallback
{
public:

	CRayCast();
	CRayCast(const glm::vec3& start, const glm::vec3& dir);

	void Init		(const glm::vec3& start, const glm::vec3& dir);
	bool ReportShape(q3Box* p_shape) final;

	CGameObject*   GetGameObject ();
	q3RaycastData& GetRayCastData();

private:

	friend class CPhysicWorld;

	r32			  m_final;
	q3Vec3		  m_nfinal;
	q3Body*       mp_impact_body;
	q3RaycastData m_data;
};

}

#endif ! //OOM_ENGINE_C_RAY_CAST_HPP__