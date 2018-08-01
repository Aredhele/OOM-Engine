/// \file       CBoxCollider.hpp
/// \date       01/08/2018
/// \project    OOM-Engine
/// \package    Physics
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_BOX_COLLIDER_HPP__
#define OOM_ENGINE_C_BOX_COLLIDER_HPP__

#include "Composite/IComponent.hpp"

namespace Oom
{

class CBoxCollider : public IComponent
{
public:

public:
    void OnEnable  () final;
    void OnDisable () final;

protected:
    void _Register () final;
    void _Destroy  () final;

private:

    friend class CRigidBody;
    void OnBodyAttached  ();
    void RemoveBoxHandle ();

private:

    q3BoxDef     m_box_def;
    const q3Box* mp_box = nullptr;
};

}

#endif // !OOM_ENGINE_C_BOX_COLLIDER_HPP__