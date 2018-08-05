/// \file       CPhysicWorld.hpp
/// \date       24/07/2018
/// \project    OOM-Engine
/// \package    Physics
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_PHYSIC_WORLD_HPP__
#define OOM_ENGINE_C_PHYSIC_WORLD_HPP__

class q3Scene;

namespace Oom
{

// Forward declaration
class CRigidBody;
class CContactListener;

class CPhysicWorld
{
public:

    // TODO

private:

    friend class CEngine;
    friend class CRigidBody;
    friend class CBoxCollider;

    bool Initialize (float delta_time);
    void Release    ();
    void Update     ();

    static q3Scene* GetScene        ();
    static void     RegisterBody    (CRigidBody* p_body);
    static void     UnregisterBody  (CRigidBody* p_body);

private:

    q3Scene*                    mp_scene     = nullptr;
	CContactListener*			mp_listener  = nullptr;

    static CPhysicWorld*        sp_instance;
    std::vector<CRigidBody*>    m_bodies;
};

}

#endif // !OOM_ENGINE_C_PHYSIC_WORLD_HPP__