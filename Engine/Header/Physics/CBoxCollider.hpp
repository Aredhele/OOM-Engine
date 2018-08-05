/// \file       CBoxCollider.hpp
/// \date       01/08/2018
/// \project    OOM-Engine
/// \package    Physics
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_BOX_COLLIDER_HPP__
#define OOM_ENGINE_C_BOX_COLLIDER_HPP__

#include "Composite/IComponent.hpp"

// Forward declaration
struct q3Box;

namespace Oom
{

class CBoxCollider : public IComponent
{
public:

	// Box collider
	void SetSensor           (const bool sensor);
	void SetDensity          (const float density);
	void SetFriction         (const float friction);
	void SetRestitution      (const float restitution);
	void SetExtent           (const glm::vec3& extent);
	void SetLocalPosition    (const glm::vec3& position);
	void SetLocalOrientation (const glm::vec3& orientation);

	void             IsSensor            () const;
	float            GetDensity          () const;
	float            GetFriction         () const;
	float            GetRestution        () const;
	const glm::vec3& GetExtent           () const;
	const glm::vec3& GetLocalPosition    () const;
	const glm::vec3& GetLocalOrientation () const;

	// Component
    void OnEnable  () final;
    void OnDisable () final;

protected:

    void _Register () final;
    void _Destroy  () final;

private:

    friend class CRigidBody;

    void OnBodyAttached  ();
    void RemoveBoxHandle ();
	void CreateBox       ();
	void DestroyBox      ();

private:

	const q3Box*    mp_box = nullptr;
	bool		    m_sensor;
	float           m_density;
	float           m_friction;
	float           m_restitution;
	const glm::vec3 m_extent;
	const glm::vec3 m_local_position;
	const glm::vec3 m_local_orientation;
};

}

#endif // !OOM_ENGINE_C_BOX_COLLIDER_HPP__