/// \file       CBehavior.hpp
/// \date       22/07/2018
/// \project    OOM-Engine
/// \package    Composite/Components
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_BEHAVIOR_HPP__
#define OOM_ENGINE_C_BEHAVIOR_HPP__

#include "Composite/IComponent.hpp"

namespace Oom
{

class CBehavior : public IComponent
{
public:

    virtual void Awake       ();
    virtual void Start       ();
    virtual void Update      ();
            void OnDestroy   () override;
            void OnEnable    () override;
            void OnDisable   () override;
    virtual void OnDrawGizmos();

private:

    void __Awake        ();
    void __Start        ();
    void __Update       ();
    void __OnDestroy    ();
    void __OnEnable     ();
    void __OnDisable    ();
    void __OnDrawGizmos ();

private:

    friend class CEngine;
    bool m_first_update = true;
};

}

#endif // !OOM_ENGINE_I_BEHAVIOR_HPP__