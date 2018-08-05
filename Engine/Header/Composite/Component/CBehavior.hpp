/// \file       CBehavior.hpp
/// \date       22/07/2018
/// \project    OOM-Engine
/// \package    Composite/Components
/// \author     Vincent STEHLY--CALISTO

#ifndef OOM_ENGINE_C_BEHAVIOR_HPP__
#define OOM_ENGINE_C_BEHAVIOR_HPP__

#include "Composite/IComponent.hpp"

// Forward declaration
struct CCollision;

namespace Oom
{

class CBehavior : public IComponent
{
public:

    CBehavior(const CBehavior& behavior)           = delete;
    CBehavior(      CBehavior&& behavior) noexcept = delete;

    virtual void Awake            ();
    virtual void Start            ();
    virtual void Update           ();
	virtual void OnCollisionEnter (const CCollision& collision);
            void OnDestroy        () override;
            void OnEnable         () override;
            void OnDisable        () override;
    virtual void OnDrawGizmos     ();

protected:
    void _Register() override;
    void _Destroy() override;

protected:

    friend class CEngine;
    CBehavior() = default;

private:

    void __Awake        (CBehavior* p_behavior);
    void __Start        ();
    void __Update       ();
    void __OnDestroy    ();
    void __OnEnable     ();
    void __OnDisable    ();
    void __OnDrawGizmos ();

private:

    bool m_first_update = true;
};

}

#endif // !OOM_ENGINE_I_BEHAVIOR_HPP__