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
        Unknown
    };

public:
    EBodyType GetBodyType           () const;
    glm::vec3 GetAngularVelocity    () const;
    float     GetGravityScale       () const;
    glm::vec3 GetLinearVelocity     () const;
    float     GetMass               () const;
    bool      IsAwake               () const;
    int32_t   GetLayers             () const;
    glm::vec3 GetPosition           () const;
    glm::vec3 GetRotation           () const;

public:
    void AddTorque                    (const glm::vec3& torque );
    void AddLinearForce               (const glm::vec3& force  );
    void AddLinearImpulse             (const glm::vec3& impulse);
    void AddForceAtPosition           (const glm::vec3& force,   const glm::vec3& point);
    void AddLinearImpulseAtPosition   (const glm::vec3& impulse, const glm::vec3& point);
    void SetGravityScale              (float gravity_scale);
    void SetLinearVelocity            (const glm::vec3& velocity);
    void SetAngularVelocity           (const glm::vec3& velocity);
	void SetBodyType                  (EBodyType body_type);
    void SetLayers                    (int32_t layers);
    void Sleep                        ();
    void Awake                        ();
    void SetPosition                  (const glm::vec3& position);
    void SetRotation                  (const glm::vec3& rotation);

    // TODO : Add damping and a way to lock axis

public:
    void OnEnable  () final;
    void OnDisable () final;

protected:
    void _Register () final;
    void _Destroy  () final;

private:

    friend class CBoxCollider;
    q3Body* mp_body = nullptr;
};

}

#endif // !OOM_ENGINE_C_RIGID_BODY_HPP__