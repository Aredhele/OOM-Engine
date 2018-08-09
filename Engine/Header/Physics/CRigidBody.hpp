/// \file       CRigidBody.hpp
/// \date       24/07/2018
/// \project    OOM-Engine
/// \package    Physics
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_RIGID_BODY_HPP__
#define OOM_ENGINE_C_RIGID_BODY_HPP__

#include "Composite/IComponent.hpp"

// Forward declaration
class q3Body;

namespace Oom
{

class CRigidBody : public IComponent
{
public:

    enum EBodyType
    {
        Static,
        Dynamic,
        Kinematic,
    };

	bool      IsAwake				() const;
	bool	  IsXLocked				() const;
	bool	  IsYLocked				() const;
	bool	  IsZLocked				() const;
	float     GetMass				() const;
	float     GetGravityScale		() const;
	float	  GetLinearDamping		() const;
	float	  GetAngularDamping		() const;
	int32_t   GetLayers				() const;
    EBodyType GetBodyType           () const;
	glm::vec3 GetPosition			() const;
	glm::vec3 GetOrientation		() const;
    glm::vec3 GetAngularVelocity    () const;
    glm::vec3 GetLinearVelocity     () const;

	void Sleep						();
	void Awake						();
	void SetLockX					(bool lock);
	void SetLockY					(bool lock);
	void SetLockZ					(bool lock);
	void SetLayers					(int32_t layers);
	void SetBodyType				(EBodyType body_type);
	void SetGravityScale			(float gravity_scale);
	void SetLinearDamping			(const float damping);
	void SetAngularDamping			(const float damping);
	void SetPosition				(const glm::vec3& position);
	void SetOrientationX			(float angle);
	void SetOrientationY			(float angle);
	void SetOrientationZ			(float angle);
    void SetLinearVelocity          (const glm::vec3& velocity);
    void SetAngularVelocity         (const glm::vec3& velocity);
	void AddTorque					(const glm::vec3& torque);
	void AddLinearForce				(const glm::vec3& force);
	void AddLinearImpulse			(const glm::vec3& impulse);
	void AddForceAtPosition			(const glm::vec3& force, const glm::vec3& point);
	void AddLinearImpulseAtPosition	(const glm::vec3& impulse, const glm::vec3& point);

	// Component
    void OnEnable  () final;
    void OnDisable () final;

protected:

    void _Register () final;
    void _Destroy  () final;

private:

    friend class CBoxCollider;
	void CreateBody ();
	void DestroyBody();

private:

	q3Body*		mp_body;
	bool		m_lock_x;
	bool        m_lock_y;
	bool		m_lock_z;
	float		m_linear_damping;
	float		m_gravity_scale;
	float		m_angular_damping;
	int32_t     m_layers;
	EBodyType	m_body_type;
	glm::vec3   m_linear_velocity;
	glm::vec3   m_angular_velocity;
};

}

#endif // !OOM_ENGINE_C_RIGID_BODY_HPP__